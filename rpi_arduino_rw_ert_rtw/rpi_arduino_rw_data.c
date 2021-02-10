/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rpi_arduino_rw_data.c
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

#include "rpi_arduino_rw.h"
#include "rpi_arduino_rw_private.h"

/* Block parameters (default storage) */
P_rpi_arduino_rw_T rpi_arduino_rw_P = {
  /* Expression: 193
   * Referenced by: '<S1>/Throttle'
   */
  193.0,

  /* Expression: 127.5
   * Referenced by: '<S1>/Steering'
   */
  127.5,

  /* Expression: 0.1
   * Referenced by: '<S1>/I2C Master Read'
   */
  0.1,

  /* Expression: 1
   * Referenced by: '<S2>/SPI Register Read1'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/SPI Register Read'
   */
  1.0,

  /* Expression: SampleTime
   * Referenced by: '<S4>/Serial Read'
   */
  0.01,

  /* Expression: 180
   * Referenced by: '<S2>/wheel_cirumfirence_in_mm'
   */
  180.0,

  /* Expression: 1/1000
   * Referenced by: '<S2>/mm_to_m'
   */
  0.001,

  /* Expression: 1/4
   * Referenced by: '<S2>/4_pulses_very_rotation'
   */
  0.25,

  /* Expression: 1/1000
   * Referenced by: '<S2>/cycle_time_in_ms'
   */
  0.001,

  /* Expression: 60000
   * Referenced by: '<S2>/ms_to_min'
   */
  60000.0,

  /* Computed Parameter: Switch2_Threshold
   * Referenced by: '<S1>/Switch2'
   */
  1U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
