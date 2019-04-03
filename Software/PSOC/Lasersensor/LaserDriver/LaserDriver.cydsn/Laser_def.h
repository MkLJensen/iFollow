/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef LASERDEF_H
#define LASERDEF_H

#ifdef __cplusplus
extern "C" {
#endif
    // PSoC include, this has to be wrapped
    #include "project.h"
#ifdef __cplusplus
}
#endif

/*Structures*/
struct SequenceStepEnables
{
    bool tcc, msrc, dss, pre_range, final_range;
};

struct SequenceStepTimeouts
{
    uint16_t pre_range_vcsel_period_pclks, final_range_vcsel_period_pclks;
    uint16_t msrc_dss_tcc_mclks, pre_range_mclks, final_range_mclks;
    uint32_t msrc_dss_tcc_us,    pre_range_us,    final_range_us;
};

/*Enums*/
enum vcselPeriodType { VcselPeriodPreRange, VcselPeriodFinalRange };

/*Defines*/
#define MSRC_CONFIG_CONTROL 96
#define SYSTEM_SEQUENCE_CONFIG 1
#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV 137
#define GLOBAL_CONFIG_SPAD_ENABLES_REF_0 176
#define DYNAMIC_SPAD_REF_EN_START_OFFSET 79
#define DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD 78
#define GLOBAL_CONFIG_REF_EN_START_SELECT 182
#define SYSTEM_INTERRUPT_CONFIG_GPIO 10
#define GPIO_HV_MUX_ACTIVE_HIGH 132
#define SYSTEM_INTERRUPT_CLEAR 11
#define MSRC_CONFIG_TIMEOUT_MACROP 70
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI 81
#define VcselPeriodFinalRange 1
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI 113
#define SYSTEM_SEQUENCE_CONFIG 1
#define PRE_RANGE_CONFIG_VCSEL_PERIOD 80
#define FINAL_RANGE_CONFIG_VCSEL_PERIOD 112
#define SYSRANGE_START 0
#define RESULT_INTERRUPT_STATUS 19
#define SYSTEM_INTERMEASUREMENT_PERIOD 4
#define OSC_CALIBRATE_VAL 248
#define RESULT_RANGE_STATUS 20



/*Macros*/
// Decode VCSEL (vertical cavity surface emitting laser) pulse period in PCLKs
// from register value
// based on VL53L0X_decode_vcsel_period()
#define decodeVcselPeriod(reg_val)      (((reg_val) + 1) << 1)
// Encode VCSEL pulse period register value from period in PCLKs
// based on VL53L0X_encode_vcsel_period()
#define encodeVcselPeriod(period_pclks) (((period_pclks) >> 1) - 1)
// Calculate macro period in *nanoseconds* from VCSEL period in PCLKs
// based on VL53L0X_calc_macro_period_ps()
// PLL_period_ps = 1655; macro_period_vclks = 2304
#define calcMacroPeriod(vcsel_period_pclks) ((((uint32_t)2304 * (vcsel_period_pclks) * 1655) + 500) / 1000)




#endif
/* [] END OF FILE */
