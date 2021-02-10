/*
 * File:    sl_nmea_parser.c
 *
 * Created on 16. September 2017, 16:09
 *
 * Copyright (c) 2017 michael breuer <michael.breuer@ilsf.de>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define S_FUNCTION_NAME  sl_nmea_parser
#define S_FUNCTION_LEVEL 2


/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

#include "nmea0183.h"
#include "sl_nmea_parser.h"
#include "circularbuffer.h"

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S) {
    ssSetNumSFcnParams(S, 0); /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }
#endif

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 2)) return;
    if (!ssSetInputPortDimensionInfo(S, 0, DYNAMIC_DIMENSION)) {
        return;ssSetInputPortDimensionInfo(S, 0, DYNAMIC_DIMENSION);
    }
    //ssSetInputPortWidth(S, 0, serialVectorInputWidth);
    ssSetInputPortDataType(S, 0, SS_UINT8);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    ssSetInputPortWidth(S, 1, 1);
    ssSetInputPortDataType(S, 1, SS_UINT32);
    ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);

    if (!ssSetNumOutputPorts(S, 2)) return;
    /* status output */
    ssSetOutputPortWidth(S, 0, 19);
    ssSetOutputPortDataType(S, 0, SS_INT32);
    /* data output */
    ssSetOutputPortWidth(S, 1, 70);
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, IWORKSIZE);
    ssSetNumPWork(S, 2);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
}

/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);

}



#undef MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)

/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    In this function, you should initialize the continuous and discrete
 *    states for your S-function block.  The initial states are placed
 *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
 *    You can also perform any other initialization activities that your
 *    S-function may require. Note, this routine will be called at the
 *    start of simulation and if it is present in an enabled subsystem
 *    configured to reset states, it will be call when the enabled subsystem
 *    restarts execution to reset the states.
 */
static void mdlInitializeConditions(SimStruct *S) {
}
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 

/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S) {
    circularBuffer_t *cBuffer;
    nmea0183_bus_t *nmeaData;
    void **PWork = ssGetPWork(S);
    int * IWork = ssGetIWork(S);
    int i;
    uint32_t bufferSize = 0;

    /* input uint8/char, so size equals number of bytes */
    int_T rxDataWidth = ssGetInputPortWidth(S, 0);
    // 	if (rxDataWidth < 60) {
    // 		bufferSize = 256;
    // 	} else if (rxDataWidth > 2048) {
    // 		ssSetErrorStatus(S, "Wow, that's a lot!");
    //         return;
    // 	} else {
    // 		bufferSize = rxDataWidth;
    // 	}
    bufferSize = 524288;
    bufferSize = circularBufferCalculateBufferSize(bufferSize * 2);
    // cBuffer is a 'object' containing the real buffer (which is cBuffer->buffer) and additional values (mainly pointers/indexes)
    cBuffer = malloc(sizeof (circularBuffer_t));
    if (cBuffer != NULL) {
        cBuffer->buffer = malloc(bufferSize);
        if (cBuffer->buffer == NULL) {
            ssSetErrorStatus(S, "Error allocating buffer memory.");
            return;
        }
        cBuffer->messageStart = 0;
        cBuffer->messageEnd = 0;
        cBuffer->write = 0;
        cBuffer->size = bufferSize;
    } else {
        ssSetErrorStatus(S, "Error creating circular buffer.");
        return;
    }
    PWork[0] = cBuffer;

    nmeaData = malloc(sizeof (nmea0183_bus_t));
    if (nmeaData == NULL) {
        ssSetErrorStatus(S, "Error creating nmea data store.");
        return;
    }
    initialiseNmeaDataset(nmeaData);
    PWork[1] = nmeaData;

    /* initialize status counters in IWork vector!*/
    for (i = 0; i < IWORKSIZE; i++) {
        IWork[i] = 0;
    }

}
#endif /*  MDL_START */

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid) {
    circularBuffer_t *cBuffer;
    nmea0183_bus_t *nmeaData;
    long int *sentenceCounter;
    long int *crcErrorCounter;
    long int *bufferOverflow;
    long int *everBytes;
    long int *gbsCounter;
    long int *ggaCounter;
    long int *ggkCounter;
    long int *ggqCounter;
    long int *gllCounter;
    long int *gsaCounter;
    long int *gstCounter;
    long int *gsvCounter;
    long int *rmcCounter;
    long int *vtgCounter;
    long int *zdaCounter;
    //real_T *RWork;
    long int *IWork;
    /* input */
    const char *message = (char*) ssGetInputPortSignal(S, 0);
    const unsigned long int *receivedBytes = (unsigned long int*) ssGetInputPortSignal(S, 1);
    /* output */
    INT32_T *statusOutput = (INT32_T *) ssGetOutputPortSignal(S, 0);
    double *nmeaOutput = ssGetOutputPortRealSignal(S, 1);

    uint_T rxDataWidth = ssGetInputPortWidth(S, 0);
    if (receivedBytes[0] > rxDataWidth) {
        ssSetErrorStatus(S, "numRxData can't be greater than RxData port width.");
        return;
    }

    if (ssGetPWork(S) != NULL) {
        cBuffer = (circularBuffer_t *) ssGetPWorkValue(S, 0);
        if (cBuffer == NULL) {
            ssSetErrorStatus(S, "circular buffer not initialized.");
            return;
        }
        nmeaData = (nmea0183_bus_t *) ssGetPWorkValue(S, 1);
        if (nmeaData == NULL) {
            ssSetErrorStatus(S, "nmea data store not initialized.");
            return;
        }
    } else {
        ssWarning(S, "Pointer to PWork vector is NULL.");
    }

    if (ssGetIWork(S) != NULL) {
        IWork = (long int *) ssGetIWork(S);
        sentenceCounter = &(IWork[0]);
        crcErrorCounter = &(IWork[1]);
        bufferOverflow = &(IWork[2]);
        rmcCounter = &(IWork[3]);
        ggaCounter = &(IWork[4]);
        zdaCounter = &(IWork[5]);
        everBytes = &(IWork[6]);
        gllCounter = &(IWork[7]);
        gsaCounter = &(IWork[8]);
        gstCounter = &(IWork[9]);
        gsvCounter = &(IWork[10]);
        gbsCounter = &(IWork[11]);
        ggkCounter = &(IWork[12]);
        ggqCounter = &(IWork[13]);
        vtgCounter = &(IWork[14]);

    } else {
        ssSetErrorStatus(S, "Pointer to IWork vector is NULL.");
        return;
    }

    gnssWorker(cBuffer, message, receivedBytes[0], nmeaData, IWork);

    //cBuffer->messageStart = circularBufferIndexIncrease(cBuffer, cBuffer->write, 60);

    /* writing output */
    nmeaOutput[0] = (double) nmeaData->zdaData.gnssStatus;
    nmeaOutput[1] = (double) nmeaData->zdaData.utcDate.day;
    nmeaOutput[2] = (double) nmeaData->zdaData.utcDate.month;
    nmeaOutput[3] = (double) nmeaData->zdaData.utcDate.year;
    nmeaOutput[4] = (double) nmeaData->zdaData.utcTime.hour;
    nmeaOutput[5] = (double) nmeaData->zdaData.utcTime.minutes;
    nmeaOutput[6] = (double) nmeaData->zdaData.utcTime.seconds;
    nmeaOutput[7] = (double) nmeaData->zdaData.localTimezone.hourOffset;
    nmeaOutput[8] = (double) nmeaData->zdaData.localTimezone.minuteOffset;
    nmeaOutput[9] = (double) nmeaData->rmcData.gnssStatus;
    nmeaOutput[10] = (double) nmeaData->rmcData.utcDate.day;
    nmeaOutput[11] = (double) nmeaData->rmcData.utcDate.month;
    nmeaOutput[12] = (double) nmeaData->rmcData.utcDate.year;
    nmeaOutput[13] = (double) nmeaData->rmcData.utcTime.hour;
    nmeaOutput[14] = (double) nmeaData->rmcData.utcTime.minutes;
    nmeaOutput[15] = (double) nmeaData->rmcData.utcTime.seconds;
    nmeaOutput[16] = (double) nmeaData->rmcData.latitude;
    nmeaOutput[17] = (double) nmeaData->rmcData.latitudeAxis;
    nmeaOutput[18] = (double) nmeaData->rmcData.longitude;
    nmeaOutput[19] = (double) nmeaData->rmcData.longitudeAxis;
    nmeaOutput[20] = (double) nmeaData->rmcData.velocity;
    nmeaOutput[21] = (double) nmeaData->rmcData.trackAngle;
    nmeaOutput[22] = (double) nmeaData->rmcData.magneticVariation;
    nmeaOutput[23] = (double) nmeaData->rmcData.magneticAxis;
    nmeaOutput[24] = (double) nmeaData->rmcData.modeIndication;
    nmeaOutput[25] = (double) nmeaData->ggaData.gnssStatus;
    nmeaOutput[26] = (double) nmeaData->ggaData.utcTime.hour;
    nmeaOutput[27] = (double) nmeaData->ggaData.utcTime.minutes;
    nmeaOutput[28] = (double) nmeaData->ggaData.utcTime.seconds;
    nmeaOutput[29] = (double) nmeaData->ggaData.latitude;
    nmeaOutput[30] = (double) nmeaData->ggaData.latitudeAxis;
    nmeaOutput[31] = (double) nmeaData->ggaData.longitude;
    nmeaOutput[32] = (double) nmeaData->ggaData.longitudeAxis;
    nmeaOutput[33] = (double) nmeaData->ggaData.numberSatellites;
    nmeaOutput[34] = (double) nmeaData->ggaData.dilusionOfPrecision;
    nmeaOutput[35] = (double) nmeaData->ggaData.antennaAboveMeanSea;
    nmeaOutput[36] = (double) nmeaData->ggaData.geodialSeparation;
    nmeaOutput[37] = (double) nmeaData->ggaData.ageDGPS;
    nmeaOutput[38] = (double) nmeaData->ggaData.dgpsReferenceStation;
    nmeaOutput[39] = (double) nmeaData->gllData.latitude;
    nmeaOutput[40] = (double) nmeaData->gllData.latitudeAxis;
    nmeaOutput[41] = (double) nmeaData->gllData.longitude;
    nmeaOutput[42] = (double) nmeaData->gllData.longitudeAxis;
    nmeaOutput[43] = (double) nmeaData->gllData.utcTime.hour;
    nmeaOutput[44] = (double) nmeaData->gllData.utcTime.minutes;
    nmeaOutput[45] = (double) nmeaData->gllData.utcTime.seconds;
    nmeaOutput[46] = (double) nmeaData->gllData.gnssStatus;
    nmeaOutput[47] = (double) nmeaData->vtgData.trueTrackMadeGood;
    nmeaOutput[48] = (double) nmeaData->vtgData.unitTrueTrackMadeGood;
    nmeaOutput[49] = (double) nmeaData->vtgData.magneticTrackMadeGood;
    nmeaOutput[50] = (double) nmeaData->vtgData.unitMagneticTrackMadeGood;
    nmeaOutput[51] = (double) nmeaData->vtgData.groundSpeedKnots;
    nmeaOutput[52] = (double) nmeaData->vtgData.unitGroundSpeedKnots;
    nmeaOutput[53] = (double) nmeaData->vtgData.groundSpeedKph;
    nmeaOutput[54] = (double) nmeaData->vtgData.unitGroundSpeedKph;
    nmeaOutput[55] = (double) nmeaData->vtgData.modeIndication;
    nmeaOutput[56] = (double) nmeaData->ggqData.gnssStatus;
    nmeaOutput[57] = (double) nmeaData->ggqData.utcTime.hour;
    nmeaOutput[58] = (double) nmeaData->ggqData.utcTime.minutes;
    nmeaOutput[59] = (double) nmeaData->ggqData.utcTime.seconds;
    nmeaOutput[60] = (double) nmeaData->ggqData.utcDate.day;
    nmeaOutput[61] = (double) nmeaData->ggqData.utcDate.month;
    nmeaOutput[62] = (double) nmeaData->ggqData.utcDate.year;
    nmeaOutput[63] = (double) nmeaData->ggqData.latitude;
    nmeaOutput[64] = (double) nmeaData->ggqData.latitudeAxis;
    nmeaOutput[65] = (double) nmeaData->ggqData.longitude;
    nmeaOutput[66] = (double) nmeaData->ggqData.longitudeAxis;
    nmeaOutput[67] = (double) nmeaData->ggqData.numberSatellites;
    nmeaOutput[68] = (double) nmeaData->ggqData.coordinateQuality;
    nmeaOutput[69] = (double) nmeaData->ggqData.antennaAboveMeanSea;

    /* status output */
    statusOutput[0] = (INT32_T) cBuffer->size;
    statusOutput[1] = (INT32_T) circularBufferDataLength(cBuffer);
    statusOutput[2] = (INT32_T) (100 * circularBufferDataLength(cBuffer) / cBuffer->size); // percentage buffer used
    statusOutput[3] = (INT32_T) cBuffer->write;
    statusOutput[4] = (INT32_T) * bufferOverflow;
    statusOutput[5] = (INT32_T) * everBytes;
    statusOutput[6] = (INT32_T) * sentenceCounter; // counter parsed nmea nessages
    statusOutput[7] = (INT32_T) * crcErrorCounter;
    statusOutput[8] = (INT32_T) * rmcCounter;
    statusOutput[9] = (INT32_T) * ggaCounter;
    statusOutput[10] = (INT32_T) * zdaCounter;
    statusOutput[11] = (INT32_T) * gllCounter;
    statusOutput[12] = (INT32_T) * gsaCounter;
    statusOutput[13] = (INT32_T) * gstCounter;
    statusOutput[14] = (INT32_T) * gsvCounter;
    statusOutput[15] = (INT32_T) * gbsCounter;
    statusOutput[16] = (INT32_T) * ggkCounter;
    statusOutput[17] = (INT32_T) * ggqCounter;
    statusOutput[18] = (INT32_T) * vtgCounter;
}



#undef MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)

/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is useful
 *    for performing any tasks that should only take place once per
 *    integration step.
 */
static void mdlUpdate(SimStruct *S, int_T tid) {
}
#endif /* MDL_UPDATE */



#undef MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)

/* Function: mdlDerivatives =================================================
 * Abstract:
 *    In this function, you compute the S-function block's derivatives.
 *    The derivatives are placed in the derivative vector, ssGetdX(S).
 */
static void mdlDerivatives(SimStruct *S) {
}
#endif /* MDL_DERIVATIVES */

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO

/* Function: mdlSetInputPortDimensionInfo ====================================
 * Abstract:
 *    This routine is called with the candidate dimensions for an input port
 *    with unknown dimensions. If the proposed dimensions are acceptable, the
 *    routine should go ahead and set the actual port dimensions.
 *    If they are unacceptable an error should be generated via
 *    ssSetErrorStatus.
 *    Note that any other input or output ports whose dimensions are
 *    implicitly defined by virtue of knowing the dimensions of the given port
 *    can also have their dimensions set.
 */
static void mdlSetInputPortDimensionInfo(SimStruct *S,
        int_T port,
        const DimsInfo_T *dimsInfo) {
    //     size_t  pWidth          = mxGetNumberOfElements(PARAM_ARG);
    //     size_t  pSize           = mxGetNumberOfDimensions(PARAM_ARG);
    //     const size_t  *pDims    = mxGetDimensions(PARAM_ARG);
    //     
    //     int_T  uNumDims   = dimsInfo->numDims;
    //     int_T  uWidth     = dimsInfo->width;
    //     int32_T  *uDims   = dimsInfo->dims;
    //     
    //     int_T numDims = 0;
    boolean_T isOk = true;
    //     int_T iParam = 0;
    //     
    /* Set input port dimension */
    if (!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;

    /*
     * The block only accepts 1-D signals. Check number of dimensions.
     */
    isOk = (dimsInfo->numDims == 1);
    //     numDims = (pSize != (size_t)uNumDims) ? numDims : uNumDims;
    //    
    //     if(isOk && pWidth > 1 && uWidth > 1){
    //         for ( iParam = 0; iParam < numDims; iParam++ ) {
    //             isOk = (pDims[iParam] == (size_t)(uDims[iParam]));
    //             if(!isOk) break;
    //         }
    //     }

    if (!isOk) {
        ssSetErrorStatus(S, "Invalid input port dimensions. The input signal must be"
                "a 1-D vector signal same dimensions as the parameter dimensions.");
        return;
    }
} /* end mdlSetInputPortDimensionInfo */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO

/* Function: mdlSetOutputPortDimensionInfo ===================================
 * Abstract:
 *    This routine is called with the candidate dimensions for an output port
 *    with unknown dimensions. If the proposed dimensions are acceptable, the
 *    routine should go ahead and set the actual port dimensions.
 *    If they are unacceptable an error should be generated via
 *    ssSetErrorStatus.
 *    Note that any other input or output ports whose dimensions are
 *    implicitly defined by virtue of knowing the dimensions of the given
 *    port can also have their dimensions set.
 */
static void mdlSetOutputPortDimensionInfo(SimStruct *S,
        int_T port,
        const DimsInfo_T *dimsInfo) {
    /* The block only accepts 2-D or n-D signals. Check number of dimensions. */
    if (dimsInfo->numDims != 1) {
        ssSetErrorStatus(S, "Invalid output port dimensions. The output signal "
                "must be a 1-D signal.");
        return;
    } else {
        /* Set the input port dimensions */
        if (!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
    }
} /* end mdlSetOutputPortDimensionInfo */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO

/* Function: mdlSetDefaultPortDimensionInfo ====================================
 *    This routine is called when Simulink is not able to find dimension
 *    candidates for ports with unknown dimensions. This function must set the
 *    dimensions of all ports with unknown dimensions.
 */
static void mdlSetDefaultPortDimensionInfo(SimStruct *S) {
    int_T rxDataWidth = ssGetInputPortWidth(S, 0);
    /* Input port dimension must be unknown. Set it to scalar. */
    if (rxDataWidth == DYNAMICALLY_SIZED) {
        /* Input dimensions are unknown. Set it to default value. */
        ssSetInputPortWidth(S, 0, 64);
    }
} /* end mdlSetDefaultPortDimensionInfo */
#endif /* MATLAB_MEX_FILE */

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S) {

    if (ssGetPWork(S) != NULL) {
        circularBuffer_t * cBuffer = (circularBuffer_t *) ssGetPWorkValue(S, 0);
        if (cBuffer != NULL) {
            if (cBuffer->buffer != NULL) {
                free(cBuffer->buffer);
            }
            free(cBuffer);
            cBuffer = NULL;
        }
        ssSetPWorkValue(S, 0, NULL);

        nmea0183_bus_t * nmeaData = (nmea0183_bus_t *) ssGetPWorkValue(S, 1);
        if (nmeaData != NULL) {
            free(nmeaData);
            nmeaData = NULL;
        }
        ssSetPWorkValue(S, 1, NULL);
    }
}

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
