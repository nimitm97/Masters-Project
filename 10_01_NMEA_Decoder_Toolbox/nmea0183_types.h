/*
 * File:    nmea0183_types.h
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

#ifndef NMEA0183_TYPES_H
#define NMEA0183_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

    /** \enum nmeaDeviceId_t
     */
    typedef enum {
        deviceUNKNOWN = 0,
        deviceGALILEO = 1,
        deviceGLONASS = 2,
        deviceGPS = 3,
        deviceCombined = 9,
        devicePROPRIETARY = 10,
        deviceFRAGMENTARY = 11,
        deviceSBF = 20
    } nmea_device_id_t;

    /** \enum gnssStatus_t
     */
    typedef enum {
        STATUS_NO_FIX = 0,
        STATUS_FIX = 1,
        STATUS_DGPS_FIX = 2,
        STATUS_PPS_FIX = 3,
        STATUS_RTK_FIX = 4,
        STATUS_FLOAT_RTK_FIX = 5,
        STATUS_ESTIMATED_FIX = 6,
        STATUS_MANUAL_INPUT = 7,
        STATUS_SIMULATION = 8
    } gnss_status_t;

    /** \enum coordAxis_t
     * Enumeration of all 4 possible axis directions.
     * The values are east = 0, west = 1, north = 2 and south = 3.
     */
    typedef enum {
        axisUNKNOWN = -1,
        axisEast = 0,
        axisWest = 1,
        axisNorth = 2,
        axisSouth = 3
    } coordAxis_t;

#ifdef __cplusplus
}
#endif

#endif /* NMEA0183_TYPES_H */
