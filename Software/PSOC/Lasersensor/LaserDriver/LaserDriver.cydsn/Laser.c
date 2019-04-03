/* ========================================
 *
 * Copyright Nicklas Grunert, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Nicklas Grunert.
 *
 * ========================================
*/
#include "Laser.h"
#include "Laser_def.h"

/******* I/O Functions **********/

// Start continuous ranging measurements. If period_ms (optional) is 0 or not
// given, continuous back-to-back mode is used (the sensor takes measurements as
// often as possible); otherwise, continuous timed mode is used, with the given
// inter-measurement period in milliseconds determining how often the sensor
// takes a measurement.
// based on VL53L0X_StartMeasurement()
void Laser::StartContinuous(uint32_t period_ms)
{
    I2C.WriteByte(dev_,0x80, 0x01);
    I2C.WriteByte(dev_,0xFF, 0x01);
    I2C.WriteByte(dev_,0x00, 0x00);
    I2C.WriteByte(dev_,0x91, stop_variable);
    I2C.WriteByte(dev_,0x00, 0x01);
    I2C.WriteByte(dev_,0xFF, 0x00);
    I2C.WriteByte(dev_,0x80, 0x00);

    if (period_ms != 0)
    {
        // continuous timed mode
        uint8_t tmparr[4]={0,0,0,0};
        
        // VL53L0X_SetInterMeasurementPeriodMilliSeconds() begin
        I2C.ReadBytes(dev_,OSC_CALIBRATE_VAL,2,tmparr); //readReg16Bit(OSC_CALIBRATE_VAL);
        uint16_t osc_calibrate_val = (tmparr[0]<<8) + tmparr[1];
        tmparr[0]=0;tmparr[1]=0;tmparr[2]=0;tmparr[3]=0; // Might be useless
        
        if (osc_calibrate_val != 0)
        {
            period_ms *= osc_calibrate_val;
        }

        //writeReg32Bit(SYSTEM_INTERMEASUREMENT_PERIOD, period_ms);
        /*Make 32Bit into 4 8Bit*/
        /*https://www.edaboard.com/showthread.php?60002-How-to-efficiently-convert-the-32-bit-data-into-8-bit-data*/
        tmparr[0] = period_ms;      // Lower order
        tmparr[1] = period_ms >> 8;
        tmparr[2] = period_ms >> 16;
        tmparr[3] = period_ms >> 24;// Higher order
        
        I2C.WriteBytes(dev_,SYSTEM_INTERMEASUREMENT_PERIOD, 4, tmparr);
        
        
        // VL53L0X_SetInterMeasurementPeriodMilliSeconds() end

        I2C.WriteByte(dev_,SYSRANGE_START, 0x04); // VL53L0X_REG_SYSRANGE_MODE_TIMED
    }
    else
    {
        // continuous back-to-back mode
        I2C.WriteByte(dev_,SYSRANGE_START, 0x02); // VL53L0X_REG_SYSRANGE_MODE_BACKTOBACK
    }
}

// Stop continuous measurements
// based on VL53L0X_StopMeasurement()
void Laser::StopContinuous(void)
{
  I2C.WriteByte(dev_,SYSRANGE_START, 0x01); // VL53L0X_REG_SYSRANGE_MODE_SINGLESHOT

  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x00, 0x00);
  I2C.WriteByte(dev_,0x91, 0x00);
  I2C.WriteByte(dev_,0x00, 0x01);
  I2C.WriteByte(dev_,0xFF, 0x00);
}

// Returns a range reading in millimeters when continuous mode is active
// (readRangeSingleMillimeters() also calls this function after starting a
// single-shot range measurement)
uint16_t Laser::ReadRangeContinuousMillimeters(void)
{
    //TODO: Fix timeouts to avoid deadlocking etc.
    //startTimeout();
    uint8_t tmp = 0;
    while ((tmp & 0x07) == 0)
    {
        if (/*checkTimeoutExpired()*/0)
        {
        //did_timeout = true;
        return 65535;   // Probably returns max-range if there was an error
        }
        I2C.ReadByte(dev_,RESULT_INTERRUPT_STATUS,&tmp); //readReg(RESULT_INTERRUPT_STATUS)
    }

    // assumptions: Linearity Corrective Gain is 1000 (default);
    // fractional ranging is not enabled
    // readReg16Bit with PSoC
    uint8_t range8bit[2];
    I2C.ReadBytes(dev_,RESULT_RANGE_STATUS+10,2,range8bit);
    uint16_t range = (range8bit[0]<<8) + range8bit[1];
    
    //writeReg(SYSTEM_INTERRUPT_CLEAR, 0x01);
    I2C.WriteByte(dev_,SYSTEM_INTERRUPT_CLEAR,0x01);
    return range;
}

/******* Init functions *********/
bool Laser::Init(bool io_2v8)
{ 
    I2CInit();
    DataInit(io_2v8);
    StaticInit();
    PerformRefCalibration();
    return true;
}

bool Laser::PerformRefCalibration()
{
    // -- VL53L0X_perform_vhv_calibration() begin
    I2C.WriteByte(dev_,SYSTEM_SEQUENCE_CONFIG, 0x01);
    if (!performSingleRefCalibration(0x40)) { return false; }
    // -- VL53L0X_perform_vhv_calibration() end

    // -- VL53L0X_perform_phase_calibration() begin
    I2C.WriteByte(dev_,SYSTEM_SEQUENCE_CONFIG, 0x02);
    if (!performSingleRefCalibration(0x00)) { return false; }
    // -- VL53L0X_perform_phase_calibration() end

    // "restore the previous Sequence Config"
    I2C.WriteByte(dev_,SYSTEM_SEQUENCE_CONFIG, 0xE8);
    return true;
}

void Laser::StaticInit()
{
    uint8_t spad_count;
    bool spad_type_is_aperture;
    if (!getSpadInfo(&spad_count, &spad_type_is_aperture)) { return; }
    
    // The SPAD map (RefGoodSpadMap) is read by VL53L0X_get_info_from_device() in
    // the API, but the same data seems to be more easily readable from
    // GLOBAL_CONFIG_SPAD_ENABLES_REF_0 through _6, so read it from there
    uint8_t ref_spad_map[6];
    I2C.ReadBytes(dev_,GLOBAL_CONFIG_SPAD_ENABLES_REF_0, 6,ref_spad_map);

    // -- VL53L0X_set_reference_spads() begin (assume NVM values are valid)
    I2C.WriteByte(dev_,0xFF, 0x01);
    I2C.WriteByte(dev_,DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
    I2C.WriteByte(dev_,DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
    I2C.WriteByte(dev_,0xFF, 0x00);
    I2C.WriteByte(dev_,GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);

    uint8_t first_spad_to_enable = spad_type_is_aperture ? 12 : 0; // 12 is the first aperture spad
    uint8_t spads_enabled = 0;
    
    /*this is fucking magic thanks pololu*/
    for (uint8_t i = 0; i < 48; i++)
    {
        if (i < first_spad_to_enable || spads_enabled == spad_count)
        {
          // This bit is lower than the first one that should be enabled, or
          // (reference_spad_count) bits have already been enabled, so zero this bit
          ref_spad_map[i / 8] &= ~(1 << (i % 8));
        }
        else if ((ref_spad_map[i / 8] >> (i % 8)) & 0x1)
        {
          spads_enabled++;
        }
    }
    
    I2C.WriteBytes(dev_,GLOBAL_CONFIG_SPAD_ENABLES_REF_0,6,ref_spad_map);
    LoadTuningSettings();
    SetGpioConfig();
    
    uint32_t measurement_timing_budget_us = getMeasurementTimingBudget();
    
    // "Disable MSRC and TCC by default"
    // MSRC = Minimum Signal Rate Check
    // TCC = Target CentreCheck
    // -- VL53L0X_SetSequenceStepEnable() begin
    I2C.WriteByte(dev_,SYSTEM_SEQUENCE_CONFIG, 0xE8);
    // -- VL53L0X_SetSequenceStepEnable() end
    
    // "Recalculate timing budget"
    setMeasurementTimingBudget(measurement_timing_budget_us);
    
    //END
}

// Set the measurement timing budget in microseconds, which is the time allowed
// for one measurement; the ST API and this library take care of splitting the
// timing budget among the sub-steps in the ranging sequence. A longer timing
// budget allows for more accurate measurements. Increasing the budget by a
// factor of N decreases the range measurement standard deviation by a factor of
// sqrt(N). Defaults to about 33 milliseconds; the minimum is 20 ms.
// based on VL53L0X_set_measurement_timing_budget_micro_seconds()
bool Laser::setMeasurementTimingBudget(uint32_t budget_us)
{
  SequenceStepEnables enables;
  SequenceStepTimeouts timeouts;

  uint16_t const StartOverhead      = 1320; // note that this is different than the value in get_
  uint16_t const EndOverhead        = 960;
  uint16_t const MsrcOverhead       = 660;
  uint16_t const TccOverhead        = 590;
  uint16_t const DssOverhead        = 690;
  uint16_t const PreRangeOverhead   = 660;
  uint16_t const FinalRangeOverhead = 550;

  uint32_t const MinTimingBudget = 20000;

  if (budget_us < MinTimingBudget) { return false; }

  uint32_t used_budget_us = StartOverhead + EndOverhead;

  getSequenceStepEnables(&enables);
  getSequenceStepTimeouts(&enables, &timeouts);

  if (enables.tcc)
  {
    used_budget_us += (timeouts.msrc_dss_tcc_us + TccOverhead);
  }

  if (enables.dss)
  {
    used_budget_us += 2 * (timeouts.msrc_dss_tcc_us + DssOverhead);
  }
  else if (enables.msrc)
  {
    used_budget_us += (timeouts.msrc_dss_tcc_us + MsrcOverhead);
  }

  if (enables.pre_range)
  {
    used_budget_us += (timeouts.pre_range_us + PreRangeOverhead);
  }

  if (enables.final_range)
  {
    used_budget_us += FinalRangeOverhead;

    // "Note that the final range timeout is determined by the timing
    // budget and the sum of all other timeouts within the sequence.
    // If there is no room for the final range timeout, then an error
    // will be set. Otherwise the remaining time will be applied to
    // the final range."

    if (used_budget_us > budget_us)
    {
      // "Requested timeout too big."
      return false;
    }

    uint32_t final_range_timeout_us = budget_us - used_budget_us;

    // set_sequence_step_timeout() begin
    // (SequenceStepId == VL53L0X_SEQUENCESTEP_FINAL_RANGE)

    // "For the final range timeout, the pre-range timeout
    //  must be added. To do this both final and pre-range
    //  timeouts must be expressed in macro periods MClks
    //  because they have different vcsel periods."

    uint16_t final_range_timeout_mclks =
      timeoutMicrosecondsToMclks(final_range_timeout_us,
                                 timeouts.final_range_vcsel_period_pclks);

    if (enables.pre_range)
    {
      final_range_timeout_mclks += timeouts.pre_range_mclks;
    }

    uint8_t tmparray[2]={0,0};
    uint16_t tmp = encodeTimeout(final_range_timeout_mclks);
    tmparray[0] = tmp & 0xff;   // Low
    tmparray[1] = (tmp >> 8);   // High
    I2C.WriteBytes(dev_,FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI,2,tmparray);
    
    // set_sequence_step_timeout() end

    measurement_timing_budget_us = budget_us; // store for internal reuse
  }
  return true;
}

// Get the measurement timing budget in microseconds
// based on VL53L0X_get_measurement_timing_budget_micro_seconds()
// in us
uint32_t Laser::getMeasurementTimingBudget(void)
{
  SequenceStepEnables enables;
  SequenceStepTimeouts timeouts;

  uint16_t const StartOverhead     = 1910; // note that this is different than the value in set_
  uint16_t const EndOverhead        = 960;
  uint16_t const MsrcOverhead       = 660;
  uint16_t const TccOverhead        = 590;
  uint16_t const DssOverhead        = 690;
  uint16_t const PreRangeOverhead   = 660;
  uint16_t const FinalRangeOverhead = 550;

  // "Start and end overhead times always present"
  uint32_t budget_us = StartOverhead + EndOverhead;

  getSequenceStepEnables(&enables);
  getSequenceStepTimeouts(&enables, &timeouts);

  if (enables.tcc)
  {
    budget_us += (timeouts.msrc_dss_tcc_us + TccOverhead);
  }

  if (enables.dss)
  {
    budget_us += 2 * (timeouts.msrc_dss_tcc_us + DssOverhead);
  }
  else if (enables.msrc)
  {
    budget_us += (timeouts.msrc_dss_tcc_us + MsrcOverhead);
  }

  if (enables.pre_range)
  {
    budget_us += (timeouts.pre_range_us + PreRangeOverhead);
  }

  if (enables.final_range)
  {
    budget_us += (timeouts.final_range_us + FinalRangeOverhead);
  }

  measurement_timing_budget_us = budget_us; // store for internal reuse
  return budget_us;
}

// Get sequence step enables
// based on VL53L0X_GetSequenceStepEnables()
void Laser::getSequenceStepEnables(SequenceStepEnables * enables)
{
    uint8_t sequence_config;
    I2C.ReadByte(dev_,SYSTEM_SEQUENCE_CONFIG,&sequence_config);

    enables->tcc          = (sequence_config >> 4) & 0x1;
    enables->dss          = (sequence_config >> 3) & 0x1;
    enables->msrc         = (sequence_config >> 2) & 0x1;
    enables->pre_range    = (sequence_config >> 6) & 0x1;
    enables->final_range  = (sequence_config >> 7) & 0x1;
}

// Get sequence step timeouts
// based on get_sequence_step_timeout(),
// but gets all timeouts instead of just the requested one, and also stores
// intermediate values
void Laser::getSequenceStepTimeouts(SequenceStepEnables const * enables, SequenceStepTimeouts * timeouts)
{
  uint8_t tmpdata;
  timeouts->pre_range_vcsel_period_pclks = getVcselPulsePeriod(VcselPeriodPreRange);

  I2C.ReadBytes(dev_,MSRC_CONFIG_TIMEOUT_MACROP,1,&tmpdata);
  timeouts->msrc_dss_tcc_mclks = tmpdata + 1;
  timeouts->msrc_dss_tcc_us =
    timeoutMclksToMicroseconds(timeouts->msrc_dss_tcc_mclks,
                               timeouts->pre_range_vcsel_period_pclks);

  uint16_t  tmp16bit = 0;
  uint8_t   tmp8bit[2];
  I2C.ReadBytes(dev_,PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI,2,tmp8bit);
  tmp16bit = (tmp8bit[0] << 8) + tmp8bit[1];

  timeouts->pre_range_mclks =
    decodeTimeout(tmp16bit);
  timeouts->pre_range_us =
    timeoutMclksToMicroseconds(timeouts->pre_range_mclks,
                               timeouts->pre_range_vcsel_period_pclks);

  timeouts->final_range_vcsel_period_pclks = getVcselPulsePeriod((vcselPeriodType)VcselPeriodFinalRange);

  I2C.ReadBytes(dev_,FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI,2,tmp8bit);
  tmp16bit = (tmp8bit[0] << 8) + tmp8bit[1];
  timeouts->final_range_mclks =
    decodeTimeout(tmp16bit);

  if (enables->pre_range)
  {
    timeouts->final_range_mclks -= timeouts->pre_range_mclks;
  }

  timeouts->final_range_us =
    timeoutMclksToMicroseconds(timeouts->final_range_mclks,
                               timeouts->final_range_vcsel_period_pclks);
}

// Decode sequence step timeout in MCLKs from register value
// based on VL53L0X_decode_timeout()
// Note: the original function returned a uint32_t, but the return value is
// always stored in a uint16_t.
uint16_t Laser::decodeTimeout(uint16_t reg_val)
{
  // format: "(LSByte * 2^MSByte) + 1"
  return (uint16_t)((reg_val & 0x00FF) <<
         (uint16_t)((reg_val & 0xFF00) >> 8)) + 1;
}

// Get the VCSEL pulse period in PCLKs for the given period type.
// based on VL53L0X_get_vcsel_pulse_period()
uint8_t Laser::getVcselPulsePeriod(vcselPeriodType type)
{
    uint8_t tmp = 0;
    if (type == VcselPeriodPreRange)
    {
        I2C.ReadByte(dev_,PRE_RANGE_CONFIG_VCSEL_PERIOD,&tmp);
        return decodeVcselPeriod(tmp);
    }
    else if (type == VcselPeriodFinalRange)
    {
        I2C.ReadByte(dev_,FINAL_RANGE_CONFIG_VCSEL_PERIOD,&tmp);
        return decodeVcselPeriod(tmp);
    }
    else { return 255; }
}

void Laser::LoadTuningSettings()
{
  // -- VL53L0X_load_tuning_settings() begin
  // DefaultTuningSettings from vl53l0x_tuning.h
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x00, 0x00);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x09, 0x00);
  I2C.WriteByte(dev_,0x10, 0x00);
  I2C.WriteByte(dev_,0x11, 0x00);
  I2C.WriteByte(dev_,0x24, 0x01);
  I2C.WriteByte(dev_,0x25, 0xFF);
  I2C.WriteByte(dev_,0x75, 0x00);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x4E, 0x2C);
  I2C.WriteByte(dev_,0x48, 0x00);
  I2C.WriteByte(dev_,0x30, 0x20);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x30, 0x09);
  I2C.WriteByte(dev_,0x54, 0x00);
  I2C.WriteByte(dev_,0x31, 0x04);
  I2C.WriteByte(dev_,0x32, 0x03);
  I2C.WriteByte(dev_,0x40, 0x83);
  I2C.WriteByte(dev_,0x46, 0x25);
  I2C.WriteByte(dev_,0x60, 0x00);
  I2C.WriteByte(dev_,0x27, 0x00);
  I2C.WriteByte(dev_,0x50, 0x06);
  I2C.WriteByte(dev_,0x51, 0x00);
  I2C.WriteByte(dev_,0x52, 0x96);
  I2C.WriteByte(dev_,0x56, 0x08);
  I2C.WriteByte(dev_,0x57, 0x30);
  I2C.WriteByte(dev_,0x61, 0x00);
  I2C.WriteByte(dev_,0x62, 0x00);
  I2C.WriteByte(dev_,0x64, 0x00);
  I2C.WriteByte(dev_,0x65, 0x00);
  I2C.WriteByte(dev_,0x66, 0xA0);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x22, 0x32);
  I2C.WriteByte(dev_,0x47, 0x14);
  I2C.WriteByte(dev_,0x49, 0xFF);
  I2C.WriteByte(dev_,0x4A, 0x00);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x7A, 0x0A);
  I2C.WriteByte(dev_,0x7B, 0x00);
  I2C.WriteByte(dev_,0x78, 0x21);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x23, 0x34);
  I2C.WriteByte(dev_,0x42, 0x00);
  I2C.WriteByte(dev_,0x44, 0xFF);
  I2C.WriteByte(dev_,0x45, 0x26);
  I2C.WriteByte(dev_,0x46, 0x05);
  I2C.WriteByte(dev_,0x40, 0x40);
  I2C.WriteByte(dev_,0x0E, 0x06);
  I2C.WriteByte(dev_,0x20, 0x1A);
  I2C.WriteByte(dev_,0x43, 0x40);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x34, 0x03);
  I2C.WriteByte(dev_,0x35, 0x44);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x31, 0x04);
  I2C.WriteByte(dev_,0x4B, 0x09);
  I2C.WriteByte(dev_,0x4C, 0x05);
  I2C.WriteByte(dev_,0x4D, 0x04);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x44, 0x00);
  I2C.WriteByte(dev_,0x45, 0x20);
  I2C.WriteByte(dev_,0x47, 0x08);
  I2C.WriteByte(dev_,0x48, 0x28);
  I2C.WriteByte(dev_,0x67, 0x00);
  I2C.WriteByte(dev_,0x70, 0x04);
  I2C.WriteByte(dev_,0x71, 0x01);
  I2C.WriteByte(dev_,0x72, 0xFE);
  I2C.WriteByte(dev_,0x76, 0x00);
  I2C.WriteByte(dev_,0x77, 0x00);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x0D, 0x01);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x80, 0x01);
  I2C.WriteByte(dev_,0x01, 0xF8);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x8E, 0x01);
  I2C.WriteByte(dev_,0x00, 0x01);
  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x80, 0x00);
}

void Laser::SetGpioConfig()
{
    // "Set interrupt config to new sample ready"
    I2C.WriteByte(dev_,SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
    uint8_t tmpdata;
    I2C.ReadByte(dev_,GPIO_HV_MUX_ACTIVE_HIGH,&tmpdata);
    I2C.WriteByte(dev_,GPIO_HV_MUX_ACTIVE_HIGH, tmpdata & ~0x10); // active low
    I2C.WriteByte(dev_,SYSTEM_INTERRUPT_CLEAR, 0x01);
}

void Laser::DataInit(bool io_2v8)
{
    // sensor uses 1V8 mode for I/O by default; switch to 2V8 mode if necessary
    if (io_2v8)
    {
        uint8_t tmp;
        I2C.ReadByte(dev_,VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV,&tmp);
        I2C.WriteByte(dev_,VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV,
        tmp | 0x01); // set bit 0
    }
    
    /*Initiate I2C-Communication*/
    I2CInit();
    
    // disable SIGNAL_RATE_MSRC (bit 1) and SIGNAL_RATE_PRE_RANGE (bit 4) limit checks
    uint8_t data;
    I2C.ReadByte(dev_,MSRC_CONFIG_CONTROL,&data);
    I2C.WriteByte(dev_,MSRC_CONFIG_CONTROL, data | 0x12);

    // set final range signal rate limit to 0.25 MCPS (million counts per second)
    setSignalRateLimit(0.25);
    I2C.WriteByte(dev_,SYSTEM_SEQUENCE_CONFIG, 0xFF);
}

void Laser::I2CInit()
{
    // "Set I2C standard mode"
    I2C.WriteByte(dev_,0x88, 0x00);
    I2C.WriteByte(dev_,0x80, 0x01);
    I2C.WriteByte(dev_,0xFF, 0x01);
    I2C.WriteByte(dev_,0x00, 0x00);
    I2C.ReadByte(dev_,0x91,&stop_variable);
    I2C.WriteByte(dev_,0x00, 0x01);
    I2C.WriteByte(dev_,0xFF, 0x00);
    I2C.WriteByte(dev_,0x80, 0x00);
}
/************************************************
// Set the return signal rate limit check value in units of MCPS (mega counts
// per second). "This represents the amplitude of the signal reflected from the
// target and detected by the device"; setting this limit presumably determines
// the minimum measurement necessary for the sensor to report a valid reading.
// Setting a lower limit increases the potential range of the sensor but also
// seems to increase the likelihood of getting an inaccurate reading because of
// unwanted reflections from objects other than the intended target.
// Defaults to 0.25 MCPS as initialized by the ST API and this library.
*************************************************/
bool Laser::setSignalRateLimit(float limit_Mcps)
{
    if (limit_Mcps < 0 || limit_Mcps > 511.99) { return false; }

    // Q9.7 fixed point format (9 integer bits, 7 fractional bits)
    uint8_t tmparray[2]={0,0};
    uint16_t tmp = limit_Mcps * (1 << 7);
    tmparray[0] = tmp & 0xff;   // Low
    tmparray[1] = (tmp >> 8);   // High
    I2C.WriteBytes(dev_,68,2,tmparray);
    
    return true;
}

// Get reference SPAD (single photon avalanche diode) count and type
// based on VL53L0X_get_info_from_device(),
// but only gets reference SPAD count and type
bool Laser::getSpadInfo(uint8_t * count, bool * type_is_aperture)
{
  uint8_t tmp;

  I2C.WriteByte(dev_,0x80, 0x01);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x00, 0x00);

  I2C.WriteByte(dev_,0xFF, 0x06);
  I2C.ReadByte(dev_,0x83,&tmp);
  I2C.WriteByte(dev_,0x83, tmp | 0x04);
  I2C.WriteByte(dev_,0xFF, 0x07);
  I2C.WriteByte(dev_,0x81, 0x01);

  I2C.WriteByte(dev_,0x80, 0x01);

  I2C.WriteByte(dev_,0x94, 0x6b);
  I2C.WriteByte(dev_,0x83, 0x00);
  //startTimeout(); Most likely a failswitch for deadlock
  tmp = 0x00;
  while (tmp == 0x00)
  {
    I2C.ReadByte(dev_,0x83,&tmp);
    //if (checkTimeoutExpired()) { return false; }
  }
  I2C.WriteByte(dev_,0x83, 0x01);
  I2C.ReadByte(dev_,0x92,&tmp);
  //tmp = readReg(0x92); ^

  *count = tmp & 0x7f;
  *type_is_aperture = (tmp >> 7) & 0x01;

  I2C.WriteByte(dev_,0x81, 0x00);
  I2C.WriteByte(dev_,0xFF, 0x06);
  I2C.ReadByte(dev_,0x83,&tmp);
  I2C.WriteByte(dev_,0x83, tmp  & ~0x04);
  I2C.WriteByte(dev_,0xFF, 0x01);
  I2C.WriteByte(dev_,0x00, 0x01);

  I2C.WriteByte(dev_,0xFF, 0x00);
  I2C.WriteByte(dev_,0x80, 0x00);

  return true;
}

// Convert sequence step timeout from MCLKs to microseconds with given VCSEL period in PCLKs
// based on VL53L0X_calc_timeout_us()
uint32_t Laser::timeoutMclksToMicroseconds(uint16_t timeout_period_mclks, uint8_t vcsel_period_pclks)
{
  uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);
  return ((timeout_period_mclks * macro_period_ns) + (macro_period_ns / 2)) / 1000;
}

// Convert sequence step timeout from microseconds to MCLKs with given VCSEL period in PCLKs
// based on VL53L0X_calc_timeout_mclks()
uint32_t Laser::timeoutMicrosecondsToMclks(uint32_t timeout_period_us, uint8_t vcsel_period_pclks)
{
  uint32_t macro_period_ns = calcMacroPeriod(vcsel_period_pclks);

  return (((timeout_period_us * 1000) + (macro_period_ns / 2)) / macro_period_ns);
}

// based on VL53L0X_perform_single_ref_calibration()
bool Laser::performSingleRefCalibration(uint8_t vhv_init_byte)
{
  I2C.WriteByte(dev_,SYSRANGE_START, 0x01 | vhv_init_byte); // VL53L0X_REG_SYSRANGE_MODE_START_STOP

  //startTimeout();
  uint8_t tmp = 0;
  while ((tmp & 0x07) == 0)
  {
    I2C.ReadByte(dev_,RESULT_INTERRUPT_STATUS,&tmp);
    //if (checkTimeoutExpired()) { return false; }
  }

  I2C.WriteByte(dev_,SYSTEM_INTERRUPT_CLEAR, 0x01);

  I2C.WriteByte(dev_,SYSRANGE_START, 0x00);

  return true;
}

// Encode sequence step timeout register value from timeout in MCLKs
// based on VL53L0X_encode_timeout()
// Note: the original function took a uint16_t, but the argument passed to it
// is always a uint16_t.
uint16_t Laser::encodeTimeout(uint16_t timeout_mclks)
{
  // format: "(LSByte * 2^MSByte) + 1"

  uint32_t ls_byte = 0;
  uint16_t ms_byte = 0;

  if (timeout_mclks > 0)
  {
    ls_byte = timeout_mclks - 1;

    while ((ls_byte & 0xFFFFFF00) > 0)
    {
      ls_byte >>= 1;
      ms_byte++;
    }

    return (ms_byte << 8) | (ls_byte & 0xFF);
  }
  else { return 0; }
}

/* [] END OF FILE */