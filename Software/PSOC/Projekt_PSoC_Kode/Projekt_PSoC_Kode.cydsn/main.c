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
#include "RpiUart.h"
#include "PIDcontroller.h"
#include "LED.h"
#include "Switches.h"

CY_ISR_PROTO(ISR_UART_rx_handler);
CY_ISR_PROTO(PowerSwitch_Handler);
CY_ISR_PROTO(FollowSwitch_Handler);

RpiUart UART;
MotorController Motor;
Switches Switchcontroller;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    Power_isr_StartEx(PowerSwitch_Handler);
    Follow_isr_StartEx(FollowSwitch_Handler);
    //isr_SPI_rx_StartEx(ISR_SPI_rx_handler);
    
    PIDcontroller PIDcontrol(0.5, 0.01, 0.01, 50);
    LED Ledcontrol;
   
    for(;;)
    {

    }
}

CY_ISR(ISR_UART_rx_handler)
{
    UART.ReadData(&Motor);
}

CY_ISR(PowerSwitch_Handler)
{
    Switchcontroller.setSwitchStatus('P');
}

CY_ISR(FollowSwitch_Handler)
{
    Switchcontroller.setSwitchStatus('F');
}

/* [] END OF FILE */
