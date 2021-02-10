/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rpi_arduino_rw_types.h
 *
 * Code generated for Simulink model 'rpi_arduino_rw'.
 *
 * Model version                  : 1.14
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Thu Feb 20 16:30:48 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rpi_arduino_rw_types_h_
#define RTW_HEADER_rpi_arduino_rw_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Custom Type definition for MATLABSystem: '<S4>/Serial Read' */
#include "MW_SVD.h"
#include <stddef.h>
#ifndef typedef_codertarget_raspi_internal_Ha_T
#define typedef_codertarget_raspi_internal_Ha_T

typedef struct {
  int32_T __dummy;
} codertarget_raspi_internal_Ha_T;

#endif                                 /*typedef_codertarget_raspi_internal_Ha_T*/

#ifndef typedef_codertarget_raspi_internal_I2_T
#define typedef_codertarget_raspi_internal_I2_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  codertarget_raspi_internal_Ha_T Hw;
  uint32_T BusSpeed;
  MW_Handle_Type MW_I2C_HANDLE;
} codertarget_raspi_internal_I2_T;

#endif                                 /*typedef_codertarget_raspi_internal_I2_T*/

#ifndef typedef_codertarget_raspi_internal__m_T
#define typedef_codertarget_raspi_internal__m_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  codertarget_raspi_internal_Ha_T Hw;
  uint32_T BusSpeed;
  MW_Handle_Type MW_I2C_HANDLE;
  real_T SampleTime;
} codertarget_raspi_internal__m_T;

#endif                                 /*typedef_codertarget_raspi_internal__m_T*/

#ifndef typedef_codertarget_raspi_internal_SP_T
#define typedef_codertarget_raspi_internal_SP_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  codertarget_raspi_internal_Ha_T Hw;
  MW_Handle_Type MW_SPI_HANDLE;
  real_T SampleTime;
} codertarget_raspi_internal_SP_T;

#endif                                 /*typedef_codertarget_raspi_internal_SP_T*/

#ifndef typedef_codertarget_raspi_internal_mu_T
#define typedef_codertarget_raspi_internal_mu_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  codertarget_raspi_internal_Ha_T Hw;
  uint32_T BusSpeed;
  MW_Handle_Type MW_I2C_HANDLE;
} codertarget_raspi_internal_mu_T;

#endif                                 /*typedef_codertarget_raspi_internal_mu_T*/

#ifndef typedef_codertarget_raspi_interna_muq_T
#define typedef_codertarget_raspi_interna_muq_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  codertarget_raspi_internal_Ha_T Hw;
  uint32_T BusSpeed;
  MW_Handle_Type MW_I2C_HANDLE;
} codertarget_raspi_interna_muq_T;

#endif                                 /*typedef_codertarget_raspi_interna_muq_T*/

#ifndef typedef_codertarget_raspi_internal_SC_T
#define typedef_codertarget_raspi_internal_SC_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  codertarget_raspi_internal_Ha_T Hw;
  MW_Handle_Type MW_SCIHANDLE;
  real_T SampleTime;
} codertarget_raspi_internal_SC_T;

#endif                                 /*typedef_codertarget_raspi_internal_SC_T*/

#ifndef typedef_raspi_internal_lsm9ds1Block_r_T
#define typedef_raspi_internal_lsm9ds1Block_r_T

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T CalGyroA[9];
  real_T CalGyroB[3];
  real_T CalAccelA[9];
  real_T CalAccelB[3];
  real_T CalMagA[9];
  real_T CalMagB[3];
  codertarget_raspi_internal_mu_T i2cobj_A_G;
  codertarget_raspi_interna_muq_T i2cobj_MAG;
} raspi_internal_lsm9ds1Block_r_T;

#endif                                 /*typedef_raspi_internal_lsm9ds1Block_r_T*/

/* Parameters (default storage) */
typedef struct P_rpi_arduino_rw_T_ P_rpi_arduino_rw_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_rpi_arduino_rw_T RT_MODEL_rpi_arduino_rw_T;

#endif                                 /* RTW_HEADER_rpi_arduino_rw_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
