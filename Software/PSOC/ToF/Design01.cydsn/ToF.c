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

void ToF::handleByte(uint8_t byte){
   byteR = byte;                                          
    
    if (byteR == 0)
        i = 0;
    
    switch (i)
    {
        case 0:
        //UART_1_PutString("Start modtaget \n\r");
        i++;
        break;
        
        case 1:
        byteR --;
        sensorRight = byteR<<8;
        i++;
        break;
        
        case 2:
        byteR --;
        sensorRight = sensorRight|byteR;
        //sprintf(string, "Sensor right: %d \n\r", sensorRight);
        //UART_1_PutString(string);
        i++;
        break;
        
        case 3:
        byteR --;
        sensorMid = byteR<<8;
        i++;
        break;
        
        case 4:
        byteR --;
        sensorMid = sensorMid|byteR;
        //sprintf(string, "Sensor middle: %d \n\r", sensorMid);
        //UART_1_PutString(string);
        i++;
        break;
        
        case 5:
        byteR --;
        sensorLeft = byteR<<8;
        i++;
        break;
        
        case 6:
        byteR --;
        sensorLeft = sensorLeft|byteR;
        //sprintf(string, "Sensor left: %d \n\r", sensorLeft);
        //UART_1_PutString(string);
        i++;
        break;
    } 
}
/* [] END OF FILE */
