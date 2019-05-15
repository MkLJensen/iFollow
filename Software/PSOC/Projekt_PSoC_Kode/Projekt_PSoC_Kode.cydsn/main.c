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
CY_ISR_PROTO(isr_handler);

enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4, Fallen = 5};
uint8_t Mode = Off; 
uint8_t byteR;

ToF obj;
Switches Switchcontroller;
MotorController Motor;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
           
    I2C_1_Start();
    UART_1_Start();
    SPIS_Start();
    isr_1_StartEx(isr_handler);
    Power_isr_StartEx(PowerSwitch_Handler);
    Follow_isr_StartEx(FollowSwitch_Handler);
    Motor_timer_isr_StartEx(Control_timer_isr);
       
    Gyro GyroController;
    RpiSPI SPIcontroller(&GyroController, &Motor);
    LED Ledcontrol;
    PIDcontroller PIDcontrol(142.9, -136.2, -0.693, 1000, &Motor );
               
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
        }
        if (Mode == Sleep && SPIcontroller.ReadData() == 'o')
        {
            Mode = Control;
            Timer_1_Start();
        }
        else if (Mode == Control && SPIcontroller.ReadData() == 'c')
        {
            Mode = Sleep;
            Timer_1_Stop();
        }
        if (Mode == Sleep && Switchcontroller.getSwitchStatus('f') == true)
        {
            Mode = Follow;
            SPIS_1_Start();
        }
        else if (Mode == Follow && Switchcontroller.getSwitchStatus('f') == false)
        {
            Mode = Sleep;
            SPIS_1_Stop();
        }
        
        switch(Mode)
        {
            case Off :
            {
                Ledcontrol.turnOffLed('g');
                Ledcontrol.turnOffLed('r');
                SPIcontroller.ReadData();
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
                Motor.GoForward(0);
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
                
                SPIcontroller.ReadData();
                           
                PIDcontrol.calculateError(obj.getMidSensor());
                PIDcontrol.calculateControl();
            }
            break;
            default :
            {
                
            }
            break;
        }
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

CY_ISR(isr_handler)
{
   byteR = SPIS_1_ReadRxData();                                                             // Gemmer aflæsning af RX-buffer
   obj.handleByte(byteR);
}

/* [] END OF FILE */
