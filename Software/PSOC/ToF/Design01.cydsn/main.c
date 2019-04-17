#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"


#ifdef __cplusplus
}
#endif

#include "ToF.h"


uint8_t byteR = 0;
ToF obj;
/*
uint8_t i = 0;
uint16_t s1, s2, s3;
char string[50];
*/
CY_ISR_PROTO(isr_handler)
{
    byteR = SPIS_ReadRxData();                                          // Gemmer aflæsning af RX-buffer
    obj.handleByte(byteR);
}


int main(void)
{
    
    CyGlobalIntEnable; //Enable global interrupts.
    /*
    // Init
    SPIS_Start();
    isr_1_StartEx(isr_handler);
    UART_1_Start();
    UART_1_PutString("Terminal vindue er connected\n\r");
    */
    SPIS_Start();
    isr_1_StartEx(isr_handler);
    CyDelay(10000);
    UART_1_PutString("-----------Nu er der gaaet 10 sekunder-----------\n\r");
    SPIS_Stop();
    
    for(;;)
    {
        /* Place your application code here. */
        
    }

}

/* [] END OF FILE */
