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

class ToF { 
    public:
    ToF();
    void start();
    void stop();
    static CY_ISR_PROTO(isr_handler);
    private:
    uint16_t sensorLeft;
    uint16_t sensorRight;
    uint16_t sensorMid;
    uint8_t i;
    uint8_t byteR;  
    char string[50];
};

#endif
/* [] END OF FILE */
