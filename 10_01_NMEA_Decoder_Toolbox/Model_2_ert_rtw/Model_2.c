/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_2.c
 *
 * Code generated for Simulink model 'Model_2'.
 *
 * Model version                  : 1.22
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Wed Apr 11 14:13:57 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Model_2.h"
#include "Model_2_private.h"
#include "Model_2_dt.h"

/* Block signals (auto storage) */
B_Model_2_T Model_2_B;

/* Block states (auto storage) */
DW_Model_2_T Model_2_DW;

/* Real-time model */
RT_MODEL_Model_2_T Model_2_M_;
RT_MODEL_Model_2_T *const Model_2_M = &Model_2_M_;

/* Model step function */
void Model_2_step(void)
{
  int16_T a_data;
  int16_T ii_data;
  int32_T b_ii;
  boolean_T p;
  boolean_T p_0;
  int32_T i;
  int32_T ii_size_idx_0;
  boolean_T exitg1;

  /* MATLABSystem: '<Root>/Serial Read' */
  p = false;
  p_0 = true;
  if (!(Model_2_DW.obj.SampleTime == Model_2_P.SerialRead_SampleTime)) {
    p_0 = false;
  }

  if (p_0) {
    p = true;
  }

  if (!p) {
    Model_2_DW.obj.SampleTime = Model_2_P.SerialRead_SampleTime;
  }

  Model_2_B.SerialRead_o2 = MW_SCI_Receive(Model_2_DW.obj.MW_SCIHANDLE,
    Model_2_B.RxDataLocChar, 300U);
  memcpy((void *)&Model_2_B.RxData[0], (void *)&Model_2_B.RxDataLocChar[0],
         (uint32_T)((size_t)300 * sizeof(uint8_T)));
  for (i = 0; i < 300; i++) {
    Model_2_B.SerialRead_o1[i] = Model_2_B.RxData[i];

    /* MATLAB Function: '<Root>/MATLAB Function' */
    Model_2_B.x[i] = (Model_2_B.SerialRead_o1[i] > 0);
  }

  /* End of MATLABSystem: '<Root>/Serial Read' */

  /* MATLAB Function: '<Root>/MATLAB Function' */
  i = 0;
  ii_size_idx_0 = 1;
  b_ii = 300;
  exitg1 = false;
  while ((!exitg1) && (b_ii > 0)) {
    if (Model_2_B.x[b_ii - 1]) {
      i = 1;
      ii_data = (int16_T)b_ii;
      exitg1 = true;
    } else {
      b_ii--;
    }
  }

  if (i == 0) {
    ii_size_idx_0 = 0;
  }

  if (0 <= ii_size_idx_0 - 1) {
    memcpy(&a_data, &ii_data, ii_size_idx_0 * sizeof(int16_T));
  }

  if (ii_size_idx_0 == 0) {
    a_data = 0;
  }

  Model_2_B.number_of_new_bytes = (uint32_T)a_data;

  /* S-Function (sl_nmea_parser): '<Root>/NMEA Decoder' */

  /* Level2 S-Function Block: '<Root>/NMEA Decoder' (sl_nmea_parser) */
  {
    SimStruct *rts = Model_2_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.1s, 0.0s] */
    rtExtModeUpload(0, Model_2_M->Timing.t[0]);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(Model_2_M)!=-1) &&
        !((rtmGetTFinal(Model_2_M)-Model_2_M->Timing.t[0]) > Model_2_M->
          Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(Model_2_M, "Simulation finished");
    }

    if (rtmGetStopRequested(Model_2_M)) {
      rtmSetErrorStatus(Model_2_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  Model_2_M->Timing.t[0] =
    (++Model_2_M->Timing.clockTick0) * Model_2_M->Timing.stepSize0;
}

/* Model initialize function */
void Model_2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Model_2_M, 0,
                sizeof(RT_MODEL_Model_2_T));
  rtsiSetSolverName(&Model_2_M->solverInfo,"FixedStepDiscrete");
  Model_2_M->solverInfoPtr = (&Model_2_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Model_2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    Model_2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Model_2_M->Timing.sampleTimes = (&Model_2_M->Timing.sampleTimesArray[0]);
    Model_2_M->Timing.offsetTimes = (&Model_2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Model_2_M->Timing.sampleTimes[0] = (0.1);

    /* task offsets */
    Model_2_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(Model_2_M, &Model_2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Model_2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    Model_2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Model_2_M, -1);
  Model_2_M->Timing.stepSize0 = 0.1;

  /* External mode info */
  Model_2_M->Sizes.checksums[0] = (1877680218U);
  Model_2_M->Sizes.checksums[1] = (553317053U);
  Model_2_M->Sizes.checksums[2] = (571600027U);
  Model_2_M->Sizes.checksums[3] = (2490956751U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    Model_2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Model_2_M->extModeInfo,
      &Model_2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Model_2_M->extModeInfo, Model_2_M->Sizes.checksums);
    rteiSetTPtr(Model_2_M->extModeInfo, rtmGetTPtr(Model_2_M));
  }

  Model_2_M->solverInfoPtr = (&Model_2_M->solverInfo);
  Model_2_M->Timing.stepSize = (0.1);
  rtsiSetFixedStepSize(&Model_2_M->solverInfo, 0.1);
  rtsiSetSolverMode(&Model_2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  (void) memset(((void *) &Model_2_B), 0,
                sizeof(B_Model_2_T));

  /* states (dwork) */
  (void) memset((void *)&Model_2_DW, 0,
                sizeof(DW_Model_2_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Model_2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &Model_2_M->NonInlinedSFcns.sfcnInfo;
    Model_2_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(Model_2_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &Model_2_M->Sizes.numSampTimes);
    Model_2_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(Model_2_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,Model_2_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(Model_2_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(Model_2_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(Model_2_M));
    rtssSetStepSizePtr(sfcnInfo, &Model_2_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(Model_2_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &Model_2_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &Model_2_M->zCCacheNeedsReset);
    rtssSetContTimeOutputInconsistentWithStateAtMajorStepPtr(sfcnInfo,
      &Model_2_M->CTOutputIncnstWithState);
    rtssSetSampleHitsPtr(sfcnInfo, &Model_2_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &Model_2_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &Model_2_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &Model_2_M->solverInfoPtr);
  }

  Model_2_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&Model_2_M->NonInlinedSFcns.childSFunctions[0], 0,
                  1*sizeof(SimStruct));
    Model_2_M->childSfunctions = (&Model_2_M->
      NonInlinedSFcns.childSFunctionPtrs[0]);
    Model_2_M->childSfunctions[0] = (&Model_2_M->
      NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: Model_2/<Root>/NMEA Decoder (sl_nmea_parser) */
    {
      SimStruct *rts = Model_2_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = Model_2_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = Model_2_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = Model_2_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      {
        ssSetBlkInfo2Ptr(rts, &Model_2_M->NonInlinedSFcns.blkInfo2[0]);
      }

      _ssSetBlkInfo2PortInfo2Ptr(rts,
        &Model_2_M->NonInlinedSFcns.inputOutputPortInfo2[0]);

      /* Set up the mdlInfo pointer */
      ssSetRTWSfcnInfo(rts, Model_2_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &Model_2_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &Model_2_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &Model_2_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &Model_2_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &Model_2_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 2);
        ssSetPortInfoForInputs(rts,
          &Model_2_M->NonInlinedSFcns.Sfcn0.inputPortInfo[0]);
        _ssSetPortInfo2ForInputUnits(rts,
          &Model_2_M->NonInlinedSFcns.Sfcn0.inputPortUnits[0]);
        ssSetInputPortUnit(rts, 0, 0);
        ssSetInputPortUnit(rts, 1, 0);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0, Model_2_B.SerialRead_o1);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 300);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1, &Model_2_B.number_of_new_bytes);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &Model_2_M->NonInlinedSFcns.Sfcn0.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 2);
        _ssSetPortInfo2ForOutputUnits(rts,
          &Model_2_M->NonInlinedSFcns.Sfcn0.outputPortUnits[0]);
        ssSetOutputPortUnit(rts, 0, 0);
        ssSetOutputPortUnit(rts, 1, 0);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 19);
          ssSetOutputPortSignal(rts, 0, ((int32_T *) Model_2_B.NMEADecoder_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 70);
          ssSetOutputPortSignal(rts, 1, ((real_T *) Model_2_B.NMEADecoder_o2));
        }
      }

      /* path info */
      ssSetModelName(rts, "NMEA Decoder");
      ssSetPath(rts, "Model_2/NMEA Decoder");
      ssSetRTModel(rts,Model_2_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* work vectors */
      ssSetIWork(rts, (int_T *) &Model_2_DW.NMEADecoder_IWORK[0]);
      ssSetPWork(rts, (void **) &Model_2_DW.NMEADecoder_PWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &Model_2_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &Model_2_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 2);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 15);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &Model_2_DW.NMEADecoder_IWORK[0]);

        /* PWORK */
        ssSetDWorkWidth(rts, 1, 2);
        ssSetDWorkDataType(rts, 1,SS_POINTER);
        ssSetDWorkComplexSignal(rts, 1, 0);
        ssSetDWork(rts, 1, &Model_2_DW.NMEADecoder_PWORK[0]);
      }

      /* registration */
      sl_nmea_parser(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.1);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetInputPortWidth(rts, 0, 300);
      ssSetInputPortDataType(rts, 0, SS_UINT8);
      ssSetInputPortComplexSignal(rts, 0, 0);
      ssSetInputPortFrameData(rts, 0, 0);
      ssSetInputPortUnit(rts, 0, 0);
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
    }
  }

  {
    codertarget_raspi_internal_SC_T *obj;
    uint32_T RxPinLoc;
    uint32_T TxPinLoc;
    char_T SCIModuleLoc[13];
    MW_SCI_StopBits_Type StopBitsValue;
    MW_SCI_Parity_Type ParityValue;
    static const char_T tmp[12] = { '/', 'd', 'e', 'v', '/', 't', 't', 'y', 'A',
      'C', 'M', '0' };

    int32_T i;

    /* Start for MATLABSystem: '<Root>/Serial Read' */
    Model_2_DW.obj.isInitialized = 0;
    Model_2_DW.obj.SampleTime = Model_2_P.SerialRead_SampleTime;
    obj = &Model_2_DW.obj;
    Model_2_DW.obj.isInitialized = 1;
    RxPinLoc = MW_UNDEFINED_VALUE;
    TxPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      SCIModuleLoc[i] = tmp[i];
    }

    SCIModuleLoc[12] = '\x00';
    obj->MW_SCIHANDLE = MW_SCI_Open(SCIModuleLoc, true, RxPinLoc, TxPinLoc);
    MW_SCI_SetBaudrate(Model_2_DW.obj.MW_SCIHANDLE, 115200U);
    StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(Model_2_DW.obj.MW_SCIHANDLE, 8U, ParityValue,
                          StopBitsValue);

    /* End of Start for MATLABSystem: '<Root>/Serial Read' */
    /* Start for S-Function (sl_nmea_parser): '<Root>/NMEA Decoder' */
    /* Level2 S-Function Block: '<Root>/NMEA Decoder' (sl_nmea_parser) */
    {
      SimStruct *rts = Model_2_M->childSfunctions[0];
      sfcnStart(rts);
      if (ssGetErrorStatus(rts) != (NULL))
        return;
    }
  }
}

/* Model terminate function */
void Model_2_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Serial Read' */
  if (Model_2_DW.obj.isInitialized == 1) {
    Model_2_DW.obj.isInitialized = 2;
    MW_SCI_Close(Model_2_DW.obj.MW_SCIHANDLE);
  }

  /* End of Terminate for MATLABSystem: '<Root>/Serial Read' */

  /* Terminate for S-Function (sl_nmea_parser): '<Root>/NMEA Decoder' */
  /* Level2 S-Function Block: '<Root>/NMEA Decoder' (sl_nmea_parser) */
  {
    SimStruct *rts = Model_2_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
