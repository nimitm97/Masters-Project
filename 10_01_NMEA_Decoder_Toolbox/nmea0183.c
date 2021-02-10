/*
 * File:    nmea0183.c
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

#include <math.h>
#include <stdlib.h>

#include "circularbuffer.h"
#include "gnss_constants.h"
#include "basic_datatypes.h"
#include "nmea0183.h"

/*****************************************************************************
 * 
 * timestamp operations
 * 
 *****************************************************************************/

/**
 * Comparison of two gnss timestamps a and b. Checks identity of two double's
 * time resolution of gps is 0.01 sec
 * 
 * @param a gnssTime_t timestamp
 * @param b gnssTime_t timestamp
 * @return returns 1 if timestamps are isochronous, 0 if they are NOT isochronous and -1 on error.
 */
/*
static int gnssMessageIsochronous(nmea_time_t a, nmea_time_t b) {
*/
    /* maximum speed CargoMover: 80 km/h = 22.222 m/s
     * maximum error in 0.01 sec: 0.22 meter
     */
/*
    const double gnssTimeEps = 0.01;

    if (a.hour == b.hour && a.minutes == b.minutes) {
        // now check the seconds
        if (fabs(a.seconds - b.seconds) < gnssTimeEps)
            return 1;
        else
            return 0;
    } else {
        // not the same hour or minute
        return 0;
    }

    // there was an error
    //return -1;
}
*/

/*****************************************************************************
 * 
 * NMEA sentence operations
 * 
 *****************************************************************************/

/** convert ascii to utc timestamp
 * 
 * datafield array should be 6 or 9 characters long
 * 
 * @param[in] datafield char array containing data
 * @param[in] length
 * @param[out] timestamp
 */
static void convertUtcTime(char datafield[], int length, nmea_time_t *timestamp) {
    /* horrible compiler @ matlab */
    //const int hourDigits = 2;
    //const int minuteDigits = 2;
    //const int secondDigits = 15;
#define hourDigits 2
#define minuteDigits 2
#define secondDigits 15
    char hour[hourDigits + 1];
    char minute[minuteDigits + 1];
    char second[secondDigits + 1];
    int i;

    hour[hourDigits] = '\0';
    minute[minuteDigits] = '\0';
    second[secondDigits] = '\0';

    for (i = 0; i < hourDigits; i++) {
        hour[i] = datafield[i];
    }
    for (i = hourDigits; i < (hourDigits + minuteDigits); i++) {
        minute[i - hourDigits] = datafield[i];
    }
    for (i = (hourDigits + minuteDigits); i < length; i++) {
        second[i - (hourDigits + minuteDigits)] = datafield[i];
    }
    if ((secondDigits + minuteDigits + hourDigits) > length) {
        second[(length - hourDigits - minuteDigits)] = '\0';
    }

    timestamp->hour = atoi(hour);
    timestamp->minutes = atoi(minute);
    timestamp->seconds = atof(second);
}

/** convert ascii to utc datestamp
 * 
 * datafield array should be 6 or 8 characters long
 * @param[in] datafield
 * @param[in] length
 * @param[in] datestamp
 */
static void convertUtcDate(char datafield[], int length, nmea_date_t *datestamp) {
    char day[2];
    char month[2];
    char year[4];
    int i;

    for (i = 0; i < 2; i++) {
        day[i] = datafield[i];
    }
    for (i = 2; i < 4; i++) {
        month[i - 2] = datafield[i];
    }
    for (i = 4; i < (length); i++) {
        year[i - 4] = datafield[i];
    }
    if (6 == length) {
        year[2] = '\0';
    }

    datestamp->year = atoi(year);
    datestamp->month = atoi(month);
    datestamp->day = atoi(day);
}

/** worker function to convert ascii (degree + minutes) to degree as number
 * 
 * \warning {allowed values for variable split: 2 or 3}
 * 
 * @param[in] datafield
 * @param[in] length
 * @param[in] degree/minute split index
 * @return the converted value in degree as double
 */
static double convertDegree(char datafield[], int length, unsigned short int split) {
    char degreeChar[4] = {0};
    char minuteChar[25] = {0};
    double degree = 0;
    int i = 0;

    /*
     * this function is valid only for split values 2 or 3!
     */
    if (split < 2 || split > 3) {
        return 0.0;
    }

    for (i = 0; i < split; i++) {
        degreeChar[i] = datafield[i];
    }
    degreeChar[split] = '\0';
    for (i = split; i < length; i++) {
        minuteChar[i - split] = datafield[i];
    }
    minuteChar[length - split] = '\0';

    degree = atof(degreeChar) + atof(minuteChar) / 60;
    return degree;
}

/** convert ascii to latitude
 * 
 * @see convertDegree()
 * @param[in] datafield
 * @param[in] length
 * @return converted value of latitude position
 */
static double convertLatitude(char datafield[], int length) {
    double latitude;

    latitude = convertDegree(datafield, length, 2);
    return (latitude);
}

/** convert ascii to longitude
 * 
 * @see convertDegree()
 * @param[in] datafield
 * @param[in] length
 * @return converted value of longitude position
 */
static double convertLongitude(char datafield[], int length) {
    double longitude;

    longitude = convertDegree(datafield, length, 3);
    return (longitude);
}

/**
 * convert single ascii axis character to axis value
 * @param[in] axisdir
 * @return enum coordAxis_t
 */
static coordAxis_t convertAxis(char axisdir) {
    switch (axisdir) {
        case 'n':
        case 'N':
        {
            return (axisNorth);
        }
        case 's':
        case 'S':
        {
            return (axisSouth);
        }
        case 'e':
        case 'E':
        {
            return (axisEast);
        }
        case 'w':
        case 'W':
        {
            return (axisWest);
        }
        default:
        {
            return (axisUNKNOWN);
        }
    }
    /** \note {matlab/dSpace's excellent compiler requires this as default return value. this code will NEVER be executed. } */
/*
    return (axisUNKNOWN);
*/
}

/**
 * \brief NMEA sentence handling for: RMC
 * 
 * @param[in] cBuffer
 * @param[out] rmcData
 */
static void processRMC(circularBuffer_t *cBuffer, nmea_rmc_t *rmcData) {
    const int numberOfFields = 11;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field of RMC sentence is UTC time
                 */
            case 0:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer) || 9 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcTime(field, circularBufferNMEADatafieldLength(cBuffer), &(rmcData->utcTime));
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 2nd field is status
                 */
            case 1:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /**
                     * \TODO list all possible cases.
                     */
                    switch (field[0]) {
                        case 'a':
                        case 'A':
                        {
                            rmcData->gnssStatus = STATUS_FIX;
                            break;
                        }
                        case 'v':
                        case 'V':
                        {
                            rmcData->gnssStatus = STATUS_NO_FIX;
                            break;
                        }
                        default:
                        {
                            rmcData->gnssStatus = STATUS_NO_FIX;
                        }
                    }
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 3rd field is latitude
                 */
            case 2:
            {
                if (8 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->latitude = convertLatitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 4th field is North/South
                 */
            case 3:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->latitudeAxis = convertAxis(field[0]);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 5th field is longitude
                 */
            case 4:
            {
                if (9 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->longitude = convertLongitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 6th field is East/West
                 */
            case 5:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->longitudeAxis = convertAxis(field[0]);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 7th field is speed over ground
                 * 
                 * the unit of the value in this field is knots. but in our data structures we use si-unit meter per second.
                 */
            case 6:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 15 > circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->velocity = atoi(field) * KNOTS_TO_MPS;
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 8th field is track angle (degrees)
                 */
            case 7:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 15 > circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->trackAngle = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 9th field is date
                 */
            case 8:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcDate(field, circularBufferNMEADatafieldLength(cBuffer), &(rmcData->utcDate));
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 10 field is magnetic variation
                 */
            case 9:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 15 > circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->magneticVariation = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 11 field is magnetic
                 */
            case 10:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    rmcData->magneticAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 12 field is mode indication
                 *
                 * mode indicator (new in NMEA 2.3): The value can be A=autonomous, 
                 * D=differential, E=Estimated, N=not valid, S=Simulator. 
                 * 
                 * Sometimes there can be a null value as well. Only the A and D 
                 * values will correspond to an Active and reliable Sentence.
                 */
            case 11:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse mode indication */
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /* what to do? */
        //rmcData->gnssStatus = 0;
    }
    return;
}

/**
 * \brief NMEA sentence handling for: GGA
 * 
 * @param[in] cBuffer
 * @param[out] ggaData
 */
static void processGGA(circularBuffer_t *cBuffer, nmea_gga_t *ggaData) {
    const int numberOfFields = 14;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field is UTC time
                 */
            case 0:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer) || 9 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcTime(field, circularBufferNMEADatafieldLength(cBuffer), &(ggaData->utcTime));
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 2nd field is latitude
                 */
            case 1:
            {
                if (8 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->latitude = convertLatitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 3rd field is North/South
                 */
            case 2:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->latitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 4th field is longitude
                 */
            case 3:
            {
                if (9 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->longitude = convertLongitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 5th field is East/West
                 */
            case 4:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->longitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 6th field is gps quality
                 */
            case 5:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->gnssStatus = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 7th field is number of satellites
                 */
            case 6:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->numberSatellites = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 8th field is dilution of precision
                 */
            case 7:
            {
                if (3 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->dilusionOfPrecision = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 9th field is antenna height above mean sea level
                 */
            case 8:
            {
                if (1 < circularBufferNMEADatafieldLength(cBuffer) && 12 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->antennaAboveMeanSea = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 10 field is unit antenna height
                 */
            case 9:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* @TODO do ascii parsing */
                    if (field[0] == 'M') {
                        ggaData->unitAntennaHeight = 1;
                    } else {
                        ggaData->unitAntennaHeight = 0;
                    }
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 11 field is geodial separation
                 */
            case 10:
            {
                if (4 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->geodialSeparation = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 12 field is unit of geodial separation
                 */
            case 11:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* @TODO do ascii parsing */
                    if (field[0] == 'M') {
                        ggaData->unitGeodialSeparation = 1;
                    } else {
                        ggaData->unitGeodialSeparation = 0;
                    }
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * (optional) 13 field is age of DGPS data
                 */
            case 12:
            {
                if (3 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggaData->ageDGPS = atof(field);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    //ggaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * (optional) 14 field is dgps reference station number
                 */
            case 13:
            {
                if (4 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* @TODO do ascii parsing: right data format? is it double or int? */
                    ggaData->dgpsReferenceStation = atof(field);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    ggaData->gnssStatus = 0;
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /* what to do? */
        //ggaData->gnssStatus = 0;
    }
    return;
}

/**
 * \brief NMEA sentence handling for: GGQ
 * 
 * @param[in] cBuffer
 * @param[out] ggqData
 */
static void processGGQ(circularBuffer_t *cBuffer, nmea_ggq_t *ggqData) {
    const int numberOfFields = 11;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field is UTC time
                 */
            case 0:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer) || 9 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcTime(field, circularBufferNMEADatafieldLength(cBuffer), &(ggqData->utcTime));
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 2nd field is date
                 */
            case 1:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcDate(field, circularBufferNMEADatafieldLength(cBuffer), &(ggqData->utcDate));
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 3rd field is latitude
                 */
            case 2:
            {
                if (8 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->latitude = convertLatitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 4th field is North/South
                 */
            case 3:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->latitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 5th field is longitude
                 */
            case 4:
            {
                if (9 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->longitude = convertLongitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 6th field is East/West
                 */
            case 5:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->longitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 7th field is gps quality
                 */
            case 6:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->gnssStatus = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 8th field is number of satellites
                 */
            case 7:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->numberSatellites = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 9th field is coordinate quality in metres
                 */
            case 8:
            {
                if (2 <= circularBufferNMEADatafieldLength(cBuffer) && 10 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->coordinateQuality = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 10th field is antenna height above mean sea level
                 */
            case 9:
            {
                if (1 < circularBufferNMEADatafieldLength(cBuffer) && 12 > circularBufferNMEADatafieldLength(cBuffer)) {
                    ggqData->antennaAboveMeanSea = atof(field);
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 11 field is unit of altitude
                 */
            case 10:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* @TODO won't parse */
                    /*
                                        if (field[0] == 'M') {
                                            ggqData->unitAntennaHeight = 1;
                                        } else {
                                            ggqData->unitAntennaHeight = 0;
                                        }
                     */
                } else {
                    /* set error flag and stop processing */
                    //ggqData->gnssStatus = 0;
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /* what to do? */
        //ggqData->gnssStatus = 0;
    }
    return;
}

/**
 * \brief NMEA sentence handling for: GSA
 * NMEA GSA message contains GPS DOP and active satellites. The DOP (dilution of precision) indicates the precision of the gnss fix based on effects of the satellite geometry. This number has no unit and smaller values are better.
 * @param[in] cBuffer
 * @param[out] gsaData
 */
/*
static void processGSA(circularBuffer_t *cBuffer, nmea_gsa_t *gsaData) {
    const int numberOfFields = 17;
    int dataFieldStart = 0;
    int dataFieldEnd = 0;
    int step = 0;
    // @TODO

    if (numberOfFields != step) {
        // @TODO invalid, field error
        // what to do?
    }
    return;
}
*/

/**
 * \brief NMEA sentence handling for: GSV
 * 
 * @param[in] cBuffer
 * @param[out] gsvData
 */
/*
static void processGSV(circularBuffer_t *cBuffer, nmea_gsv_t *gsvData) {
    const int numberOfFields = 7; // there much more fields possbile!!!
    int dataFieldStart = 0;
    int dataFieldEnd = 0;
    int step = 0;
    // @TODO


    if (numberOfFields != step) {
        // @TODO invalid, field error
        // what to do?
    }
    return;
}
*/

/**
 * \brief NMEA sentence handling for: GLL
 * NMEA sentence GLL geogaphic position. It contains Latitude, Longitude and time.
 * @param[in] cBuffer
 * @param[out] gllData
 */
static void processGLL(circularBuffer_t *cBuffer, nmea_gll_t *gllData) {
    const int numberOfFields = 7;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field is latitude
                 */
            case 0:
            {
                if (8 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    gllData->latitude = convertLatitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 2nd field is North/South
                 */
            case 1:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    gllData->latitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 3rd field is longitude
                 */
            case 2:
            {
                if (9 <= circularBufferNMEADatafieldLength(cBuffer) && 22 > circularBufferNMEADatafieldLength(cBuffer)) {
                    gllData->longitude = convertLongitude(field, circularBufferNMEADatafieldLength(cBuffer));
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 4th field is East/West
                 */
            case 3:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    gllData->longitudeAxis = convertAxis(field[0]);
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 5th field of GLL sentence is UTC time
                 */
            case 4:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer) || 9 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcTime(field, circularBufferNMEADatafieldLength(cBuffer), &(gllData->utcTime));
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 6th field is status
                 */
            case 5:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /**
                     * \TODO list all possible cases.
                     */
                    switch (field[0]) {
                        case 'a':
                        case 'A':
                        {
                            gllData->gnssStatus = STATUS_FIX;
                            break;
                        }
                        case 'v':
                        case 'V':
                        {
                            gllData->gnssStatus = STATUS_NO_FIX;
                            break;
                        }
                        default:
                        {
                            gllData->gnssStatus = STATUS_NO_FIX;
                        }
                    }
                } else {
                    /* set error flag and stop processing */
                    //gllData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 7th field is mode indication
                 *
                 * mode indicator (new in NMEA 2.3): The value can be A=autonomous, 
                 * D=differential, E=Estimated, N=not valid, S=Simulator. 
                 * 
                 * Sometimes there can be a null value as well. Only the A and D 
                 * values will correspond to an Active and reliable Sentence.
                 */
            case 6:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse mode indication */
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /* do nothing */
                } else {
                    /* set error flag and stop processing */
                    //rmcData->gnssStatus = 0;
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /** \TODO optional fields may lead to wrong */
        /* what to do? */
        //gllData->gnssStatus = 0;
    }
    return;
}

/**
 * \brief NMEA sentence handling for: GST
 * 
 * @param[in] cBuffer
 * @param[out] gstData
 */
/*
static void processGST(circularBuffer_t *cBuffer, nmea_gst_t *gstData) {
    // @TODO
    //return 0;
}
*/

/**
 * \brief NMEA sentence handling for: ZDA
 * 
 * @param[in] cBuffer
 * @param[out] zdaData
 */
static void processZDA(circularBuffer_t *cBuffer, nmea_zda_t *zdaData) {
    const int numberOfFields = 6;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field is UTC time
                 */
            case 0:
            {
                if (6 == circularBufferNMEADatafieldLength(cBuffer) || 9 == circularBufferNMEADatafieldLength(cBuffer)) {
                    convertUtcTime(field, circularBufferNMEADatafieldLength(cBuffer), &(zdaData->utcTime));
                } else {
                    /* set error flag and stop processing */
                    zdaData->gnssStatus = 0;
                }
                break;
            }
                /** 
                 * 2nd field is day
                 */
            case 1:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->utcDate.day = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //zdaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 3rd field is month
                 */
            case 2:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->utcDate.month = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //zdaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 4th field is year
                 */
            case 3:
            {
                if (4 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->utcDate.year = atoi(field);
                } else {
                    /* set error flag and stop processing */
                    //zdaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 5th field is local zone hours offset
                 * 
                 * \TODO signed?
                 */
            case 4:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->localTimezone.hourOffset = atoi(field);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->localTimezone.hourOffset = 0;
                } else {
                    /* set error flag and stop processing */
                    //zdaData->gnssStatus = 0;
                }
                break;
            }
                /**
                 * 6th field is local zone minutes offset
                 */
            case 5:
            {
                if (2 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->localTimezone.minuteOffset = atoi(field);
                } else if (0 == circularBufferNMEADatafieldLength(cBuffer)) {
                    zdaData->localTimezone.minuteOffset = 0;
                } else {
                    /* set error flag and stop processing */
                    //zdaData->gnssStatus = 0;
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /* what to do? */
        //zdaData->gnssStatus = 0;
    }
    return;
}

/**
 * \brief NMEA sentence handling for: GBS
 * 
 * @param[in] cBuffer
 * @param[out] gbsData
 */
/*
static void processGBS(circularBuffer_t *cBuffer, nmea_gbs_t *gbsData) {
    // @TODO
    //return 0;
}
*/

/**
 * \brief NMEA sentence handling for: VTG
 * 
 * @param[in] cBuffer
 * @param[out] vtgData
 */
static void processVTG(circularBuffer_t *cBuffer, nmea_vtg_t *vtgData) {
    const int numberOfFields = 8;
    int step = 0;
    int i;
    char field[NMEA_MAX_SENTENCE_LENGTH];

    cBuffer->datafieldStart = circularBufferMessageStartIncrease(cBuffer, 1);
    cBuffer->datafieldEnd = circularBufferMessageStartIncrease(cBuffer, 6);

    while (cBuffer->buffer[cBuffer->datafieldEnd] != '*' && cBuffer->buffer[cBuffer->datafieldEnd] != '\r') {
        circularBufferGetNextNMEADatafield(cBuffer);

        /** \brief copy data for processing
         * copy the content of current datafield to "processing memory"
         */
        for (i = 0; i < circularBufferNMEADatafieldLength(cBuffer); i++) {
            field[i] = cBuffer->buffer[circularBufferIndexIncrease(cBuffer, cBuffer->datafieldStart, i)];
        }
        field[i] = '\0';

        switch (step) {
                /**
                 * 1st field is true track made good.
                 */
            case 0:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 10 > circularBufferNMEADatafieldLength(cBuffer)) {
                    vtgData->trueTrackMadeGood = atoi(field);
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 2nd field is true track made good UNIT.
                 */
            case 1:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse this field too */
                    //vtgData->unitTrueTrackMadeGood = ?;
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 3rd field is magnetic track made good.
                 */
            case 2:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 10 > circularBufferNMEADatafieldLength(cBuffer)) {
                    vtgData->magneticTrackMadeGood = atoi(field);
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 4th field is magnetic track made good UNIT.
                 */
            case 3:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse this field too */
                    //vtgData->unitMagneticTrackMadeGood = ?;
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 5th field is ground speed knots.
                 */
            case 4:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 10 > circularBufferNMEADatafieldLength(cBuffer)) {
                    vtgData->groundSpeedKnots = atoi(field);
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 6th field is ground speed knots UNIT.
                 */
            case 5:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse this field too */
                    //vtgData->unitGroundSpeedKnots = ?;
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 7th field is ground speed kilometer per hour.
                 */
            case 6:
            {
                if (3 <= circularBufferNMEADatafieldLength(cBuffer) && 10 > circularBufferNMEADatafieldLength(cBuffer)) {
                    vtgData->groundSpeedKph = atoi(field);
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
                /**
                 * 8th field is ground speed kilometer per hour UNIT.
                 */
            case 7:
            {
                if (1 == circularBufferNMEADatafieldLength(cBuffer)) {
                    /** \TODO parse this field too */
                    //vtgData->unitGroundSpeedKph = ?;
                } else {
                    /* set error flag and stop processing */
                }
                break;
            }
        } /* end switch */

        step++;
    } /* end while */

    if (numberOfFields != step) {
        /* what to do? */
    }
    return;
}

/*
 * NMEA sentence handling: checksum
 * 
 * NMEA sentence should start with '$' and end with <CR><LF>
 * 
 * returns:
 *  1: checksum is valid
 *  0: checksum is NOT valid
 *  2: no checksum avalaible (use sentence anyway)
 */
static short int checksumIsValid(circularBuffer_t *cBuffer) {
    unsigned char crc = '\0';
    unsigned char myCRC = '\0';
    int hopcount = circularBufferIndexIncrease(cBuffer, cBuffer->messageStart, 1);

    /* calculate checksum */
    while ((cBuffer->buffer[hopcount] != '*') && (hopcount != cBuffer->messageEnd)) {
        myCRC ^= cBuffer->buffer[hopcount];
        hopcount = circularBufferIndexIncrease(cBuffer, hopcount, 1);
    }

    /* extract crc in nmea sentence (hex coded) */
    if (cBuffer->buffer[hopcount] == '*') {
        // @TODO this is subject to endianness ?!?
        crc = (cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 1)] >= 'A' ? ((cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 1)] & 0xdf) - 'A') + 10 : (cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 1)] - '0'));
        /* Bitverschiebung */
        crc <<= 4;
        crc += (cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 2)] >= 'A' ? ((cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 2)] & 0xdf) - 'A') + 10 : (cBuffer->buffer[circularBufferIndexIncrease(cBuffer, hopcount, 2)] - '0'));
    } else {
        /* no checksum avalaible */
        return 2;
    }

    /* compare checksum */
    if (crc == myCRC) {
        /* checksum valid */
        return 1;
    } else {
        /* checksum invalid */
        return 0;
    }
}

/*****************************************************************************
 * 
 * nmea sentence decoder
 * 
 *****************************************************************************/

/**
 * check sentence identification: sentenceGGA, sentenceGLL, sentenceGSA,
 * sentenceGST, sentenceGSV, sentenceRMC, sentenceZDA, sentenceGBS
 * 
 * \TODO erfasst nicht alle NMEA sentences
 * 
 * @param[in] cBuffer
 * @return nmea sentence
 */
static nmea_sentences_t nmeaSentenceIdentification(circularBuffer_t *cBuffer) {
    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 3)]) {
        case 'G':
        {
            switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 4)]) {
                case 'B':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'S':
                        {
                            return (GBS);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                case 'G':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'A':
                        {
                            return (GGA);
                            break;
                        }
                        case 'K':
                        {
                            return (GGK);
                            break;
                        }
                        case 'Q':
                        {
                            return (GGQ);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                case 'L':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'L':
                        {
                            return (GLL);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                case 'S':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'A':
                        {
                            return (GSA);
                            break;
                        }
                        case 'T':
                        {
                            return (GST);
                            break;
                        }
                        case 'V':
                        {
                            return (GSV);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    return (NMEA_UNKNOWN);
                    break;
                }
            }
            break;
        }
        case 'R':
        {
            switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 4)]) {
                case 'M':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'C':
                        {
                            return (RMC);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    return (NMEA_UNKNOWN);
                    break;
                }
            }
            break;
        }
        case 'V':
        {
            switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 4)]) {
                case 'T':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'G':
                        {
                            return (VTG);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    return (NMEA_UNKNOWN);
                    break;
                }
            }
            break;
        }
        case 'Z':
        {
            switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 4)]) {
                case 'D':
                {
                    switch (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 5)]) {
                        case 'A':
                        {
                            return (ZDA);
                            break;
                        }
                        default:
                        {
                            return (NMEA_UNKNOWN);
                            break;
                        }
                    }
                    break;
                }
                default:
                {
                    return (NMEA_UNKNOWN);
                    break;
                }
            }
            break;
        }
        default:
        {
            return (NMEA_UNKNOWN);
            break;
        }
    }
    /* for matlab/dSpace low budget compiler
     * 
     * the following line of CODE is UNREACHABLE!!! 
     */
    return (NMEA_UNKNOWN);
}

/** nmea sentence decoder
 * 
 * @param cBuffer
 * @param deviceId
 * @param[out] nmeaData
 * @param[in,out] status
 */
void nmea_decoder(circularBuffer_t *cBuffer, nmea_device_id_t deviceId, nmea0183_bus_t *nmeaData, long int *status) {
    nmea_sentences_t thisSentence = NMEA_UNKNOWN;
    short int crcValid;
    long int *crcErrorCounter;
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

    crcErrorCounter = &(status[1]);
    rmcCounter = &(status[3]);
    ggaCounter = &(status[4]);
    zdaCounter = &(status[5]);
    gllCounter = &(status[7]);
    gsaCounter = &(status[8]);
    gstCounter = &(status[9]);
    gsvCounter = &(status[10]);
    gbsCounter = &(status[11]);
    ggkCounter = &(status[12]);
    ggqCounter = &(status[13]);
    vtgCounter = &(status[14]);

    crcValid = checksumIsValid(cBuffer);
    if (crcValid > 0) {
        if (deviceId == devicePROPRIETARY) {
            /* @TODO currently no parsing of poprietary data */
        } else {
            thisSentence = nmeaSentenceIdentification(cBuffer);
            if (thisSentence == RMC) {
                (*rmcCounter)++;
                processRMC(cBuffer, &(nmeaData->rmcData));
            } else if (thisSentence == GGA) {
                (*ggaCounter)++;
                processGGA(cBuffer, &(nmeaData->ggaData));
            } else if (thisSentence == GGK) {
                (*ggkCounter)++;
                /**
                 * \TODO Parser für GGK sentences implementieren.
                 */
            } else if (thisSentence == GGQ) {
                (*ggqCounter)++;
                processGGQ(cBuffer, &(nmeaData->ggqData));
            } else if (thisSentence == GBS) {
                (*gbsCounter)++;
                /**
                 * \TODO Parser für GBS sentences implementieren.
                 */
            } else if (thisSentence == GLL) {
                (*gllCounter)++;
                processGLL(cBuffer, &(nmeaData->gllData));
            } else if (thisSentence == GSA) {
                (*gsaCounter)++;
                /**
                 * \TODO Parser für GSA sentences implementieren.
                 */
            } else if (thisSentence == GST) {
                (*gstCounter)++;
                /**
                 * \TODO Parser für GST sentences implementieren.
                 */
            } else if (thisSentence == GSV) {
                (*gsvCounter)++;
                /**
                 * \TODO Parser für GSV sentences implementieren.
                 */
            } else if (thisSentence == VTG) {
                (*vtgCounter)++;
                processVTG(cBuffer, &(nmeaData->vtgData));
            } else if (thisSentence == ZDA) {
                (*zdaCounter)++;
                processZDA(cBuffer, &(nmeaData->zdaData));
            }

        }
    } else {
        (*crcErrorCounter) += 1;
    }
}

/** initialize nmea dataset
 * 
 * after allocating memory for nmeadataset this function sets all values to zero
 * 
 * @param[out] nmeaData
 */
void initialiseNmeaDataset(nmea0183_bus_t *nmeaData) {
    nmeaData->ggaData.ageDGPS = 0.0;
    nmeaData->ggaData.antennaAboveMeanSea = 0.0;
    nmeaData->ggaData.dgpsReferenceStation = 0.0;
    nmeaData->ggaData.dilusionOfPrecision = 0.0;
    nmeaData->ggaData.geodialSeparation = 0.0;
    nmeaData->ggaData.gnssStatus = STATUS_NO_FIX;
    nmeaData->ggaData.latitude = 0.0;
    nmeaData->ggaData.latitudeAxis = axisUNKNOWN;
    nmeaData->ggaData.longitude = 0.0;
    nmeaData->ggaData.longitudeAxis = axisUNKNOWN;
    nmeaData->ggaData.numberSatellites = 0;
    nmeaData->ggaData.unitAntennaHeight = 0.0;
    nmeaData->ggaData.unitGeodialSeparation = 0.0;
    nmeaData->ggaData.utcTime.hour = 0;
    nmeaData->ggaData.utcTime.minutes = 0;
    nmeaData->ggaData.utcTime.seconds = 0.0;
    nmeaData->ggqData.antennaAboveMeanSea = 0.0;
    nmeaData->ggqData.coordinateQuality = 0.0;
    nmeaData->ggqData.gnssStatus = STATUS_NO_FIX;
    nmeaData->ggqData.latitude = 0.0;
    nmeaData->ggqData.latitudeAxis = axisUNKNOWN;
    nmeaData->ggqData.longitude = 0.0;
    nmeaData->ggqData.longitudeAxis = axisUNKNOWN;
    nmeaData->ggqData.numberSatellites = 0;
    nmeaData->ggqData.utcTime.hour = 0;
    nmeaData->ggqData.utcTime.minutes = 0;
    nmeaData->ggqData.utcTime.seconds = 0.0;
    nmeaData->ggqData.utcDate.day = 0;
    nmeaData->ggqData.utcDate.month = 0;
    nmeaData->ggqData.utcDate.year = 0;
    nmeaData->gllData.gnssStatus = STATUS_NO_FIX;
    nmeaData->gllData.latitude = 0.0;
    nmeaData->gllData.latitudeAxis = axisUNKNOWN;
    nmeaData->gllData.longitude = 0.0;
    nmeaData->gllData.longitudeAxis = axisUNKNOWN;
    nmeaData->gllData.utcTime.hour = 0;
    nmeaData->gllData.utcTime.minutes = 0;
    nmeaData->gllData.utcTime.seconds = 0.0;
    nmeaData->rmcData.gnssStatus = STATUS_NO_FIX;
    nmeaData->rmcData.latitude = 0.0;
    nmeaData->rmcData.latitudeAxis = axisUNKNOWN;
    nmeaData->rmcData.longitude = 0.0;
    nmeaData->rmcData.longitudeAxis = axisUNKNOWN;
    nmeaData->rmcData.magneticAxis = axisUNKNOWN;
    nmeaData->rmcData.magneticVariation = 0.0;
    nmeaData->rmcData.modeIndication = 0.0;
    nmeaData->rmcData.trackAngle = 0.0;
    nmeaData->rmcData.utcTime.hour = 0;
    nmeaData->rmcData.utcTime.minutes = 0;
    nmeaData->rmcData.utcTime.seconds = 0.0;
    nmeaData->rmcData.utcDate.day = 0;
    nmeaData->rmcData.utcDate.month = 0;
    nmeaData->rmcData.utcDate.year = 0;
    nmeaData->rmcData.velocity = 0.0;
    nmeaData->vtgData.groundSpeedKnots = 0;
    nmeaData->vtgData.groundSpeedKph = 0;
    nmeaData->vtgData.magneticTrackMadeGood = 0;
    nmeaData->vtgData.modeIndication = 0;
    nmeaData->vtgData.trueTrackMadeGood = 0;
    nmeaData->vtgData.unitGroundSpeedKnots = 0;
    nmeaData->vtgData.unitGroundSpeedKph = 0;
    nmeaData->vtgData.unitMagneticTrackMadeGood = 0;
    nmeaData->vtgData.unitTrueTrackMadeGood = 0;
    nmeaData->zdaData.utcTime.hour = 0;
    nmeaData->zdaData.utcTime.minutes = 0;
    nmeaData->zdaData.utcTime.seconds = 0.0;
    nmeaData->zdaData.utcDate.day = 0;
    nmeaData->zdaData.utcDate.month = 0;
    nmeaData->zdaData.utcDate.year = 0;
    nmeaData->zdaData.localTimezone.hourOffset = 0;
    nmeaData->zdaData.localTimezone.minuteOffset = 0;
    nmeaData->zdaData.gnssStatus = STATUS_NO_FIX;
}

/** gnssMessageIsKnownFormat
 * 
 * checks wther is nmea sentence or sbf message
 * 
 * @param[in,out] cBuffer circular buffer object. end-of-message state is changed by this function if nmea sentence is found.
 * @return nmeaDevice_t type of detected device
 */
static nmea_device_id_t gnssMessageIsKnownFormat(circularBuffer_t *cBuffer) {
    nmea_device_id_t deviceId;

    /**
     * \note each sentence starts with dollar or exmak, but this is checked in buffermgmt!
     */
    //    if (cBuffer->buffer[cBuffer->messageStart] != '$' && cBuffer->buffer[cBuffer->messageStart] != '!') {
    //        return (deviceUNKNOWN);
    //    }

    /** 
     * \note The following nmea device id's will be evaluated: 
     *  - GA
     *  - GL
     *  - GP
     *  - GN
     * 
     * \TODO erfasst nicht alle NMEA Devices
     */
    if (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 1)] == 'G' && cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 2)] == 'A') {
        deviceId = deviceGALILEO;
    } else if (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 1)] == 'G' && cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 2)] == 'L') {
        deviceId = deviceGLONASS;
    } else if (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 1)] == 'G' && cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 2)] == 'P') {
        deviceId = deviceGPS;
    } else if (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 1)] == 'G' && cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 2)] == 'N') {
        deviceId = deviceCombined;
    } else if (cBuffer->buffer[circularBufferMessageStartIncrease(cBuffer, 1)] == 0x40) { // 0x40 is @
        return (deviceSBF);
    } else {
        return (deviceUNKNOWN);
    }

    /**
     * start search for end of message
     */
    cBuffer->messageEnd = cBuffer->messageStart;
    while (cBuffer->buffer[cBuffer->messageEnd] != '\r' && (circularBufferDataLength(cBuffer) - circularBufferMessageLength(cBuffer)) > 1) {
        cBuffer->messageEnd = circularBufferMessageEndIncrease(cBuffer, 1);
    }
    if (cBuffer->buffer[cBuffer->messageEnd] == '\r') {
        if (cBuffer->buffer[circularBufferMessageEndIncrease(cBuffer, 1)] == '\n') {
            /** bingo!
             * nmea sentence end found, congratulations.
             */
            cBuffer->messageEnd = circularBufferMessageEndIncrease(cBuffer, 1);
            return (deviceId);
        } else if ((circularBufferDataLength(cBuffer) - circularBufferMessageLength(cBuffer)) == 1) {
            return (deviceFRAGMENTARY);
        } else {
            return (deviceUNKNOWN);
        }

    } else if (circularBufferMessageLength(cBuffer) > 80) {
        /** \note NMEA standard limits messages to 80 printable char
         */
        return (deviceUNKNOWN);
    } else {
        /**
         * only part of nmea sentence detected. wait for new data!
         */
        return (deviceFRAGMENTARY);
    }
}

/** gnssWorker
 * 
 * @param[in,out] cBuffer
 * @param[in] message
 * @param[in] messageLength
 * @param[out] nmeaData
 * @param[out] status
 */
void gnssWorker(circularBuffer_t *cBuffer, const uint8_t message[], const unsigned long int messageLength, nmea0183_bus_t *nmeaData, long int *status) {
    bufferError_t bufErr = NOERROR;
    nmea_device_id_t deviceId = deviceUNKNOWN;
    long int *sentenceCounter;
    long int *bufferOverflow;
    long int *everBytes;

    sentenceCounter = &(status[0]);
    bufferOverflow = &(status[2]);
    everBytes = &(status[6]);

    /** get data into buffer
     */
    bufErr = circularBufferWrite(cBuffer, message, messageLength);
    *bufferOverflow += bufErr;
    *everBytes += messageLength;

    /** parse data avalaible
     */
    while (circularBufferDataLength(cBuffer) > 5 && deviceId != deviceFRAGMENTARY) {
        bufErr = circularBufferGetMessageStart(cBuffer);
        if (bufErr != NOMESSAGE) {
            deviceId = gnssMessageIsKnownFormat(cBuffer);
            if (deviceId == deviceGALILEO || deviceId == deviceGLONASS || deviceId == deviceGPS || deviceId == deviceCombined) {
                nmea_decoder(cBuffer, deviceId, nmeaData, status);
                (*sentenceCounter)++;
                circularBufferSetMessageStartToEndOfMessage(cBuffer);
            } else if (deviceId == deviceFRAGMENTARY) {
                /* do nothing (while-loop will stop next time) */
            } else {
                circularBufferMessageStartPlusPlus(cBuffer);
            }
        }
    }
}
