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
    void handleByte(uint16_t byte);
    uint16_t getRightSensor(void) const;
    uint16_t getMidSensor(void) const;
    uint16_t getLeftSensor(void) const;
    
    void setRightSensor(uint16_t value);
    void setMidSensor(uint16_t value);
    void setLeftSensor(uint16_t value);
    
    uint8_t getCounter(void) const;
    void setCounter(uint8_t value);
    
private:
    uint16_t sensorLeft;
    uint16_t sensorRight;
    uint16_t sensorMid;
      
    char string[50];
    uint8_t counter_ = 0;
};

#endif
/* [] END OF FILE */
