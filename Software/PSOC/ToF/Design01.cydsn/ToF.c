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

ToF::ToF(){
    sensorLeft = 1;
    sensorRight = 1;
    sensorMid = 1;
}
void ToF::start(){
    CyGlobalIntEnable; /* Enable global interrupts. */
     
    // Init
    SPIS_Start();
    isr_1_StartEx(&ToF.isr_handler);
    UART_1_Start();
    UART_1_PutString("Terminal vindue er connected\n\r");
}

void ToF::stop(){
    CyGlobalIntDisable; /* Enable global interrupts. */
     
    // Init
    SPIS_Stop();
    isr_1_StopEx(&ToF.isr_handler);
    UART_1_PutString("Terminal vindue er disconnected\n\r");
    UART_1_Stop();

}

CY_ISR(ToF::isr_handler){
   byteR = SPIS_ReadRxData();                                          // Gemmer aflæsning af RX-buffer
    
    if (byteR == 0)
        i = 0;
    
    switch (i)
    {
        case 0:
        UART_1_PutString("Start modtaget \n\r");
        i++;
        break;
        
        case 1:
        byteR --;
        s1 = byteR<<8;
        i++;
        break;
        
        case 2:
        byteR --;
        s1 = s1|byteR;
        sprintf(string, "Sensor 1: %d \n\r", s1);
        UART_1_PutString(string);
        i++;
        break;
        
        case 3:
        byteR --;
        s2 = byteR<<8;
        i++;
        break;
        
        case 4:
        byteR --;
        s2 = s2|byteR;
        sprintf(string, "Sensor 2: %d \n\r", s2);
        UART_1_PutString(string);
        i++;
        break;
        
        case 5:
        byteR --;
        s3 = byteR<<8;
        i++;
        break;
        
        case 6:
        byteR --;
        s3 = s3|byteR;
        sprintf(string, "Sensor 3: %d \n\r", s3);
        UART_1_PutString(string);
        i++;
        break;
        
        default:
            UART_1_PutString("Error! Ukendt Index");
    } 
}
/* [] END OF FILE */
