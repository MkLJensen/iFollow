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
#include "GyroDefs.h"

sensor_data::sensor_data(gyro_data *gyro,acc_data *acc,float *temperature)
{
	gyro_=gyro;
	acc_=acc;
	temperature_=temperature;
}

/* [] END OF FILE */
