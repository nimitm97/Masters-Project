/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rpi_arduino_rw.c
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
#include "rpi_arduino_rw_dt.h"

/* Block signals (default storage) */
B_rpi_arduino_rw_T rpi_arduino_rw_B;

/* Block states (default storage) */
DW_rpi_arduino_rw_T rpi_arduino_rw_DW;

/* Real-time model */
RT_MODEL_rpi_arduino_rw_T rpi_arduino_rw_M_;
RT_MODEL_rpi_arduino_rw_T *const rpi_arduino_rw_M = &rpi_arduino_rw_M_;

/* Forward declaration for local functions */
static void rpi_ardu_SystemCore_release_muq(const
  codertarget_raspi_internal_SP_T *obj);
static void rpi_ardui_SystemCore_delete_muq(const
  codertarget_raspi_internal_SP_T *obj);
static void matlabCodegenHandle_matlabC_muq(codertarget_raspi_internal_SP_T *obj);
static void rpi_ardui_SystemCore_release_mu(const
  codertarget_raspi_internal_SP_T *obj);
static void rpi_arduin_SystemCore_delete_mu(const
  codertarget_raspi_internal_SP_T *obj);
static void matlabCodegenHandle_matlabCo_mu(codertarget_raspi_internal_SP_T *obj);
static void rpi_ard_SystemCore_release_muqg(const
  raspi_internal_lsm9ds1Block_r_T *obj);
static void rpi_ardu_SystemCore_delete_muqg(const
  raspi_internal_lsm9ds1Block_r_T *obj);
static void matlabCodegenHandle_matlab_muqg(raspi_internal_lsm9ds1Block_r_T *obj);
static void rpi_ar_SystemCore_release_muqgd(codertarget_raspi_internal_mu_T *obj);
static void rpi_ard_SystemCore_delete_muqgd(codertarget_raspi_internal_mu_T *obj);
static void matlabCodegenHandle_matla_muqgd(codertarget_raspi_internal_mu_T *obj);
static void rpi_a_SystemCore_release_muqgdu(codertarget_raspi_interna_muq_T *obj);
static void rpi_ar_SystemCore_delete_muqgdu(codertarget_raspi_interna_muq_T *obj);
static void matlabCodegenHandle_matl_muqgdu(codertarget_raspi_interna_muq_T *obj);
static void rpi_arduin_SystemCore_release_m(const
  codertarget_raspi_internal__m_T *obj);
static void rpi_arduino_SystemCore_delete_m(const
  codertarget_raspi_internal__m_T *obj);
static void matlabCodegenHandle_matlabCod_m(codertarget_raspi_internal__m_T *obj);
static void rpi_arduino__SystemCore_release(const
  codertarget_raspi_internal_I2_T *obj);
static void rpi_arduino_r_SystemCore_delete(const
  codertarget_raspi_internal_I2_T *obj);
static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_I2_T *obj);
static void rpi__SystemCore_release_muqgduy(const
  codertarget_raspi_internal_SC_T *obj);
static void rpi_a_SystemCore_delete_muqgduy(const
  codertarget_raspi_internal_SC_T *obj);
static void matlabCodegenHandle_mat_muqgduy(codertarget_raspi_internal_SC_T *obj);
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void rpi_arduino_rw_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(rpi_arduino_rw_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(rpi_arduino_rw_M, 2));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rpi_arduino_rw_M->Timing.TaskCounters.TID[1])++;
  if ((rpi_arduino_rw_M->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.1s, 0.0s] */
    rpi_arduino_rw_M->Timing.TaskCounters.TID[1] = 0;
  }

  (rpi_arduino_rw_M->Timing.TaskCounters.TID[2])++;
  if ((rpi_arduino_rw_M->Timing.TaskCounters.TID[2]) > 99) {/* Sample time: [1.0s, 0.0s] */
    rpi_arduino_rw_M->Timing.TaskCounters.TID[2] = 0;
  }
}

static void rpi_ardu_SystemCore_release_muq(const
  codertarget_raspi_internal_SP_T *obj)
{
  uint32_T PinNameLoc;
  uint32_T MOSIPinLoc;
  uint32_T MISOPinLoc;
  uint32_T SCKPinLoc;
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    PinNameLoc = SPI0_CE0;
    MOSIPinLoc = MW_UNDEFINED_VALUE;
    MISOPinLoc = MW_UNDEFINED_VALUE;
    SCKPinLoc = MW_UNDEFINED_VALUE;
    MW_SPI_Close(obj->MW_SPI_HANDLE, MOSIPinLoc, MISOPinLoc, SCKPinLoc,
                 PinNameLoc);
  }
}

static void rpi_ardui_SystemCore_delete_muq(const
  codertarget_raspi_internal_SP_T *obj)
{
  rpi_ardu_SystemCore_release_muq(obj);
}

static void matlabCodegenHandle_matlabC_muq(codertarget_raspi_internal_SP_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_ardui_SystemCore_delete_muq(obj);
  }
}

static void rpi_ardui_SystemCore_release_mu(const
  codertarget_raspi_internal_SP_T *obj)
{
  uint32_T PinNameLoc;
  uint32_T MOSIPinLoc;
  uint32_T MISOPinLoc;
  uint32_T SCKPinLoc;
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    PinNameLoc = SPI0_CE1;
    MOSIPinLoc = MW_UNDEFINED_VALUE;
    MISOPinLoc = MW_UNDEFINED_VALUE;
    SCKPinLoc = MW_UNDEFINED_VALUE;
    MW_SPI_Close(obj->MW_SPI_HANDLE, MOSIPinLoc, MISOPinLoc, SCKPinLoc,
                 PinNameLoc);
  }
}

static void rpi_arduin_SystemCore_delete_mu(const
  codertarget_raspi_internal_SP_T *obj)
{
  rpi_ardui_SystemCore_release_mu(obj);
}

static void matlabCodegenHandle_matlabCo_mu(codertarget_raspi_internal_SP_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_arduin_SystemCore_delete_mu(obj);
  }
}

static void rpi_ard_SystemCore_release_muqg(const
  raspi_internal_lsm9ds1Block_r_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_I2C_Close(obj->i2cobj_A_G.MW_I2C_HANDLE);
    MW_I2C_Close(obj->i2cobj_MAG.MW_I2C_HANDLE);
  }
}

static void rpi_ardu_SystemCore_delete_muqg(const
  raspi_internal_lsm9ds1Block_r_T *obj)
{
  rpi_ard_SystemCore_release_muqg(obj);
}

static void matlabCodegenHandle_matlab_muqg(raspi_internal_lsm9ds1Block_r_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_ardu_SystemCore_delete_muqg(obj);
  }
}

static void rpi_ar_SystemCore_release_muqgd(codertarget_raspi_internal_mu_T *obj)
{
  if (obj->isInitialized == 1) {
    obj->isInitialized = 2;
  }
}

static void rpi_ard_SystemCore_delete_muqgd(codertarget_raspi_internal_mu_T *obj)
{
  rpi_ar_SystemCore_release_muqgd(obj);
}

static void matlabCodegenHandle_matla_muqgd(codertarget_raspi_internal_mu_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_ard_SystemCore_delete_muqgd(obj);
  }
}

static void rpi_a_SystemCore_release_muqgdu(codertarget_raspi_interna_muq_T *obj)
{
  if (obj->isInitialized == 1) {
    obj->isInitialized = 2;
  }
}

static void rpi_ar_SystemCore_delete_muqgdu(codertarget_raspi_interna_muq_T *obj)
{
  rpi_a_SystemCore_release_muqgdu(obj);
}

static void matlabCodegenHandle_matl_muqgdu(codertarget_raspi_interna_muq_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_ar_SystemCore_delete_muqgdu(obj);
  }
}

static void rpi_arduin_SystemCore_release_m(const
  codertarget_raspi_internal__m_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_I2C_Close(obj->MW_I2C_HANDLE);
  }
}

static void rpi_arduino_SystemCore_delete_m(const
  codertarget_raspi_internal__m_T *obj)
{
  rpi_arduin_SystemCore_release_m(obj);
}

static void matlabCodegenHandle_matlabCod_m(codertarget_raspi_internal__m_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_arduino_SystemCore_delete_m(obj);
  }
}

static void rpi_arduino__SystemCore_release(const
  codertarget_raspi_internal_I2_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_I2C_Close(obj->MW_I2C_HANDLE);
  }
}

static void rpi_arduino_r_SystemCore_delete(const
  codertarget_raspi_internal_I2_T *obj)
{
  rpi_arduino__SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(codertarget_raspi_internal_I2_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_arduino_r_SystemCore_delete(obj);
  }
}

static void rpi__SystemCore_release_muqgduy(const
  codertarget_raspi_internal_SC_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    MW_SCI_Close(obj->MW_SCIHANDLE);
  }
}

static void rpi_a_SystemCore_delete_muqgduy(const
  codertarget_raspi_internal_SC_T *obj)
{
  rpi__SystemCore_release_muqgduy(obj);
}

static void matlabCodegenHandle_mat_muqgduy(codertarget_raspi_internal_SC_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    rpi_a_SystemCore_delete_muqgduy(obj);
  }
}

/* Model step function for TID0 */
void rpi_arduino_rw_step0(void)        /* Sample time: [0.01s, 0.0s] */
{
  uint8_T RxDataLocChar;

  {                                    /* Sample time: [0.01s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* MATLABSystem: '<S4>/Serial Read' */
  if (rpi_arduino_rw_DW.obj_hq.SampleTime !=
      rpi_arduino_rw_P.SerialRead_SampleTime) {
    rpi_arduino_rw_DW.obj_hq.SampleTime = rpi_arduino_rw_P.SerialRead_SampleTime;
  }

  MW_SCI_Receive(rpi_arduino_rw_DW.obj_hq.MW_SCIHANDLE, &RxDataLocChar, 1U);
  memcpy((void *)&rpi_arduino_rw_B.SerialRead_o1, (void *)&RxDataLocChar,
         (uint32_T)((size_t)1 * sizeof(int8_T)));

  /* End of MATLABSystem: '<S4>/Serial Read' */

  /* External mode */
  rtExtModeUploadCheckTrigger(3);
  rtExtModeUpload(0, (real_T)rpi_arduino_rw_M->Timing.taskTime0);

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(rpi_arduino_rw_M)!=-1) &&
        !((rtmGetTFinal(rpi_arduino_rw_M)-rpi_arduino_rw_M->Timing.taskTime0) >
          rpi_arduino_rw_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(rpi_arduino_rw_M, "Simulation finished");
    }

    if (rtmGetStopRequested(rpi_arduino_rw_M)) {
      rtmSetErrorStatus(rpi_arduino_rw_M, "Simulation finished");
    }
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rpi_arduino_rw_M->Timing.taskTime0 =
    (++rpi_arduino_rw_M->Timing.clockTick0) * rpi_arduino_rw_M->Timing.stepSize0;
}

/* Model step function for TID1 */
void rpi_arduino_rw_step1(void)        /* Sample time: [0.1s, 0.0s] */
{
  int16_T b_RegisterValue[3];
  uint8_T SwappedDataBytes;
  uint8_T status;
  uint8_T output_raw[6];
  real_T a[3];
  uint8_T SwappedDataBytes_0[2];
  uint8_T rtb_Switch2[2];
  int32_T i;
  real_T a_0;

  /* MATLABSystem: '<S3>/LSM9DS1 IMU Sensor' */
  status = 24U;
  memcpy((void *)&SwappedDataBytes, (void *)&status, (uint32_T)((size_t)1 *
          sizeof(uint8_T)));
  status = MW_I2C_MasterWrite(rpi_arduino_rw_DW.obj.i2cobj_A_G.MW_I2C_HANDLE,
    106U, &SwappedDataBytes, 1U, true, false);
  if (0 == status) {
    MW_I2C_MasterRead(rpi_arduino_rw_DW.obj.i2cobj_A_G.MW_I2C_HANDLE, 106U,
                      output_raw, 6U, false, true);
    memcpy((void *)&b_RegisterValue[0], (void *)&output_raw[0], (uint32_T)
           ((size_t)3 * sizeof(int16_T)));
  } else {
    b_RegisterValue[0] = 0;
    b_RegisterValue[1] = 0;
    b_RegisterValue[2] = 0;
  }

  memcpy(&rpi_arduino_rw_B.b[0], &rpi_arduino_rw_DW.obj.CalGyroA[0], 9U * sizeof
         (real_T));
  for (i = 0; i < 3; i++) {
    rpi_arduino_rw_B.a[i] = ((rpi_arduino_rw_B.b[3 * i + 1] * (real_T)
      b_RegisterValue[1] + rpi_arduino_rw_B.b[3 * i] * (real_T)b_RegisterValue[0])
      + rpi_arduino_rw_B.b[3 * i + 2] * (real_T)b_RegisterValue[2]) +
      rpi_arduino_rw_DW.obj.CalGyroB[i];
  }

  status = 40U;
  memcpy((void *)&SwappedDataBytes, (void *)&status, (uint32_T)((size_t)1 *
          sizeof(uint8_T)));
  status = MW_I2C_MasterWrite(rpi_arduino_rw_DW.obj.i2cobj_A_G.MW_I2C_HANDLE,
    106U, &SwappedDataBytes, 1U, true, false);
  if (0 == status) {
    MW_I2C_MasterRead(rpi_arduino_rw_DW.obj.i2cobj_A_G.MW_I2C_HANDLE, 106U,
                      output_raw, 6U, false, true);
    memcpy((void *)&b_RegisterValue[0], (void *)&output_raw[0], (uint32_T)
           ((size_t)3 * sizeof(int16_T)));
  } else {
    b_RegisterValue[0] = 0;
    b_RegisterValue[1] = 0;
    b_RegisterValue[2] = 0;
  }

  memcpy(&rpi_arduino_rw_B.b[0], &rpi_arduino_rw_DW.obj.CalAccelA[0], 9U *
         sizeof(real_T));
  for (i = 0; i < 3; i++) {
    a[i] = ((rpi_arduino_rw_B.b[3 * i + 1] * (real_T)b_RegisterValue[1] +
             rpi_arduino_rw_B.b[3 * i] * (real_T)b_RegisterValue[0]) +
            rpi_arduino_rw_B.b[3 * i + 2] * (real_T)b_RegisterValue[2]) +
      rpi_arduino_rw_DW.obj.CalAccelB[i];
  }

  status = 40U;
  memcpy((void *)&SwappedDataBytes, (void *)&status, (uint32_T)((size_t)1 *
          sizeof(uint8_T)));
  status = MW_I2C_MasterWrite(rpi_arduino_rw_DW.obj.i2cobj_MAG.MW_I2C_HANDLE,
    28U, &SwappedDataBytes, 1U, true, false);
  if (0 == status) {
    MW_I2C_MasterRead(rpi_arduino_rw_DW.obj.i2cobj_MAG.MW_I2C_HANDLE, 28U,
                      output_raw, 6U, false, true);
    memcpy((void *)&b_RegisterValue[0], (void *)&output_raw[0], (uint32_T)
           ((size_t)3 * sizeof(int16_T)));
  } else {
    b_RegisterValue[0] = 0;
    b_RegisterValue[1] = 0;
    b_RegisterValue[2] = 0;
  }

  memcpy(&rpi_arduino_rw_B.b[0], &rpi_arduino_rw_DW.obj.CalMagA[0], 9U * sizeof
         (real_T));
  for (i = 0; i < 3; i++) {
    a_0 = ((rpi_arduino_rw_B.b[3 * i + 1] * (real_T)b_RegisterValue[1] +
            rpi_arduino_rw_B.b[3 * i] * (real_T)b_RegisterValue[0]) +
           rpi_arduino_rw_B.b[3 * i + 2] * (real_T)b_RegisterValue[2]) +
      rpi_arduino_rw_DW.obj.CalMagB[i];
    rpi_arduino_rw_B.LSM9DS1IMUSensor_o1[i] = rpi_arduino_rw_B.a[i] * 245.0 /
      32768.0;
    rpi_arduino_rw_B.LSM9DS1IMUSensor_o2[i] = a[i] * 2.0 / 32768.0;
    rpi_arduino_rw_B.LSM9DS1IMUSensor_o3[i] = a_0 * 4.0 / 32768.0;
  }

  /* End of MATLABSystem: '<S3>/LSM9DS1 IMU Sensor' */
  /* MATLABSystem: '<S1>/I2C Master Read' */
  if (rpi_arduino_rw_DW.obj_h.SampleTime !=
      rpi_arduino_rw_P.I2CMasterRead_SampleTime) {
    rpi_arduino_rw_DW.obj_h.SampleTime =
      rpi_arduino_rw_P.I2CMasterRead_SampleTime;
  }

  MW_I2C_MasterRead(rpi_arduino_rw_DW.obj_h.MW_I2C_HANDLE, 1U, &status, 1U,
                    false, false);
  memcpy((void *)&rpi_arduino_rw_B.I2CMasterRead_o1, (void *)&status, (uint32_T)
         ((size_t)1 * sizeof(uint8_T)));

  /* End of MATLABSystem: '<S1>/I2C Master Read' */

  /* Switch: '<S1>/Switch2' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   */
  if (rpi_arduino_rw_B.I2CMasterRead_o1 >= rpi_arduino_rw_P.Switch2_Threshold) {
    /* DataTypeConversion: '<S1>/Data Type Conversion1' incorporates:
     *  Constant: '<S1>/Throttle'
     */
    a_0 = floor(rpi_arduino_rw_P.Throttle_Value);
    if (rtIsNaN(a_0) || rtIsInf(a_0)) {
      a_0 = 0.0;
    } else {
      a_0 = fmod(a_0, 256.0);
    }

    rtb_Switch2[0] = (uint8_T)(a_0 < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
      -a_0 : (int32_T)(uint8_T)a_0);

    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  Constant: '<S1>/Steering'
     *  DataTypeConversion: '<S1>/Data Type Conversion1'
     */
    a_0 = floor(rpi_arduino_rw_P.Steering_Value);
    if (rtIsNaN(a_0) || rtIsInf(a_0)) {
      a_0 = 0.0;
    } else {
      a_0 = fmod(a_0, 256.0);
    }

    rtb_Switch2[1] = (uint8_T)(a_0 < 0.0 ? (int32_T)(uint8_T)-(int8_T)(uint8_T)
      -a_0 : (int32_T)(uint8_T)a_0);
  } else {
    rtb_Switch2[0] = 0U;
    rtb_Switch2[1] = 0U;
  }

  /* End of Switch: '<S1>/Switch2' */

  /* MATLABSystem: '<S1>/I2C Master Write' */
  memcpy((void *)&SwappedDataBytes_0[0], (void *)&rtb_Switch2[0], (uint32_T)
         ((size_t)2 * sizeof(uint8_T)));
  MW_I2C_MasterWrite(rpi_arduino_rw_DW.obj_b.MW_I2C_HANDLE, 1U,
                     SwappedDataBytes_0, 2U, false, false);
  rtExtModeUpload(1, (real_T)((rpi_arduino_rw_M->Timing.clockTick1) * 0.1));

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rpi_arduino_rw_M->Timing.clockTick1++;
}

/* Model step function for TID2 */
void rpi_arduino_rw_step2(void)        /* Sample time: [1.0s, 0.0s] */
{
  uint8_T rdDataRaw1[4];
  uint8_T rdDataRaw[5];
  uint8_T in[5];
  uint32_T PinNameLoc;
  uint8_T status;
  MW_SPI_Mode_type ClockModeValue;
  MW_SPI_FirstBitTransfer_Type MsbFirstTransferLoc;
  real_T rtb_Product5;
  int32_T i;

  /* MATLABSystem: '<S2>/SPI Register Read' */
  if (rpi_arduino_rw_DW.obj_m.SampleTime !=
      rpi_arduino_rw_P.SPIRegisterRead_SampleTime) {
    rpi_arduino_rw_DW.obj_m.SampleTime =
      rpi_arduino_rw_P.SPIRegisterRead_SampleTime;
  }

  for (i = 0; i < 5; i++) {
    in[i] = 0U;
  }

  PinNameLoc = SPI0_CE0;
  MW_SPI_SetSlaveSelect(rpi_arduino_rw_DW.obj_m.MW_SPI_HANDLE, PinNameLoc, true);
  ClockModeValue = MW_SPI_MODE_0;
  MsbFirstTransferLoc = MW_SPI_MOST_SIGNIFICANT_BIT_FIRST;
  status = MW_SPI_SetFormat(rpi_arduino_rw_DW.obj_m.MW_SPI_HANDLE, 8,
    ClockModeValue, MsbFirstTransferLoc);
  if (status == 0) {
    MW_SPI_MasterWriteRead_8bits(rpi_arduino_rw_DW.obj_m.MW_SPI_HANDLE, in,
      rdDataRaw, 5U);
  }

  memcpy((void *)&in[0], (void *)&rdDataRaw[0], (uint32_T)((size_t)5 * sizeof
          (uint8_T)));
  rdDataRaw1[0] = in[1];
  rdDataRaw1[1] = in[2];
  rdDataRaw1[2] = in[3];
  rdDataRaw1[3] = in[4];
  memcpy((void *)&rpi_arduino_rw_B.SPIRegisterRead[0], (void *)&rdDataRaw1[0],
         (uint32_T)((size_t)4 * sizeof(uint8_T)));

  /* End of MATLABSystem: '<S2>/SPI Register Read' */

  /* MATLABSystem: '<S2>/SPI Register Read1' */
  if (rpi_arduino_rw_DW.obj_m4.SampleTime !=
      rpi_arduino_rw_P.SPIRegisterRead1_SampleTime) {
    rpi_arduino_rw_DW.obj_m4.SampleTime =
      rpi_arduino_rw_P.SPIRegisterRead1_SampleTime;
  }

  for (i = 0; i < 5; i++) {
    in[i] = 0U;
  }

  PinNameLoc = SPI0_CE1;
  MW_SPI_SetSlaveSelect(rpi_arduino_rw_DW.obj_m4.MW_SPI_HANDLE, PinNameLoc, true);
  ClockModeValue = MW_SPI_MODE_0;
  MsbFirstTransferLoc = MW_SPI_MOST_SIGNIFICANT_BIT_FIRST;
  status = MW_SPI_SetFormat(rpi_arduino_rw_DW.obj_m4.MW_SPI_HANDLE, 8,
    ClockModeValue, MsbFirstTransferLoc);
  if (status == 0) {
    MW_SPI_MasterWriteRead_8bits(rpi_arduino_rw_DW.obj_m4.MW_SPI_HANDLE, in,
      rdDataRaw, 5U);
  }

  memcpy((void *)&in[0], (void *)&rdDataRaw[0], (uint32_T)((size_t)5 * sizeof
          (uint8_T)));
  rdDataRaw1[0] = in[1];
  rdDataRaw1[1] = in[2];
  rdDataRaw1[2] = in[3];
  rdDataRaw1[3] = in[4];
  memcpy((void *)&rpi_arduino_rw_B.SPIRegisterRead1[0], (void *)&rdDataRaw1[0],
         (uint32_T)((size_t)4 * sizeof(uint8_T)));

  /* End of MATLABSystem: '<S2>/SPI Register Read1' */

  /* Product: '<S2>/Product1' incorporates:
   *  Constant: '<S2>/4_pulses_very_rotation'
   *  Constant: '<S2>/mm_to_m'
   *  Constant: '<S2>/wheel_cirumfirence_in_mm'
   */
  rtb_Product5 = rpi_arduino_rw_P.wheel_cirumfirence_in_mm_Value *
    rpi_arduino_rw_P.mm_to_m_Value *
    rpi_arduino_rw_P.u_pulses_very_rotation_Value;

  /* Product: '<S2>/Product2' */
  rpi_arduino_rw_B.Product2 = (real_T)rpi_arduino_rw_B.SPIRegisterRead[2] *
    rtb_Product5;

  /* Product: '<S2>/Product' */
  rpi_arduino_rw_B.Product = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead[1];

  /* Product: '<S2>/Product4' */
  rpi_arduino_rw_B.Product4 = (real_T)rpi_arduino_rw_B.SPIRegisterRead1[2] *
    rtb_Product5;

  /* Product: '<S2>/Product3' */
  rpi_arduino_rw_B.Product3 = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead1[1];

  /* SignalConversion: '<S2>/TmpSignal ConversionAtTo WorkspaceInport1' */
  rpi_arduino_rw_B.TmpSignalConversionAtToWorkspac[0] =
    rpi_arduino_rw_B.Product2;
  rpi_arduino_rw_B.TmpSignalConversionAtToWorkspac[1] = rpi_arduino_rw_B.Product;
  rpi_arduino_rw_B.TmpSignalConversionAtToWorkspac[2] =
    rpi_arduino_rw_B.Product4;
  rpi_arduino_rw_B.TmpSignalConversionAtToWorkspac[3] =
    rpi_arduino_rw_B.Product3;

  /* Product: '<S2>/Product5' incorporates:
   *  Constant: '<S2>/4_pulses_very_rotation'
   *  Constant: '<S2>/cycle_time_in_ms'
   *  Constant: '<S2>/ms_to_min'
   */
  rtb_Product5 = rpi_arduino_rw_P.u_pulses_very_rotation_Value *
    rpi_arduino_rw_P.cycle_time_in_ms_Value * rpi_arduino_rw_P.ms_to_min_Value;

  /* Product: '<S2>/Product6' */
  rpi_arduino_rw_B.Product6 = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead1[2];

  /* Product: '<S2>/Product7' */
  rpi_arduino_rw_B.Product7 = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead1[1];

  /* Product: '<S2>/Product8' */
  rpi_arduino_rw_B.Product8 = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead[2];

  /* Product: '<S2>/Product9' */
  rpi_arduino_rw_B.Product9 = rtb_Product5 * (real_T)
    rpi_arduino_rw_B.SPIRegisterRead[1];
  rtExtModeUpload(2, (real_T)((rpi_arduino_rw_M->Timing.clockTick2) * 1.0));

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 1.0, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  rpi_arduino_rw_M->Timing.clockTick2++;
}

/* Model step wrapper function for compatibility with a static main program */
void rpi_arduino_rw_step(int_T tid)
{
  switch (tid) {
   case 0 :
    rpi_arduino_rw_step0();
    break;

   case 1 :
    rpi_arduino_rw_step1();
    break;

   case 2 :
    rpi_arduino_rw_step2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void rpi_arduino_rw_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)rpi_arduino_rw_M, 0,
                sizeof(RT_MODEL_rpi_arduino_rw_T));
  rtmSetTFinal(rpi_arduino_rw_M, -1);
  rpi_arduino_rw_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  rpi_arduino_rw_M->Sizes.checksums[0] = (4150052482U);
  rpi_arduino_rw_M->Sizes.checksums[1] = (2541565079U);
  rpi_arduino_rw_M->Sizes.checksums[2] = (3763652915U);
  rpi_arduino_rw_M->Sizes.checksums[3] = (1289365057U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
    rpi_arduino_rw_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(rpi_arduino_rw_M->extModeInfo,
      &rpi_arduino_rw_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(rpi_arduino_rw_M->extModeInfo,
                        rpi_arduino_rw_M->Sizes.checksums);
    rteiSetTPtr(rpi_arduino_rw_M->extModeInfo, rtmGetTPtr(rpi_arduino_rw_M));
  }

  /* block I/O */
  (void) memset(((void *) &rpi_arduino_rw_B), 0,
                sizeof(B_rpi_arduino_rw_T));

  /* states (dwork) */
  (void) memset((void *)&rpi_arduino_rw_DW, 0,
                sizeof(DW_rpi_arduino_rw_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    rpi_arduino_rw_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    codertarget_raspi_internal_SP_T *obj;
    raspi_internal_lsm9ds1Block_r_T *obj_0;
    uint8_T b_SwappedDataBytes[2];
    uint8_T SwappedDataBytes[2];
    uint8_T CastedData;
    codertarget_raspi_internal__m_T *obj_1;
    codertarget_raspi_internal_I2_T *obj_2;
    codertarget_raspi_internal_SC_T *obj_3;
    MW_SCI_Parity_Type ParityValue;
    static const int8_T tmp[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

    static const char_T tmp_0[12] = { '/', 'd', 'e', 'v', '/', 't', 't', 'y',
      'U', 'S', 'B', '0' };

    int32_T i;

    /* Start for MATLABSystem: '<S2>/SPI Register Read' */
    rpi_arduino_rw_DW.obj_m.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj_m.isInitialized = 0;
    rpi_arduino_rw_DW.obj_m.matlabCodegenIsDeleted = false;
    rpi_arduino_rw_DW.obj_m.SampleTime =
      rpi_arduino_rw_P.SPIRegisterRead_SampleTime;
    obj = &rpi_arduino_rw_DW.obj_m;
    rpi_arduino_rw_DW.obj_m.isSetupComplete = false;
    rpi_arduino_rw_DW.obj_m.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = SPI0_CE0;
    rpi_arduino_rw_B.MOSIPinLoc = MW_UNDEFINED_VALUE;
    rpi_arduino_rw_B.MISOPinLoc = MW_UNDEFINED_VALUE;
    rpi_arduino_rw_B.SCKPinLoc = MW_UNDEFINED_VALUE;
    obj->MW_SPI_HANDLE = MW_SPI_Open(0U, rpi_arduino_rw_B.MOSIPinLoc,
      rpi_arduino_rw_B.MISOPinLoc, rpi_arduino_rw_B.SCKPinLoc,
      rpi_arduino_rw_B.SSPinNameLoc, true, 0);
    MW_SPI_SetBusSpeed(rpi_arduino_rw_DW.obj_m.MW_SPI_HANDLE, 500000U);
    rpi_arduino_rw_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<S2>/SPI Register Read1' */
    rpi_arduino_rw_DW.obj_m4.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj_m4.isInitialized = 0;
    rpi_arduino_rw_DW.obj_m4.matlabCodegenIsDeleted = false;
    rpi_arduino_rw_DW.obj_m4.SampleTime =
      rpi_arduino_rw_P.SPIRegisterRead1_SampleTime;
    obj = &rpi_arduino_rw_DW.obj_m4;
    rpi_arduino_rw_DW.obj_m4.isSetupComplete = false;
    rpi_arduino_rw_DW.obj_m4.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = SPI0_CE1;
    rpi_arduino_rw_B.MOSIPinLoc = MW_UNDEFINED_VALUE;
    rpi_arduino_rw_B.MISOPinLoc = MW_UNDEFINED_VALUE;
    rpi_arduino_rw_B.SCKPinLoc = MW_UNDEFINED_VALUE;
    obj->MW_SPI_HANDLE = MW_SPI_Open(0U, rpi_arduino_rw_B.MOSIPinLoc,
      rpi_arduino_rw_B.MISOPinLoc, rpi_arduino_rw_B.SCKPinLoc,
      rpi_arduino_rw_B.SSPinNameLoc, true, 0);
    MW_SPI_SetBusSpeed(rpi_arduino_rw_DW.obj_m4.MW_SPI_HANDLE, 500000U);
    rpi_arduino_rw_DW.obj_m4.isSetupComplete = true;

    /* Start for MATLABSystem: '<S3>/LSM9DS1 IMU Sensor' */
    rpi_arduino_rw_DW.obj.i2cobj_MAG.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj.i2cobj_A_G.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj.matlabCodegenIsDeleted = true;
    obj_0 = &rpi_arduino_rw_DW.obj;
    for (i = 0; i < 9; i++) {
      rpi_arduino_rw_DW.obj.CalGyroA[i] = tmp[i];
    }

    rpi_arduino_rw_DW.obj.CalGyroB[0] = 0.0;
    rpi_arduino_rw_DW.obj.CalGyroB[1] = 0.0;
    rpi_arduino_rw_DW.obj.CalGyroB[2] = 0.0;
    for (i = 0; i < 9; i++) {
      rpi_arduino_rw_DW.obj.CalAccelA[i] = tmp[i];
    }

    rpi_arduino_rw_DW.obj.CalAccelB[0] = 0.0;
    rpi_arduino_rw_DW.obj.CalAccelB[1] = 0.0;
    rpi_arduino_rw_DW.obj.CalAccelB[2] = 0.0;
    for (i = 0; i < 9; i++) {
      rpi_arduino_rw_DW.obj.CalMagA[i] = tmp[i];
    }

    rpi_arduino_rw_DW.obj.CalMagB[0] = 0.0;
    rpi_arduino_rw_DW.obj.CalMagB[1] = 0.0;
    rpi_arduino_rw_DW.obj.CalMagB[2] = 0.0;
    rpi_arduino_rw_DW.obj.isInitialized = 0;
    obj_0->i2cobj_A_G.isInitialized = 0;
    obj_0->i2cobj_A_G.matlabCodegenIsDeleted = false;
    obj_0->i2cobj_MAG.isInitialized = 0;
    obj_0->i2cobj_MAG.matlabCodegenIsDeleted = false;
    rpi_arduino_rw_DW.obj.matlabCodegenIsDeleted = false;
    obj_0 = &rpi_arduino_rw_DW.obj;
    rpi_arduino_rw_DW.obj.isSetupComplete = false;
    rpi_arduino_rw_DW.obj.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = 1;
    obj_0->i2cobj_A_G.MW_I2C_HANDLE = MW_I2C_Open(rpi_arduino_rw_B.SSPinNameLoc,
      0);
    obj_0->i2cobj_A_G.BusSpeed = 100000U;
    MW_I2C_SetBusSpeed(obj_0->i2cobj_A_G.MW_I2C_HANDLE,
                       obj_0->i2cobj_A_G.BusSpeed);
    CastedData = 96U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 16U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 17U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 18U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 56U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 30U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 19U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 56U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 31U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 103U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 32U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 33U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 4U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 34U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_A_G.MW_I2C_HANDLE, 106U, SwappedDataBytes,
                       2U, false, false);
    rpi_arduino_rw_B.SSPinNameLoc = 1;
    obj_0->i2cobj_MAG.MW_I2C_HANDLE = MW_I2C_Open(rpi_arduino_rw_B.SSPinNameLoc,
      0);
    obj_0->i2cobj_MAG.BusSpeed = 100000U;
    MW_I2C_SetBusSpeed(obj_0->i2cobj_MAG.MW_I2C_HANDLE,
                       obj_0->i2cobj_MAG.BusSpeed);
    CastedData = 24U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 32U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_MAG.MW_I2C_HANDLE, 28U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 33U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_MAG.MW_I2C_HANDLE, 28U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 34U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_MAG.MW_I2C_HANDLE, 28U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 35U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_MAG.MW_I2C_HANDLE, 28U, SwappedDataBytes,
                       2U, false, false);
    CastedData = 0U;
    memcpy((void *)&b_SwappedDataBytes[1], (void *)&CastedData, (uint32_T)
           ((size_t)1 * sizeof(uint8_T)));
    b_SwappedDataBytes[0] = 36U;
    memcpy((void *)&SwappedDataBytes[0], (void *)&b_SwappedDataBytes[0],
           (uint32_T)((size_t)2 * sizeof(uint8_T)));
    MW_I2C_MasterWrite(obj_0->i2cobj_MAG.MW_I2C_HANDLE, 28U, SwappedDataBytes,
                       2U, false, false);
    rpi_arduino_rw_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/LSM9DS1 IMU Sensor' */
    /* Start for MATLABSystem: '<S1>/I2C Master Read' */
    rpi_arduino_rw_DW.obj_h.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj_h.isInitialized = 0;
    rpi_arduino_rw_DW.obj_h.matlabCodegenIsDeleted = false;
    rpi_arduino_rw_DW.obj_h.SampleTime =
      rpi_arduino_rw_P.I2CMasterRead_SampleTime;
    obj_1 = &rpi_arduino_rw_DW.obj_h;
    rpi_arduino_rw_DW.obj_h.isSetupComplete = false;
    rpi_arduino_rw_DW.obj_h.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = 1;
    obj_1->MW_I2C_HANDLE = MW_I2C_Open(rpi_arduino_rw_B.SSPinNameLoc, 0);
    rpi_arduino_rw_DW.obj_h.BusSpeed = 100000U;
    MW_I2C_SetBusSpeed(rpi_arduino_rw_DW.obj_h.MW_I2C_HANDLE,
                       rpi_arduino_rw_DW.obj_h.BusSpeed);
    rpi_arduino_rw_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/I2C Master Write' */
    rpi_arduino_rw_DW.obj_b.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj_b.isInitialized = 0;
    rpi_arduino_rw_DW.obj_b.matlabCodegenIsDeleted = false;
    obj_2 = &rpi_arduino_rw_DW.obj_b;
    rpi_arduino_rw_DW.obj_b.isSetupComplete = false;
    rpi_arduino_rw_DW.obj_b.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = 1;
    obj_2->MW_I2C_HANDLE = MW_I2C_Open(rpi_arduino_rw_B.SSPinNameLoc, 0);
    rpi_arduino_rw_DW.obj_b.BusSpeed = 100000U;
    MW_I2C_SetBusSpeed(rpi_arduino_rw_DW.obj_b.MW_I2C_HANDLE,
                       rpi_arduino_rw_DW.obj_b.BusSpeed);
    rpi_arduino_rw_DW.obj_b.isSetupComplete = true;

    /* Start for MATLABSystem: '<S4>/Serial Read' */
    rpi_arduino_rw_DW.obj_hq.matlabCodegenIsDeleted = true;
    rpi_arduino_rw_DW.obj_hq.isInitialized = 0;
    rpi_arduino_rw_DW.obj_hq.matlabCodegenIsDeleted = false;
    rpi_arduino_rw_DW.obj_hq.SampleTime = rpi_arduino_rw_P.SerialRead_SampleTime;
    obj_3 = &rpi_arduino_rw_DW.obj_hq;
    rpi_arduino_rw_DW.obj_hq.isSetupComplete = false;
    rpi_arduino_rw_DW.obj_hq.isInitialized = 1;
    rpi_arduino_rw_B.SSPinNameLoc = MW_UNDEFINED_VALUE;
    rpi_arduino_rw_B.MOSIPinLoc = MW_UNDEFINED_VALUE;
    for (i = 0; i < 12; i++) {
      rpi_arduino_rw_B.SCIModuleLoc[i] = tmp_0[i];
    }

    rpi_arduino_rw_B.SCIModuleLoc[12] = '\x00';
    obj_3->MW_SCIHANDLE = MW_SCI_Open(rpi_arduino_rw_B.SCIModuleLoc, true,
      rpi_arduino_rw_B.SSPinNameLoc, rpi_arduino_rw_B.MOSIPinLoc);
    MW_SCI_SetBaudrate(rpi_arduino_rw_DW.obj_hq.MW_SCIHANDLE, 9600U);
    rpi_arduino_rw_B.StopBitsValue = MW_SCI_STOPBITS_1;
    ParityValue = MW_SCI_PARITY_NONE;
    MW_SCI_SetFrameFormat(rpi_arduino_rw_DW.obj_hq.MW_SCIHANDLE, 8, ParityValue,
                          rpi_arduino_rw_B.StopBitsValue);
    rpi_arduino_rw_DW.obj_hq.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/Serial Read' */
  }
}

/* Model terminate function */
void rpi_arduino_rw_terminate(void)
{
  /* Terminate for MATLABSystem: '<S2>/SPI Register Read' */
  matlabCodegenHandle_matlabC_muq(&rpi_arduino_rw_DW.obj_m);

  /* Terminate for MATLABSystem: '<S2>/SPI Register Read1' */
  matlabCodegenHandle_matlabCo_mu(&rpi_arduino_rw_DW.obj_m4);

  /* Terminate for MATLABSystem: '<S3>/LSM9DS1 IMU Sensor' */
  matlabCodegenHandle_matlab_muqg(&rpi_arduino_rw_DW.obj);
  matlabCodegenHandle_matla_muqgd(&rpi_arduino_rw_DW.obj.i2cobj_A_G);
  matlabCodegenHandle_matl_muqgdu(&rpi_arduino_rw_DW.obj.i2cobj_MAG);

  /* Terminate for MATLABSystem: '<S1>/I2C Master Read' */
  matlabCodegenHandle_matlabCod_m(&rpi_arduino_rw_DW.obj_h);

  /* Terminate for MATLABSystem: '<S1>/I2C Master Write' */
  matlabCodegenHandle_matlabCodeg(&rpi_arduino_rw_DW.obj_b);

  /* Terminate for MATLABSystem: '<S4>/Serial Read' */
  matlabCodegenHandle_mat_muqgduy(&rpi_arduino_rw_DW.obj_hq);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
