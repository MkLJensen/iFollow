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

#ifndef ToF_H
#define ToF_H

#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif
#include "time.h"
#include "stdio.h"

class ToF { 
public:
    ToF();
    //void start();
    //void stop();
    void handleByte(uint8_t byte);
    uint16_t getRightSensor(void) const;
    uint16_t getMidSensor(void) const;
    uint16_t getLeftSensor(void) const;
    
    uint16_t sensorLeft;
    uint16_t sensorRight;
    uint16_t sensorMid;
    uint8_t i;
    uint8_t byteR_; 
    uint8_t sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;
    char string[50];
};

#endif
/* [] END OF FILE */
