/*
 * File:    nmea0183_types_time.h
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

#ifndef NMEA0183_TYPES_TIME_H
#define NMEA0183_TYPES_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

    /** \struct gnssDate_t
     */
    typedef struct {
        /** \var year
         * year of date
         */
        unsigned int year;
        /** \var month
         * month of date
         */
        unsigned int month;
        /** \var day
         * day of date
         */
        unsigned int day;
    } nmea_date_t;

    /** \struct gnssTime_t
     */
    typedef struct {
        /** \var hour
         * hour of day as integer value.
         */
        unsigned int hour;
        /** \var minutes
         * minute of hour as an integer value.
         */
        unsigned int minutes;
        /** \var seconds
         * seconds of minute as double value.
         */
        double seconds;
    } nmea_time_t;

    /** \struct timezone_T
     * structure to define timezone as offset to utc.
     */
    typedef struct {
        /** \var hourOffset
         * timezone offset (hours) to utc
         */
        short int hourOffset;
        /** \var minuteOffset
         * timezone offset (minutes) to utc
         */
        short int minuteOffset;
    } timezone_t;

#ifdef __cplusplus
}
#endif

#endif /* NMEA0183_TYPES_TIME_H */
