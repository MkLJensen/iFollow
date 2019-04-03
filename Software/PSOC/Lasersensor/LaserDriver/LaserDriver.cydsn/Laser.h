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
/*Credits to:*/
/*https://github.com/pololu/vl53l0x-arduino*/
#ifndef LASER_H
#define LASER_H

#ifdef __cplusplus
extern "C" {
#endif
    // PSoC include, this has to be wrapped
    #include "project.h"
#ifdef __cplusplus
}
#endif
#include "i2c.h"
#include "Laser_def.h"


class Laser{
  public:
    /*Constructor*/
    Laser(uint8_t address){dev_ = address;};
    Laser(){dev_ = 0x29;};
    
    /*IO Functions*/
    inline void SetTimeout(uint16_t timeout) { io_timeout = timeout; };
    inline uint16_t GetTimeout(void) { return io_timeout; }
    void StartContinuous(uint32_t period_ms=0);
    void StopContinuous(void);
    uint16_t ReadRangeContinuousMillimeters(void);  // Read in mm
    
    /*Init functions*/
    bool Init(bool);
    void StaticInit();
    void I2CInit();
    void DataInit(bool);
    void LoadTuningSettings();
    void SetGpioConfig();
    void getSequenceStepEnables(SequenceStepEnables * enables);
    void getSequenceStepTimeouts(SequenceStepEnables const * enables, SequenceStepTimeouts * timeouts);
    uint8_t getVcselPulsePeriod(vcselPeriodType type);
    uint32_t getMeasurementTimingBudget(void);
    uint32_t timeoutMclksToMicroseconds(uint16_t timeout_period_mclks, uint8_t vcsel_period_pclks);
    uint32_t timeoutMicrosecondsToMclks(uint32_t timeout_period_us, uint8_t vcsel_period_pclks);
    bool setSignalRateLimit(float limit_Mcps);
    bool getSpadInfo(uint8_t * count, bool * type_is_aperture);
    uint16_t decodeTimeout(uint16_t reg_val);
    bool setMeasurementTimingBudget(uint32_t budget_us);
    bool PerformRefCalibration();
    uint16_t encodeTimeout(uint16_t timeout_mclks);

  private:
    i2c I2C;
    void ReadRange();
    uint16_t range_;
    uint8_t dev_ = 0x29;    // Default device address
    bool performSingleRefCalibration(uint8_t vhv_init_byte);
    uint32_t measurement_timing_budget_us;
    uint16_t io_timeout;
    uint8_t stop_variable; // read by init and used when starting measurement; is StopVariable field of VL53L0X_DevData_t structure in API
};

#endif
/* [] END OF FILE */
