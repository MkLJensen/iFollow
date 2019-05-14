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
uint16_t ToF::getLeftSensor(void) const
{
    return sensorLeft;
}

uint16_t ToF::getMidSensor(void) const
{
    return sensorMid;
}

uint16_t ToF::getRightSensor(void) const
{
    return sensorRight;
}

void ToF::handleByte(uint8_t byte){
   byteR_ = byte;                                          
    
    if (byteR_ == 0)
        i = 0;
    
    switch (i)
    {
        case 0:
        //UART_1_PutString("Start modtaget \n\r");
        i++;
        break;
        
        case 1:
        byteR_ --;
        sensorRight = byteR_<<8;
        i++;
        break;
        
        case 2:
        //byteR --;
        sensorRight = sensorRight|byteR_;
        //sprintf(string, "Sensor Right: %d \n\r", sensorRight);
        //UART_1_PutString(string);
        i++;
        break;
        
        case 3:
        byteR_ --;
        sensorMid = byteR_<<8;
        i++;
        break;
        
        case 4:
        //byteR --;
        sensorMid = sensorMid|byteR_;
        //sprintf(string, "Sensor Middle: %d \n\r", sensorMid);
        //UART_1_PutString(string);
        i++;
        break;
        
        case 5:
        byteR_ --;
        sensorLeft = byteR_<<8;
        i++;
        break;
        
        case 6:
        //byteR --;
        sensorLeft = sensorLeft|byteR_;
        //sprintf(string, "Sensor Left: %d \n\r", sensorLeft);
        //UART_1_PutString(string);
        i++;
        break;
        
        default: 
        //UART_1_PutString("Unknown index!\n\r");
        break;
    }
}
    /*
    //TEST!!
    switch (i)
    {
        case 0:
        UART_1_PutString("Start modtaget \n\r");
        i++;
        break;
        
        case 1:
        sensor1 = byteR_;
        sprintf(string, "Sensor Nr. 1: %d \n\r", sensor1);
        UART_1_PutString(string);
        i++;
        break;
        
        case 2:
        sensor2 = byteR_;
        sprintf(string, "Sensor Nr. 2: %d \n\r", sensor2);
        UART_1_PutString(string);
        i++;
        break;
        
        case 3:
        sensor3 = byteR_;
        sprintf(string, "Sensor Nr. 3: %d \n\r", sensor3);
        UART_1_PutString(string);
        i++;
        break;
        
        case 4:
        sensor4 = byteR_;
        sprintf(string, "Sensor Nr. 4: %d \n\r", sensor4);
        UART_1_PutString(string);
        i++;
        break;
        
        case 5:
        sensor5 = byteR_;
        sprintf(string, "Sensor Nr. 5: %d \n\r", sensor5);
        UART_1_PutString(string);
        i++;
        break;
        
        case 6:
        sensor6 = byteR_;
        sprintf(string, "Sensor Nr. 6: %d \n\r", sensor6);
        UART_1_PutString(string);
        i++;
        break;
        
        default: 
        UART_1_PutString("Unknown index!\n\r");
        break;
    } */
/* [] END OF FILE */
