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

/* [] END OF FILE */

#include "LED.h"

LED::LED()
{
    LED_PWM_Start();
}

LED::~LED()
{
}

void LED::turnOnLed(char Color)
{
    if (Color == 'g' || Color == 'G')
    {
        LED_PWM_WriteCompare2(100);
    }
    else if(Color == 'r' || Color == 'R')
    {
        LED_PWM_WriteCompare1(100);
    }
}

void LED::turnOffLed(char Color)
{
    if (Color == 'g' || Color == 'G')
    {
        LED_PWM_WriteCompare2(0);
    }
    else if(Color == 'r' || Color == 'R')
    {
        LED_PWM_WriteCompare1(0);
    }
}

void LED::blinkLed(char Color)
{
    if (Color == 'g' || Color == 'G')
    {
        LED_PWM_WriteCompare2(50);
    }
    else if(Color == 'r' || Color == 'R')
    {
        LED_PWM_WriteCompare1(50);        
    }
}