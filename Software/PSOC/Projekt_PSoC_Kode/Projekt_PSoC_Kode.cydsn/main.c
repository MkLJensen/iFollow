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
#include "Gyro.h"

CY_ISR_PROTO(PowerSwitch_Handler);
CY_ISR_PROTO(FollowSwitch_Handler);
CY_ISR_PROTO(Control_timer_isr);

uint8_t byteR = 0;

enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4};

//Have to be declared here to able to use in ISR!!!
Switches Switchcontroller;
MotorController Motor;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
           
    I2C_1_Start();
    UART_1_Start();
    SPIS_Start();
    Power_isr_StartEx(PowerSwitch_Handler);
    Follow_isr_StartEx(FollowSwitch_Handler);
    Motor_timer_isr_StartEx(Control_timer_isr);
    
    
    Gyro GyroController;
    RpiSPI SPIcontroller(&GyroController, &Motor);
    LED Ledcontrol;
    PIDcontroller PIDcontrol(142.9, -136.2, -0.693, 50, &Motor );
                
    uint8_t Mode = Off; 
    
    UART_1_PutString("Say Hello To my LIttle FRIEND!");
    
    /*while(1)
    {
        for(int i = 0; i < 100; i++)
        {
            Motor.GoForward(i);
            CyDelay(200);
        }
        Motor.GoForward(0);
        for(int i = 0; i < 100; i++)
        {
            Motor.GoBackward(i);
            CyDelay(200);
        }
        Motor.GoForward(0);
        for(int i = 0; i < 100; i++)
        {
            Motor.TurnLeft(i);
            CyDelay(200);
        }
        Motor.GoForward(0);
        for(int i = 0; i < 100; i++)
        {
            Motor.TurnRight(i);
            CyDelay(200);
        }
        Motor.GoForward(0);
    }*/
    for(;;)
    {
        if(Mode == Off && Switchcontroller.getSwitchStatus('p') == true)
        {
            Mode = Init;
            Ledcontrol.blinkLed('r');
            CyDelay(1000);
            Mode = Sleep;
        }
        else if (Mode == Sleep && Switchcontroller.getSwitchStatus('p') == false)
        {
            Mode = Off;
            Ledcontrol.turnOffLed('g');
            Ledcontrol.turnOffLed('r');
        }
        if (Mode == Sleep && SPIcontroller.ReadData() == 'o')
        {
            Mode = Control;
            Timer_1_Start();
            Ledcontrol.turnOffLed('r');
            Ledcontrol.blinkLed('g');
        }
        else if (Mode == Control && SPIcontroller.ReadData() == 'c')
        {
            Mode = Sleep;
            Timer_1_Stop();
            Ledcontrol.turnOffLed('r');
            Ledcontrol.turnOnLed('g');
        }
        if (Mode == Sleep && Switchcontroller.getSwitchStatus('f') == true)
        {
            Mode = Follow;
            Ledcontrol.turnOffLed('r');
            Ledcontrol.blinkLed('g');
        }
        else if (Mode == Follow && Switchcontroller.getSwitchStatus('f') == false)
        {
            Mode = Sleep;
            Ledcontrol.turnOffLed('r');
            Ledcontrol.turnOnLed('g');
        }
        /*     
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
            }
            break;
            default :
            {
                
            }
            break;
        }*/
    }
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
        Motor.setPower(Motor.getPower()-10); 
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
