/*
 * File:    gnss_constants.h
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

#ifndef GNSS_CONSTANTS_H
#define GNSS_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

    /* some multipliers for interpreting GPS output */
//#define METERS_TO_FEET 3.2808399 /* Meters to U.S./British feet */
//#define METERS_TO_MILES 0.00062137119 /* Meters to miles */
//#define METERS_TO_FATHOMS 0.54680665 /* Meters to fathoms */
//#define KNOTS_TO_MPH 1.1507794 /* Knots to miles per hour */
//#define KNOTS_TO_KPH 1.852  /* Knots to kilometers per hour */
#define KNOTS_TO_MPS 0.51444444 /* Knots to meters per second */
//#define MPS_TO_KPH 3.6  /* Meters per second to klicks/hr */
//#define MPS_TO_MPH 2.2369363 /* Meters/second to miles per hour */
//#define MPS_TO_KNOTS 1.9438445 /* Meters per second to knots */
    /* miles and knots are both the international standard versions of the units */

    /* angle conversion multipliers */
//#define GPS_PI       3.1415926535897932384626433832795029
//#define RAD_2_DEG 57.2957795130823208767981548141051703
//#define DEG_2_RAD 0.0174532925199432957692369076848861271

    /* geodetic constants */
//#define WGS84A 6378137  /* equatorial radius */
//#define WGS84F 298.257223563 /* flattening */
//#define WGS84B 6356752.3142 /* polar radius */

#ifdef __cplusplus
}
#endif

#endif /* GNSS_CONSTANTS_H */
