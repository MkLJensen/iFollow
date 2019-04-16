#include "project.h"
#include "stdio.h"
uint8_t byteR = 0;
uint8_t i = 0;
uint16_t s1, s2, s3;
char string[50];

CY_ISR_PROTO(isr_handler)
{
    byteR = SPIS_ReadRxData();                                          // Gemmer aflæsning ad RX-buffer
    //sprintf(string, "Modtaget: %d \n\r",byteR);
    //UART_1_PutString(string);
    
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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
     
    // Init
    SPIS_Start();
    isr_1_StartEx(isr_handler);
    UART_1_Start();
    UART_1_PutString("Terminal vindue er connected\n\r");
    
    
    
    for(;;)
    {
        /* Place your application code here. */
        
    }
}

/* [] END OF FILE */
