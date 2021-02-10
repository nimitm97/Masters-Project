/*
 * rpi_arduino_rw_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "rpi_arduino_rw".
 *
 * Model version              : 1.14
 * Simulink Coder version : 9.0 (R2018b) 24-May-2018
 * C source code generated on : Thu Feb 20 16:30:48 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(codertarget_raspi_internal__m_T),
  sizeof(codertarget_raspi_internal_I2_T),
  sizeof(codertarget_raspi_internal_SP_T),
  sizeof(raspi_internal_lsm9ds1Block_r_T),
  sizeof(codertarget_raspi_internal_SC_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "codertarget_raspi_internal__m_T",
  "codertarget_raspi_internal_I2_T",
  "codertarget_raspi_internal_SP_T",
  "raspi_internal_lsm9ds1Block_r_T",
  "codertarget_raspi_internal_SC_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&rpi_arduino_rw_B.TmpSignalConversionAtToWorkspac[0]), 0, 0, 4 },

  { (char_T *)(&rpi_arduino_rw_B.Product2), 0, 0, 17 },

  { (char_T *)(&rpi_arduino_rw_B.SPIRegisterRead[0]), 3, 0, 9 },

  { (char_T *)(&rpi_arduino_rw_B.SerialRead_o1), 2, 0, 1 }
  ,

  { (char_T *)(&rpi_arduino_rw_DW.obj), 17, 0, 1 },

  { (char_T *)(&rpi_arduino_rw_DW.obj_h), 14, 0, 1 },

  { (char_T *)(&rpi_arduino_rw_DW.obj_m), 16, 0, 2 },

  { (char_T *)(&rpi_arduino_rw_DW.obj_hq), 18, 0, 1 },

  { (char_T *)(&rpi_arduino_rw_DW.obj_b), 15, 0, 1 },

  { (char_T *)(&rpi_arduino_rw_DW.ToWorkspace_PWORK.LoggedData), 11, 0, 5 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  10U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&rpi_arduino_rw_P.Throttle_Value), 0, 0, 11 },

  { (char_T *)(&rpi_arduino_rw_P.Switch2_Threshold), 3, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  2U,
  rtPTransitions
};

/* [EOF] rpi_arduino_rw_dt.h */
