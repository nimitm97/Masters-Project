/*
 * File:    nmea0183_sentences.h
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

#ifndef NMEA0183_SENTENCES_H
#define NMEA0183_SENTENCES_H

#include "nmea0183_types.h"
#include "nmea0183_types_time.h"

#ifdef __cplusplus
extern "C" {
#endif

    /** \enum nmeaSentences_t
     */
    typedef enum {
        NMEA_UNKNOWN,
        GGA,
        GLL,
        GSA,
        GST,
        GSV,
        RMC,
        ZDA,
        GBS,
        GGQ,
        GGK,
        VTG
    } nmea_sentences_t;

    typedef struct {
        double noop;
    } nmea_gbs_t;

    typedef struct {
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
        double latitude;
        coordAxis_t latitudeAxis;
        double longitude;
        coordAxis_t longitudeAxis;
        int numberSatellites;
        double dilusionOfPrecision;
        double antennaAboveMeanSea;
        double unitAntennaHeight;
        double geodialSeparation;
        double unitGeodialSeparation;
        double ageDGPS;
        double dgpsReferenceStation;
    } nmea_gga_t;

    typedef struct {
        nmea_time_t utcTime;
        nmea_date_t utcDate;
        double latitude;
        coordAxis_t latitudeAxis;
        double longitude;
        coordAxis_t longitudeAxis;
        gnss_status_t gnssStatus;
        int numberSatellites;
        double coordinateQuality;
        double antennaAboveMeanSea;
    } nmea_ggq_t;

    typedef struct {
        double latitude;
        coordAxis_t latitudeAxis;
        double longitude;
        coordAxis_t longitudeAxis;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
    } nmea_gll_t;

    typedef struct {
        nmea_date_t utcDate;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
    } nmea_gsa_t;

    typedef struct {
        nmea_date_t utcDate;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
    } nmea_gst_t;

    typedef struct {
        nmea_date_t utcDate;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
    } nmea_gsv_t;

    typedef struct {
        nmea_date_t utcDate;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
        double latitude;
        coordAxis_t latitudeAxis;
        double longitude;
        coordAxis_t longitudeAxis;
        double velocity; // m/s
        double trackAngle;
        double magneticVariation;
        coordAxis_t magneticAxis;
        double modeIndication;
    } nmea_rmc_t;

    typedef struct {
        double trueTrackMadeGood;
        short int unitTrueTrackMadeGood;
        double magneticTrackMadeGood;
        short int unitMagneticTrackMadeGood;
        double groundSpeedKnots;
        short int unitGroundSpeedKnots;
        double groundSpeedKph;
        short int unitGroundSpeedKph;
        short int modeIndication;
    } nmea_vtg_t;

    typedef struct {
        nmea_date_t utcDate;
        nmea_time_t utcTime;
        gnss_status_t gnssStatus;
        timezone_t localTimezone;
    } nmea_zda_t;

    typedef struct {
        nmea_gga_t ggaData;
        nmea_ggq_t ggqData;
        nmea_gll_t gllData;
        nmea_rmc_t rmcData;
        nmea_vtg_t vtgData;
        nmea_zda_t zdaData;
    } nmea0183_bus_t;

#ifdef __cplusplus
}
#endif

#endif /* NMEA0183_SENTENCES_H */
