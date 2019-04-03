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
#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

class i2c { 
    public:
    i2c(){};  // Maybe delete no need for constructor
    void ReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
    void ReadByte(uint8_t devAddr, uint8_t regAddr, uint8_t *value);
    void WriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
    void WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value);
    void WriteBytes16bit(uint8_t device_add, uint16_t reg_add, uint8_t nobytes, uint8_t *data);
    void WriteByte16bit(uint8_t device_add, uint16_t reg_add, uint8_t data);
    void ReadBytes16bits(uint8_t device_add, uint16_t reg_add, uint8_t nobytes, uint8_t *data);
    void ReadByte16bits(uint8_t device_add, uint16_t reg_add, uint8_t *data);
    
};

#endif
/* [] END OF FILE */
