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
/***************************************************
* Default constructor for object creation. Initalizes
* member-variables
* @param  none
* @return void
****************************************************/
LED::LED()
{
    LED_PWM_Start();
}
/***************************************************
* Destructor for object-destruction, deletes
* dynamically allocated variables
* @param none
* @return void
****************************************************/
LED::~LED()
{
}

/***************************************************
* Used to turn on LED 
* @param color of LED - R or G
* @return none
****************************************************/
void LED::turnOnLed(char Color)
{
    if (Color == 'g' || Color == 'G')
    {
        if (LED_PWM_ReadCompare2() != 255)
        {
            LED_PWM_WriteCompare2(255);
        }
    }
    else if(Color == 'r' || Color == 'R')
    {
        if (LED_PWM_ReadCompare1() != 255)
        {
            LED_PWM_WriteCompare1(255); 
        }
    }
}

/***************************************************
* Used to turn off LED 
* @param color of LED - R or G
* @return none
****************************************************/
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

/***************************************************
* Used to blink LED 
* @param color of LED - R or G
* @return none
****************************************************/
void LED::blinkLed(char Color)
{
    if (Color == 'g' || Color == 'G')
    {
        LED_PWM_WriteCompare2(122);
    }
    else if(Color == 'r' || Color == 'R')
    {
        LED_PWM_WriteCompare1(122);        
    }
}