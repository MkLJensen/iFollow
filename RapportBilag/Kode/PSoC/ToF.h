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
    void handleByte(uint8_t byte);
    uint16_t getSensorLeft(void) const;
    uint16_t getSensorMid(void) const;
    uint16_t getSensorRight(void) const;
    uint8_t byteR_; 
    char string[50];
private:
    uint16_t sensorLeft;
    uint16_t sensorRight;
    uint16_t sensorMid;
    uint8_t index;
};

#endif
/* [] END OF FILE */
