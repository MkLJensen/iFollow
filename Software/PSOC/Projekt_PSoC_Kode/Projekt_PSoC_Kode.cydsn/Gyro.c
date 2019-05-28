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
#include "Gyro.h"

/***************************************************
* Hack for using the c++ new-operator in PSoC
* @param <size of desired allocation>
* @return byte pointer
****************************************************/
void* operator new(size_t size) { 
    return malloc(size); 
} 

/***************************************************
* Hack for using the c++ delete-operator in PSoC
* @param <desired dynamic allocated byte>
* @return void
****************************************************/
void operator delete(void* ptr) {
    free(ptr); 
}

/***************************************************
* Default constructor for object creation. Initalizes
* member-variables and sensors.
* @param  none
* @return void
****************************************************/
Gyro::Gyro(){
	/*Make I2C interface*/
	I2C = new i2c;
	
	/*Initialize pointers to structures*/
	acceldata_ = new acc_data;
	gyrodata_ = new gyro_data;
	sensordata_ = new sensor_data(gyrodata_,
		acceldata_,
		&temperature_);
	sensordata_->gyro_ = gyrodata_;
	
	initGyro();
};

/***************************************************
* Destructor for object-destruction, deletes
* dynamically allocated variables
* @param none
* @return void
****************************************************/
Gyro::~Gyro(){
	/*Free dynamically allocated memory*/
	delete I2C;
	delete acceldata_;
	delete gyrodata_;
	delete sensordata_;
};

/***************************************************
* Retrieve if gyroscope is upside down. Used to detect
* if robot has fallen.
* @param none
* @return < 1 if fallen, 0 if not fallen >
****************************************************/
int Gyro::hasFallen()
{
	getAccData();
	//return 1;
	return acceldata_->z_G < 0 ? 1 : 0;
}

/***************************************************
* Initialize sensors
* @param none
* @return void
****************************************************/
void Gyro::initGyro()
{
    //Initializing MPU6050 -- Might need some tweaking
    //UART_1_PutString("Intializing MPU6050..\r\n");
    I2C->WriteByte(MPU6050_ADD, PWR_MGMT_1, 0x00);
    I2C->WriteByte(MPU6050_ADD,SMPRT_DIV,109);
    I2C->WriteByte(MPU6050_ADD,GYRO_CONFIG,0x18); // FULLSCALE
    I2C->WriteByte(MPU6050_ADD,USER_CTRL,0x20);
    I2C->WriteByte(MPU6050_ADD,INT_PIN_CFG,0x37);
    I2C->WriteByte(MPU6050_ADD,CONFIG,6);         //6 very slow
    
}

/***************************************************
* Used to update and retrieve member accelerometer data
* @param none
* @return <pointer to member accelerometer-object (acceldata_)>
****************************************************/
acc_data* Gyro::getAccData()
{
	//Buffer for sensor data
    uint8_t rx_buffer[6];

    /*Read data into buffer*/
    I2C->ReadBytes(MPU6050_ADD,START_ACC_DATA, 6, rx_buffer);
    
    //Extract raw data
    acceldata_->x = rx_buffer[0] << 8 | rx_buffer[1];
    acceldata_->y = rx_buffer[2] << 8 | rx_buffer[3];
    acceldata_->z = rx_buffer[4] << 8 | rx_buffer[5];
    
    /*Convert into G's*/
    acceldata_->x_G = acceldata_->x / 8192.0f;
    acceldata_->y_G = acceldata_->y / 8192.0f;
    acceldata_->z_G = acceldata_->z / 8192.0f;
	
	return acceldata_;
}

/***************************************************
* Used to update and retrieve member temperature data
* @param none
* @return <current sensor temperature>
****************************************************/
float Gyro::getTemp()
{
    uint8_t rx_buffer[2];
    uint16_t temp_buffer;
    
    /*Read data into buffer*/
    I2C->ReadBytes(MPU6050_ADD,START_TEMP_DATA, 2, rx_buffer);
    
    /*Extract raw data*/
    temp_buffer = rx_buffer[0] << 8 | rx_buffer[1];
    
    /*Convert to celsius*/
    temperature_ = temp_buffer / 340.0f + 36.53f;
	return temperature_;
}

/***************************************************
* Used to update and retrieve all sensors data
* @param none
* @return <pointer to member sensor_data object>
****************************************************/
sensor_data* Gyro::getSensorData()
{
	/*Get new values from sensor!*/
	getAccData();
	getTemp();
	getGyroData();
	
	/*Return sensor struct*/
	return sensordata_;
}

/***************************************************
* Used to update and retrieve gyro data
* @param none
* @return <pointer to member gyro-data object (gyrodata_)>
****************************************************/
gyro_data* Gyro::getGyroData()
{
	//Buffer for sensor data
    uint8_t rx_buffer[6];

    /*Read data into buffer*/
    I2C->ReadBytes(MPU6050_ADD,START_GYRO_DATA, 6, rx_buffer);
    
    //Extract raw data
    gyrodata_->x = rx_buffer[0] << 8 | rx_buffer[1];
    gyrodata_->y = rx_buffer[2] << 8 | rx_buffer[3];
    gyrodata_->z = rx_buffer[4] << 8 | rx_buffer[5];
    
    /*Convert into radians per second*/
    gyrodata_->x_rad = gyrodata_->x / 939.650784f;
    gyrodata_->y_rad = gyrodata_->y / 939.650784f;
    gyrodata_->z_rad = gyrodata_->z / 939.650784f;
	
	return gyrodata_;
}



/* [] END OF FILE */
