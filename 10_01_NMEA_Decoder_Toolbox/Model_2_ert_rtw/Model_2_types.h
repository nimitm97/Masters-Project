/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Model_2_types.h
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

#ifndef RTW_HEADER_Model_2_types_h_
#define RTW_HEADER_Model_2_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Custom Type definition for MATLABSystem: '<Root>/Serial Read' */
#include "MW_SVD.h"
#include <stddef.h>
#ifndef typedef_codertarget_raspi_internal_Ha_T
#define typedef_codertarget_raspi_internal_Ha_T

typedef struct {
  int32_T dummy;
} codertarget_raspi_internal_Ha_T;

#endif                                 /*typedef_codertarget_raspi_internal_Ha_T*/

#ifndef typedef_codertarget_raspi_internal_SC_T
#define typedef_codertarget_raspi_internal_SC_T

typedef struct {
  int32_T isInitialized;
  codertarget_raspi_internal_Ha_T Hw;
  MW_Handle_Type MW_SCIHANDLE;
  real_T SampleTime;
} codertarget_raspi_internal_SC_T;

#endif                                 /*typedef_codertarget_raspi_internal_SC_T*/

/* Parameters (auto storage) */
typedef struct P_Model_2_T_ P_Model_2_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Model_2_T RT_MODEL_Model_2_T;

#endif                                 /* RTW_HEADER_Model_2_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
