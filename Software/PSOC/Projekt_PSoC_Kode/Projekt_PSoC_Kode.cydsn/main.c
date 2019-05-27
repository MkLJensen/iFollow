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
int lul = 0, lul2 = 0;
CY_ISR_PROTO(Tester1)
    {
        UART_1_PutChar(lul);
        lul = 0;
        lul2 = 0;
    }

//Enum to make states easier to read
enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4, Fallen = 5};

//Declare global variable
uint8_t Mode = Off, oldMode = Off; 

//Declare objects used in interrupts
ToF obj;
Switches Switchcontroller;
MotorController Motor;
PIDcontroller PIDcontrol(6.842, -3.296, -0.2332, 500, &Motor);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
           
    I2C_1_Start();                                      //Start I2C 
    SPIS_Start();                                       //Start SPI (RPI-PSoC)
    isr_1_StartEx(isr_handler);                         //Start SPI interrupt
    Power_isr_StartEx(PowerSwitch_Handler);             //Start PowerBtn interrupt
    Follow_isr_StartEx(FollowSwitch_Handler);           //Start FollowBtn interrupt
    Motor_timer_isr_StartEx(Control_timer_isr);         //Start MotorControl timer interrupt
    
    UART_1_Start();
    
    UART_1_PutString("HEEEJ");
    Tester_StartEx(Tester1);
       
    // Declare objects
    Gyro GyroController;
    RpiSPI SPIcontroller(&GyroController, &Motor);
    LED Ledcontrol;
               
    for(;;)
    {                    
        if(Mode == Off && Switchcontroller.getSwitchStatus('p') == true)            //Check powerbutton and mode is off
        {
            Mode = Init;                    //Set mode init
        }
        else if (Mode == Sleep && Switchcontroller.getSwitchStatus('p') == false)   //Check powerbutton and mode sleep
        {
            Mode = Off;                     //Set mode off
        }
        if (Mode == Sleep && SPIcontroller.ReadData() == 'o')                       //Check if data recived is 'o' and mode is sleep
        {
            Mode = Control;                 //Set mode control
            Timer_1_Start();                //Start motor timer
        }
        else if (Mode == Control && SPIcontroller.ReadData() == 'c')                //Check if data recived is 'c' and mode is control
        {
            Mode = Sleep;                   //Set mode sleep
            Timer_1_Stop();                 //Stop motor timer
        }
        if (Mode == Sleep && Switchcontroller.getSwitchStatus('f') == true)         //Check followbutton and mode sleep
        {
            Mode = Follow;                  //Set mode follow
            SPIS_1_Start();                 //Start SPI to arduino
            //Timer_2_Start();
        }
        else if (Mode == Follow && Switchcontroller.getSwitchStatus('f') == false)  //Check followbutton and mode follow
        {
            Mode = Sleep;                   //Set mode follow
            SPIS_1_Stop();                  //Stop SPI to arduino
        }
        
        switch(Mode)
        {
            case Off :
            {
                Ledcontrol.turnOffLed('g');     //Turn off green LED
                Ledcontrol.turnOffLed('r');     //Turn off red LED
                SPIcontroller.TransmitData(Mode);
            }
            break;
            case Init :
            {
                Ledcontrol.blinkLed('r');       //Blink red LED
                CyDelay(1000);
                Mode = Sleep;                   //Set mode to sleep
            }
            break;
            case Sleep :
            {
                Ledcontrol.turnOffLed('r');     //Turn off Red LED
                Ledcontrol.turnOnLed('g');      //Turn on green LED
                Motor.GoForward(0);             //Stop motor if running
            }
            break;
            case Control :
            {
                Ledcontrol.turnOffLed('r');     //Turn off red LED
                Ledcontrol.blinkLed('g');       //Blink green LED
            }
            break;
            case Follow :
            {
                Ledcontrol.turnOffLed('r');     //Turn off red LED
                Ledcontrol.blinkLed('g');       //Blink green LED
                SPIcontroller.ReadData();
                Timer_2_Start();
            }
            break;
            case Fallen :
            {
                Ledcontrol.turnOffLed('g');     //Turn off green LED
                Ledcontrol.blinkLed('r');       //Blink red LED
                SPIcontroller.ReadData();
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
    Switchcontroller.setSwitchStatus('P');          //Set switch status
}

CY_ISR(FollowSwitch_Handler)
{
    Switchcontroller.setSwitchStatus('F');          //Set switch status
}

CY_ISR(Control_timer_isr)
{                                                       //This timer is used to make iFollow ramp up when controlling it
    if (Motor.getOldPower() == Motor.getPower())        //If motor.control() havent been called they will be equal
    {
        Motor.setPower(Motor.getPower()-10);            //Set power lower
        Motor.setOldPower();                            //Set old power to new power
        if (Motor.getPower() > 0)                       //If power is greater than 0 set pwm to power value
        {
            Motor.setLeftPWM(500+4*Motor.getPower());
            Motor.setRightPWM(500+4*Motor.getPower());
        }
        else                                            //else set it to 0
        {
            Motor.setLeftPWM(0);
            Motor.setRightPWM(0);
        }
    }
}

CY_ISR(isr_handler)
{
    bool regulate = false;
    if (SPIS_1_GetRxBufferSize() >= 4)
    {
        lul++;
        for(uint8_t i; i < 4; i++)
        {
            obj.handleByte(SPIS_1_ReadRxData()); 
        }
        regulate = true;
    }
    if (regulate == true)
    {
        PIDcontrol.calculateError(obj.getLeftSensor());                               //Calculate error
        PIDcontrol.calculateControl(obj.getLeftSensor(), obj.getRightSensor());       //Regulate iFollow 
        lul2++;
    }
}

/* [] END OF FILE */
