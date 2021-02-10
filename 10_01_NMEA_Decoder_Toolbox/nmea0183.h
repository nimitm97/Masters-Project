/*
 * File:    nmea0183.h
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


#ifndef NMEA0183_H
#define NMEA0183_H

#include "circularbuffer.h"
#include "nmea0183_sentences.h"
#include "nmea0183_types.h"

#ifdef __cplusplus
extern "C" {
#endif

    /** \def NMEA_MAX_SENTENCE_LENGTH
     * maximum length of nmea sentences (see nmea0183 standard)
     */
#define NMEA_MAX_SENTENCE_LENGTH 80
/** \def Enable CUnit test wrapper functions
 * macro to enable CUnit-test wrapper functions to access static functions
 */
//#define __CUNITTEST__

    extern void nmea_decoder(circularBuffer_t *cBuffer, nmea_device_id_t deviceId, nmea0183_bus_t *nmeaData, long int *status);
    extern void initialiseNmeaDataset(nmea0183_bus_t *nmeaData);
    /** gnssWorker function
     * main "working" function to parse gnss data
     */
    extern void gnssWorker(circularBuffer_t *cBuffer, const uint8_t message[], const unsigned long int messageLength, nmea0183_bus_t *nmeaData, long int *status);

#ifdef __cplusplus
}
#endif

#endif /* NMEA0183_H */
