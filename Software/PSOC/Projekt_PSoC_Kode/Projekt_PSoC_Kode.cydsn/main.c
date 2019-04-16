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
#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif
#include "MotorController.h"
#include "RpiUartHandler.h"
#include "PIDcontroller.h"

CY_ISR_PROTO(ISR_UART_rx_handler);
//void handleByteReceived(uint8_t byteReceived[]);

RpiUartHandler Handler;
MotorController Motor;

int i = 50;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    PWM_1_Start();
    I2C_1_Start();
    UART_1_Start();   
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    //isr_SPI_rx_StartEx(ISR_SPI_rx_handler);
    
    SPIS_1_Start();
    
    PIDcontroller PIDcontrol(0.5, 0.01, 0.01, 50);
   
    for(;;)
    {
        
    }
}


CY_ISR(ISR_UART_rx_handler)
{
    Handler.UARTreaddata(&Motor);
}

CY_ISR(ISR_SPI_rx_handler)
{
    UART_1_PutString("Data");
}



/* [] END OF FILE */
