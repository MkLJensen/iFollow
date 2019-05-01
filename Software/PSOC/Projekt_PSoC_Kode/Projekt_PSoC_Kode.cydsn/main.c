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
#include "RpiSPI.h"
#include "PIDcontroller.h"
#include "LED.h"
#include "Switches.h"
#include "ToF.h"

CY_ISR_PROTO(isr_spi_handler);
CY_ISR_PROTO(PowerSwitch_Handler);
CY_ISR_PROTO(FollowSwitch_Handler);
CY_ISR_PROTO(Control_timer_isr);

uint8_t byteR = 0;

RpiSPI SPIcontroller;
MotorController Motor;
Switches Switchcontroller;

enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
       
    SPIS_Start();
    isr_spi_StartEx(isr_spi_handler); 
    
    /*Stop kom med ToF
    
    SPIS_Stop();
    isr_1_StopEx(isr_handler); */
    
    Power_isr_StartEx(PowerSwitch_Handler);
    Follow_isr_StartEx(FollowSwitch_Handler);
    Motor_timer_isr_StartEx(Control_timer_isr);
    
    LED Ledcontrol;
    PIDcontroller PIDcontrol(0.5, 0.01, 0.01, 50);
    
    UART_1_Start();
    
    UART_1_PutString("LulUmomGay    ");
    
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
        if (Mode == Sleep && SPIcontroller.ReadData(&Motor) == 'o')
        {
            Mode = Control;
            Timer_1_Start();
        }
        else if (Mode == Control && SPIcontroller.ReadData(&Motor) == 'c')
        {
            Mode = Sleep;
            Timer_1_Stop();
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
                //uint8_t Data[7] = {"Wallah"};
                //SPIcontroller.TransmitData(Data, sizeof(Data)/sizeof(uint8_t));
            }
            break;
            default :
            {
                
            }
            break;
        }
    }
}
CY_ISR(isr_spi_handler)
{
    //byteR = SPIS_ReadRxData();                                          // Gemmer aflæsning af RX-buffer
    //Sensor.handleByte(byteR);
}

CY_ISR(PowerSwitch_Handler)
{
    Switchcontroller.setSwitchStatus('P');
}

CY_ISR(FollowSwitch_Handler)
{
    Switchcontroller.setSwitchStatus('F');
}

CY_ISR(Control_timer_isr)
{
    if (Motor.getOldPower() == Motor.getPower())
    {
        
        //if (MotorPwr >= 10)
        {
            Motor.setPower(Motor.getPower()-10); 
        }
        /*else if(MotorPwr < 10 && MotorPwr > 0)
        {
            Motor.setPower(Motor.getPower()-1);
        }*/
        Motor.setOldPower();
        if (Motor.getPower() > 0)
        {
            PWM_1_WriteCompare1(500+4*Motor.getPower());
            PWM_1_WriteCompare2(500+4*Motor.getPower());
        }
        else  
        {
            PWM_1_WriteCompare1(0);
            PWM_1_WriteCompare2(0);
        }
    }
}

/* [] END OF FILE */
