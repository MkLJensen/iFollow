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
#include "i2c.h"

/***************************************************
* For writing data to device with I2C
* @param <the device address><the wanted register address><number of bytes to read><pointer to data>
* @return void
****************************************************/
void i2c::WriteBytes(uint8_t device_add, uint8_t reg_add, uint8_t nobytes, uint8_t *data) {
    
    uint8_t i=0;    //Index for loop
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Begin writing to register address*/
    I2C_1_MasterWriteByte(reg_add);
    
    while (i++ < nobytes) 
    {
        /*Keep writing bytes untill nobytes is reached*/
        I2C_1_MasterWriteByte(*data++);
    }
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();
}

/***************************************************
* For writing data to device with I2C with 16bit addressing protocol
* @param <the device address><the wanted register address><number of bytes to read><pointer to data>
* @return void
****************************************************/
void i2c::WriteBytes16bit(uint8_t device_add, uint16_t reg_add, uint8_t nobytes, uint8_t *data) 
{    
    uint8_t i=0;            // Index for loop
    uint8_t msg[2] = {0,0}; // Message array for addresses
    
    /*Make 16-bit address from 10bit*/
    msg[0] = reg_add >> 8;
    msg[1] = reg_add & 0b0000000011111111;
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Begin writing to register address*/
    for (int j = 0; j<2;j++) I2C_1_MasterWriteByte(msg[j]);
    
    while (i++ < nobytes) 
    {
        /*Keep writing bytes untill nobytes is reached*/
        I2C_1_MasterWriteByte(*data++);
    }
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();
}

/***************************************************
* For writing a single byte of data to device with I2C
* @param <the device address><the wanted register address><data>
* @return void
****************************************************/
void i2c::WriteByte(uint8_t device_add, uint8_t reg_add, uint8_t data) {
    /*Just call I2CWriteBytes function*/
	WriteBytes(device_add, reg_add, 1, &data);
}

/***************************************************
* For writing a single byte of data to device with I2C using 16bit addressing
* @param <the device address><the wanted register address><data>
* @return void
****************************************************/
void i2c::WriteByte16bit(uint8_t device_add, uint16_t reg_add, uint8_t data) {
    /*Just call I2CWriteBytes16bit function*/
	WriteBytes16bit(device_add, reg_add, 1, &data);
}

/***************************************************
* For reading bytes of data from device with I2C
* @param <the device address><the wanted register address><number of bytes to read><pointer to data storage variable>
* @return void
****************************************************/
void i2c::ReadBytes(uint8_t device_add, uint8_t reg_add, uint8_t nobytes, uint8_t *data)
{
    uint8_t i=0;    //Index for loop
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Specify register address to read from*/
    I2C_1_MasterWriteByte(reg_add);
    
    /*Go into read-mode*/
    I2C_1_MasterSendRestart(device_add, I2C_1_READ_XFER_MODE);
    
    /*Start reading nobytes bytes*/
    while (i++ < (nobytes-1)) {
        *data++ = I2C_1_MasterReadByte(I2C_1_ACK_DATA); // ACK to signal keep reading
    }
    *data = I2C_1_MasterReadByte(I2C_1_NAK_DATA); // NAK to signal stop reading
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();    
}

/***************************************************
* For reading a single byte of data from device with I2C
* @param <the device address><the wanted register address><number of bytes to read><pointer to data storage variable>
* @return void
****************************************************/
void i2c::ReadByte(uint8_t devAddr, uint8_t regAddr, uint8_t *value)
{
    ReadBytes(devAddr,regAddr,1,value);
}

/***************************************************
* For reading bytes of data from device with I2C using 16bit addressing
* @param <the device address><the wanted register address><number of bytes to read><pointer to data storage variable>
* @return void
****************************************************/
void i2c::ReadBytes16bits(uint8_t device_add, uint16_t reg_add, uint8_t nobytes, uint8_t *data)
{
    uint8_t i=0;                //Index for loop
    uint8_t msg[2] = {0,0};     // Message array for addresses
    
    /*Make 16-bit address from 10bit*/
    msg[0] = reg_add >> 8;
    msg[1] = reg_add & 0b0000000011111111;
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Specify register address to read from*/
    for (int j = 0; j<2;j++) I2C_1_MasterWriteByte(msg[j]);
    
    /*Go into read-mode*/
    I2C_1_MasterSendRestart(device_add, I2C_1_READ_XFER_MODE);
    
    /*Start reading nobytes bytes*/
    while (i++ < (nobytes-1)) {
        *data++ = I2C_1_MasterReadByte(I2C_1_ACK_DATA); // ACK to signal keep reading
    }
    *data = I2C_1_MasterReadByte(I2C_1_NAK_DATA); // NAK to signal stop reading
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();    
}
/* [] END OF FILE */
