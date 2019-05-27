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
/*
void ToF::start(){  
    // Init
    SPIS_Start();
    
    UART_1_Start();
    UART_1_PutString("Terminal vindue er connected\n\r");
}

void ToF::stop(){     
    // Init
    SPIS_Stop();
    UART_1_PutString("Terminal vindue er disconnected\n\r");
    UART_1_Stop();
}
*/

void ToF::setRightSensor(uint16_t value)
{
    sensorRight = value;
}

void ToF::setMidSensor(uint16_t value)
{
    sensorMid = value;
}

void ToF::setLeftSensor(uint16_t value)
{
    sensorLeft = value;
}

uint16_t ToF::getRightSensor(void) const
{
    return sensorRight;
}

uint16_t ToF::getMidSensor(void) const
{
    return sensorMid;
}

uint16_t ToF::getLeftSensor(void) const
{
    return sensorLeft;
}

uint8_t ToF::getCounter(void) const
{
    return counter_;
}
void ToF::setCounter(uint8_t value)
{
    counter_ = value;
}

void ToF::handleByte(uint16_t byte){
  
    if (byte == 0)
    {
        setCounter(1);
        return;
    }
    char string[50];
    switch (counter_)
    {       
        case 1:
        setRightSensor(byte);
        setCounter(2);
        
        sprintf(string, "Sensor right is: %d \n\r", byte);
        UART_1_PutString(string);
        break;
        
        case 2:
        setMidSensor(byte);
        setCounter(3);
      
        sprintf(string, "Sensor middle is: %d \n\r", byte);
        UART_1_PutString(string);
        break;
        
        case 3:
        setLeftSensor(byte);
        setCounter(0);
        
        sprintf(string, "Sensor left is: %d \n\r", byte);
        UART_1_PutString(string);
        break;
                
        default: 
        //UART_1_PutString("Unknown index!\n\r");
        break;
    }
}
/* [] END OF FILE */
