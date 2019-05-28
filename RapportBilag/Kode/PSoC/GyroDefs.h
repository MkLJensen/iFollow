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

#ifndef GYRODEFS_H
#define GYRODEFS_H

#ifdef __cplusplus
extern "C" {
#endif
    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

#include <stdlib.h>

/*ADDRESSES FOR I2C-COMMUNICATION WITH MPU6050*/
#define MPU6050_ADD     (0x68)      // Device / Slave Address
#define PWR_MGMT_1      (0x6B)      // Reset with 0x00 to wakeup
#define SMPRT_DIV       (0x19)      // Register for holding sample rate 109
#define GYRO_CONFIG     (0x1b)      // Register for self-test and scale 0x18 for fullscale
#define ACCEL_CONFIG    (0x1c)      // --||-- 0x08 fullscale +- 4g
#define USER_CTRL       (0x6a)      // 0x00 to disable master mode | 0x20 to enable
#define INT_PIN_CFG     (0x37)      // 0x02 I2C bypass enable
#define CONFIG          (0x1A)      // For setting DLPF - fast or slow
#define START_GYRO_DATA (0x43)      // First address in gyro registers      | 6bytes long
#define START_ACC_DATA  (0x3b)      // First address in accelerometer       | 6bytes long
#define START_TEMP_DATA (0x41)      // First address in temperature sensor  | 2bytes long

/***********Typedefs************/
/*Structure for gyrosensor data*/
typedef struct gyro_data {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
    float x_rad = 0.0f;
    float y_rad = 0.0f;
    float z_rad = 0.0f;
} gyro_data;

/*Structure for accelerometer data*/
typedef struct acc_data {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
    float x_G = 0.0f;
    float y_G = 0.0f;
    float z_G = 0.0f;
} acc_data;

/*Structure for all sensor data*/
typedef struct sensor_data {
    gyro_data *gyro_ = NULL;
    acc_data *acc_ = NULL;
    float *temperature_ = NULL;
	sensor_data(gyro_data *gyro,acc_data *acc,float *temperature);
	sensor_data(){}
} sensor_data;
    
#endif
/* [] END OF FILE */
