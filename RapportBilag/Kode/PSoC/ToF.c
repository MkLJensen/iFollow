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
#include "ToF.h"

ToF::ToF(){}

void ToF::handleByte(uint8_t byte){
   byteR_ = byte;                                          
    
    if (byteR_ == 0)
        index = 0;
    
    switch (index)
    {
        case 0:
        //UART_1_PutString("Start modtaget \n\r");
        index++;
        break;
        
        case 1:
        byteR_ --;
        sensorRight = byteR_<<8;
        index++;
        break;
        
        case 2:
        sensorRight = sensorRight|byteR_;
        //sprintf(string, "Sensor Right: %d \n\r", sensorRight);
        //UART_1_PutString(string);
        index++;
        break;
        
        case 3:
        byteR_ --;
        sensorMid = byteR_<<8;
        index++;
        break;
        
        case 4:
        sensorMid = sensorMid|byteR_;
        //sprintf(string, "Sensor Middle: %d \n\r", sensorMid);
        //UART_1_PutString(string);
        index++;
        break;
        
        case 5:
        byteR_ --;
        sensorLeft = byteR_<<8;
        index++;
        break;
        
        case 6:
        sensorLeft = sensorLeft|byteR_;
        //sprintf(string, "Sensor Left: %d \n\r", sensorLeft);
        //UART_1_PutString(string);
        index++;
        break;
        
        default: 
        //UART_1_PutString("Unknown index!\n\r");
        break;
    }
}
uint16_t ToF::getSensorLeft(void) const
{
    return sensorLeft;
}

uint16_t ToF::getSensorMid(void) const
{
    return sensorMid;
}

uint16_t ToF::getSensorRight(void) const
{
    return sensorRight;
}

/* [] END OF FILE */
