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
#include "ToF.h"

CY_ISR_PROTO(isr_handler);
CY_ISR_PROTO(PowerSwitch_Handler);
CY_ISR_PROTO(FollowSwitch_Handler);

uint8_t byteR = 0;
ToF Sensor;
RpiUart UARTcontroller;
MotorController Motor;
Switches Switchcontroller;

enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    
    /*Start kom med ToF
    
    SPIS_Start();
    isr_1_StartEx(isr_handler); */
    
    /*Stop kom med ToF
    
    SPIS_Stop();
    isr_1_StopEx(isr_handler); */
    
    Power_isr_StartEx(PowerSwitch_Handler);
    Follow_isr_StartEx(FollowSwitch_Handler);
    
    LED Ledcontrol;
    PIDcontroller PIDcontrol(0.5, 0.01, 0.01, 50);
    
    UART_1_Start();
    
    uint8_t Mode = Off; 
   
    for(;;)
    {
        if(Mode == Off && Switchcontroller.getSwitchStatus('p') == true)
        {
            Mode = Init;
        }
        else if (Mode == Sleep && Switchcontroller.getSwitchStatus('p') == false)
        {
            Mode = Off;
        }
        if (Mode == Sleep && UARTcontroller.ReadData(&Motor) == 'o')
        {
            Mode = Control;
        }
        else if (Mode == Control && UARTcontroller.ReadData(&Motor) == 'c')
        {
            Mode = Sleep;
        }
        if (Mode == Sleep && Switchcontroller.getSwitchStatus('f') == true)
        {
            Mode = Follow;
        }
        else if (Mode == Follow && Switchcontroller.getSwitchStatus('f') == false)
        {
            Mode = Sleep;
        }
        
        switch(Mode)
        {
            case Off :
            {
                Ledcontrol.turnOffLed('g');
                Ledcontrol.turnOffLed('r');
            }
            break;
            case Init :
            {
                Ledcontrol.blinkLed('r');
                CyDelay(1000);
                Mode = Sleep;
            }
            break;
            case Sleep :
            {
                Ledcontrol.turnOffLed('r');
                Ledcontrol.turnOnLed('g');
            }
            break;
            case Control :
            {
                Ledcontrol.turnOffLed('r');
                Ledcontrol.blinkLed('g');
            }
            break;
            case Follow :
            {
                Ledcontrol.turnOffLed('r');
                Ledcontrol.blinkLed('g');
                uint8_t Data[7] = {"Wallah"};
                UARTcontroller.TransmitData(Data, sizeof(Data)/sizeof(uint8_t));
            }
            break;
            default :
            {
                
            }
            break;
        }
    }
}
CY_ISR(isr_handler)
{
    byteR = SPIS_ReadRxData();                                          // Gemmer aflæsning af RX-buffer
    Sensor.handleByte(byteR);
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
