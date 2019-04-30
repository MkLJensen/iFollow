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
#ifndef GYRO_H
#define GYRO_H
    
#ifdef __cplusplus
extern "C" {
#endif
    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

#include "i2c.h"
#include "GyroDefs.h"

class Gyro 
{ 
public:
	/*Constructor and destructor*/
	Gyro();
	~Gyro();
    
	/*Methods*/
	sensor_data* getSensorData();
    
private:
	/*PRIVATE ATTRIBUTES*/
	i2c* I2C;
	float temperature_ = 0.0f;
	acc_data* acceldata_ = NULL;
	gyro_data* gyrodata_ = NULL;
	sensor_data* sensordata_ = NULL;
    
	/*PRIVATE METHODS*/
	acc_data* getAccData();
	float getTemp();
	gyro_data* getGyroData();
	void initGyro();
};
    
#endif
/* [] END OF FILE */
