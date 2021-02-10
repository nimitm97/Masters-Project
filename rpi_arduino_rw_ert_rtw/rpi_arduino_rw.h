/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rpi_arduino_rw.h
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

#ifndef RTW_HEADER_rpi_arduino_rw_h_
#define RTW_HEADER_rpi_arduino_rw_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef rpi_arduino_rw_COMMON_INCLUDES_
# define rpi_arduino_rw_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "dt_info.h"
#include "ext_work.h"
#include "MW_I2C.h"
#include "MW_SPI.h"
#include "MW_SPI_Helper.h"
#include "MW_SCI.h"
#endif                                 /* rpi_arduino_rw_COMMON_INCLUDES_ */

#include "rpi_arduino_rw_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real_T b[9];
  real_T TmpSignalConversionAtToWorkspac[4];
  real_T a[3];
  char_T SCIModuleLoc[13];
  uint32_T SSPinNameLoc;
  uint32_T MOSIPinLoc;
  uint32_T MISOPinLoc;
  uint32_T SCKPinLoc;
  MW_SCI_StopBits_Type StopBitsValue;
  real_T Product2;                     /* '<S2>/Product2' */
  real_T Product;                      /* '<S2>/Product' */
  real_T Product4;                     /* '<S2>/Product4' */
  real_T Product3;                     /* '<S2>/Product3' */
  real_T Product6;                     /* '<S2>/Product6' */
  real_T Product7;                     /* '<S2>/Product7' */
  real_T Product8;                     /* '<S2>/Product8' */
  real_T Product9;                     /* '<S2>/Product9' */
  real_T LSM9DS1IMUSensor_o1[3];       /* '<S3>/LSM9DS1 IMU Sensor' */
  real_T LSM9DS1IMUSensor_o2[3];       /* '<S3>/LSM9DS1 IMU Sensor' */
  real_T LSM9DS1IMUSensor_o3[3];       /* '<S3>/LSM9DS1 IMU Sensor' */
  uint8_T SPIRegisterRead[4];          /* '<S2>/SPI Register Read' */
  uint8_T SPIRegisterRead1[4];         /* '<S2>/SPI Register Read1' */
  uint8_T I2CMasterRead_o1;            /* '<S1>/I2C Master Read' */
  int8_T SerialRead_o1;                /* '<S4>/Serial Read' */
} B_rpi_arduino_rw_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  raspi_internal_lsm9ds1Block_r_T obj; /* '<S3>/LSM9DS1 IMU Sensor' */
  codertarget_raspi_internal__m_T obj_h;/* '<S1>/I2C Master Read' */
  codertarget_raspi_internal_SP_T obj_m;/* '<S2>/SPI Register Read' */
  codertarget_raspi_internal_SP_T obj_m4;/* '<S2>/SPI Register Read1' */
  codertarget_raspi_internal_SC_T obj_hq;/* '<S4>/Serial Read' */
  codertarget_raspi_internal_I2_T obj_b;/* '<S1>/I2C Master Write' */
  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<S2>/To Workspace' */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK_e;               /* '<S3>/To Workspace' */

  struct {
    void *LoggedData;
  } ToWorkspace1_PWORK;                /* '<S3>/To Workspace1' */

  struct {
    void *LoggedData;
  } ToWorkspace2_PWORK;                /* '<S3>/To Workspace2' */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK_h;               /* '<S4>/To Workspace' */
} DW_rpi_arduino_rw_T;

/* Parameters (default storage) */
struct P_rpi_arduino_rw_T_ {
  real_T Throttle_Value;               /* Expression: 193
                                        * Referenced by: '<S1>/Throttle'
                                        */
  real_T Steering_Value;               /* Expression: 127.5
                                        * Referenced by: '<S1>/Steering'
                                        */
  real_T I2CMasterRead_SampleTime;     /* Expression: 0.1
                                        * Referenced by: '<S1>/I2C Master Read'
                                        */
  real_T SPIRegisterRead1_SampleTime;  /* Expression: 1
                                        * Referenced by: '<S2>/SPI Register Read1'
                                        */
  real_T SPIRegisterRead_SampleTime;   /* Expression: 1
                                        * Referenced by: '<S2>/SPI Register Read'
                                        */
  real_T SerialRead_SampleTime;        /* Expression: SampleTime
                                        * Referenced by: '<S4>/Serial Read'
                                        */
  real_T wheel_cirumfirence_in_mm_Value;/* Expression: 180
                                         * Referenced by: '<S2>/wheel_cirumfirence_in_mm'
                                         */
  real_T mm_to_m_Value;                /* Expression: 1/1000
                                        * Referenced by: '<S2>/mm_to_m'
                                        */
  real_T u_pulses_very_rotation_Value; /* Expression: 1/4
                                        * Referenced by: '<S2>/4_pulses_very_rotation'
                                        */
  real_T cycle_time_in_ms_Value;       /* Expression: 1/1000
                                        * Referenced by: '<S2>/cycle_time_in_ms'
                                        */
  real_T ms_to_min_Value;              /* Expression: 60000
                                        * Referenced by: '<S2>/ms_to_min'
                                        */
  uint8_T Switch2_Threshold;           /* Computed Parameter: Switch2_Threshold
                                        * Referenced by: '<S1>/Switch2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_rpi_arduino_rw_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_rpi_arduino_rw_T rpi_arduino_rw_P;

/* Block signals (default storage) */
extern B_rpi_arduino_rw_T rpi_arduino_rw_B;

/* Block states (default storage) */
extern DW_rpi_arduino_rw_T rpi_arduino_rw_DW;

/* External function called from main */
extern void rpi_arduino_rw_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void rpi_arduino_rw_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void rpi_arduino_rw_initialize(void);
extern void rpi_arduino_rw_step(int_T tid);
extern void rpi_arduino_rw_terminate(void);

/* Real-time Model object */
extern RT_MODEL_rpi_arduino_rw_T *const rpi_arduino_rw_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'rpi_arduino_rw'
 * '<S1>'   : 'rpi_arduino_rw/Automatic Mode'
 * '<S2>'   : 'rpi_arduino_rw/Encoder'
 * '<S3>'   : 'rpi_arduino_rw/IMU'
 * '<S4>'   : 'rpi_arduino_rw/Potentiometer'
 */
#endif                                 /* RTW_HEADER_rpi_arduino_rw_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
