/*
 * File:    nmea_demo.c
 * 
 * NMEA standalone demo application
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nmea0183.h"
#include "nmea0183.h"
#include "sl_nmea_parser.h"

#define MINBUFFSIZE  40960 //1048576 //65540 

/**
 * \brief main function for standalone gnss parser application
 * 
 * @param argc
 * @param argv
 * @return status code
 */
int main(int argc, char** argv) {
    FILE *fhandle;
    FILE *fouthandle;
/*
    double lastSec = -1;
*/
    int ccla = 0;
    int i = 0;
    circularBuffer_t *cBuffer;
    nmea0183_bus_t *nmeaData;
    long int *IWork;
    uint8_t message[64];
    uint32_t bufferSize = 0;
    /** minimum required buffer size */
    uint32_t minimumBufferSize = MINBUFFSIZE * sizeof (uint8_t);

/*
    InitGnss();
*/

    /*
     * peparation: get memory etc.
     */
    bufferSize = circularBufferCalculateBufferSize(minimumBufferSize); /**< calculate buffer size */
    // cBuffer is a 'object' containing the real buffer (which is cBuffer->buffer) and additional values (mainly pointers/indexes)
    cBuffer = malloc(sizeof (circularBuffer_t));
    if (cBuffer != NULL) {
        cBuffer->buffer = malloc(bufferSize);
        if (cBuffer->buffer == NULL) {
            free(cBuffer);
            cBuffer = NULL;
            return (EXIT_FAILURE);
        }
        cBuffer->messageStart = 0;
        cBuffer->messageEnd = 0;
        cBuffer->write = 0;
        cBuffer->size = bufferSize;
    } else {
        return (EXIT_FAILURE);
    }
    nmeaData = malloc(sizeof (nmea0183_bus_t));
    if (nmeaData == NULL) {
        return (EXIT_FAILURE);
    }
/*
    initialiseNmeaDataset(nmeaData);
*/
    IWork = malloc(IWORKSIZE * sizeof (long int));
    /* initialize status counters in IWork vector!*/
    for (i = 0; i < IWORKSIZE; i++) {
        IWork[i] = 0;
    }

    fhandle = fopen("sampleData/sept_add.log", "r");
    if (fhandle == NULL) {
        printf("error opening file!");
        return (EXIT_FAILURE);
    }

    /*
     * output file
     */
    fouthandle = fopen("parserOutput.txt", "w");
    if (fouthandle == NULL) {
        printf("error opening output file!");
        return (EXIT_FAILURE);
    }

    do {
        i = 0;
        //receivedBytes < 64
        uint32_t receivedBytes = 10 + (rand() % 5);
        while (i < receivedBytes && (ccla = fgetc(fhandle)) != EOF) {
            message[i] = (uint8_t) ccla;
            i++;
        }
        if (ccla == EOF) {
            /** if we reached end of file there are likely less than receivedBytes in buffer.
             * it's i+1 'cause we started i at 0!
             */
            receivedBytes = i + 1;
        }
        gnssWorker(cBuffer, message, receivedBytes, nmeaData, IWork); /**< parsing step */
        //printf("GGA: %i - %i:%i:%i %f %f %i %f\n", nmeaData->ggaData.gnssStatus, nmeaData->ggaData.utcTime.hour, nmeaData->ggaData.utcTime.minutes, nmeaData->ggaData.utcTime.seconds, nmeaData->ggaData.latitude, nmeaData->ggaData.longitude, nmeaData->ggaData.numberSatellites, nmeaData->ggaData.antennaAboveMeanSea);
        //printf("Hour: %i, Minute: %i, Second: %f Lat: %f Lon: %f\n", nmeaData->ggaData.utcTime.hour, nmeaData->ggaData.utcTime.minutes, nmeaData->ggaData.utcTime.seconds, nmeaData->ggaData.latitude, nmeaData->ggaData.longitude);
        //if (nmeaData->ggaData.antennaAboveMeanSea > 500 || nmeaData->ggaData.antennaAboveMeanSea < 100) {
        //printf("GGA height: %f\n", nmeaData->ggaData.antennaAboveMeanSea);
        //}
        if (nmeaData->rmcData.latitude > 55 || nmeaData->rmcData.latitude < 50 || nmeaData->rmcData.longitude < 5 || nmeaData->rmcData.longitude > 6) {
            fprintf(fouthandle, "%u, %u, %f, ", nmeaData->rmcData.utcTime.hour, nmeaData->rmcData.utcTime.minutes, nmeaData->rmcData.utcTime.seconds);
            fprintf(fouthandle, "%u, ", nmeaData->rmcData.gnssStatus);
            fprintf(fouthandle, "%f, %f, ", nmeaData->rmcData.latitude, nmeaData->rmcData.longitude);
            fprintf(fouthandle, "%f\n", nmeaData->rmcData.trackAngle);
        }
    } while (ccla != EOF);

    printf("***** GENERAL INFORMATION ******\n\r");
    printf("buffer bytes: %i, buffer overflow: %ld\n\r", circularBufferDataLength(cBuffer), IWork[2]);
    printf("NMEA: message count: %ld, crc error count: %ld\n\r", IWork[0], IWork[1]);
    printf("********************************\n\r");
    printf("***** NMEA message count *******\n\r");
    printf("RMC: %ld\n\rGGA: %ld\n\rZDA: %ld\n\rGLL: %ld\n\rGSA: %ld\n\rGST: %ld\n\rGSV: %ld\n\rGBS: %ld\n\rGGK: %ld\n\rGGQ: %ld\n\rVTG: %ld\n\r", IWork[3], IWork[4], IWork[5], IWork[7], IWork[8], IWork[9], IWork[10], IWork[11], IWork[12], IWork[13], IWork[14]);
    printf("day: %u, month: %u, year: %u \n\r", nmeaData->zdaData.utcDate.day, nmeaData->zdaData.utcDate.month, nmeaData->zdaData.utcDate.year);
    printf("********************************\n\r");

    /**
     * \brief clean shutdown
     * 
     * free allocated memory etc. before program termination.
     */
    fclose(fhandle);
    fclose(fouthandle);
    if (cBuffer != NULL) {
        if (cBuffer->buffer != NULL) {
            free(cBuffer->buffer);
        }
        free(cBuffer);
        cBuffer = NULL;
    }
    if (nmeaData != NULL) {
        free(nmeaData);
        nmeaData = NULL;
    }

    return (EXIT_SUCCESS);
}
