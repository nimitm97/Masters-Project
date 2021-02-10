/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rpi_arduino_rw_private.h
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

#ifndef RTW_HEADER_rpi_arduino_rw_private_h_
#define RTW_HEADER_rpi_arduino_rw_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "rpi_arduino_rw.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

extern void rpi_arduino_rw_step0(void);
extern void rpi_arduino_rw_step1(void);
extern void rpi_arduino_rw_step2(void);

#endif                                 /* RTW_HEADER_rpi_arduino_rw_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
