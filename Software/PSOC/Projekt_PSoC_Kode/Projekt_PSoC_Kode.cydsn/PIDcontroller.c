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

#include "PIDcontroller.h"
enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4, Fallen = 5};
extern uint8_t Mode;

/***************************************************
* Default constructor for object creation. Initalizes
* member-variables
* @param  <float a0, a1, b1 - regulator coefficients, 
           float referance - distance to hold, pointer to Motor-object>>
* @return void
****************************************************/
PIDcontroller::PIDcontroller(float a0, float a1, float b1, float reference, MotorController *MotorPtr)
{
    MotorPtr_ = MotorPtr;
    a0_ = a0;
    a1_ = a1;
    b1_ = b1;
    setReference(reference);
}

PIDcontroller::~PIDcontroller()
{
}

/***************************************************
* Used to set reference variable 
* @param float reference
* @return none
****************************************************/
void PIDcontroller::setReference(float reference)
{
    ref_ = reference;
}

/***************************************************
* Used to get reference variable 
* @param none
* @return float reference
****************************************************/
float PIDcontroller::getReference(void) const
{
    return ref_;
}

/***************************************************
* Used to calculate and set error 
* @param float sensor_data
* @return none
****************************************************/
void PIDcontroller::calculateError(float MidSensor)
{
    error_ = ref_ - MidSensor;
}

/***************************************************
* Used to calculate control and regulate motors 
* @param <float sensor_data, float sensor_data>
* @return none
****************************************************/
void PIDcontroller::calculateControl(float leftSensor, float rightSensor)
{
	/*Calculate the control variable*/
	control_ = (b1_*old_control_) + (a0_*error_) + (a1_*old_error_); 
    
    control_ = control_/10;
    
    /*Limit control*/
	if (control_ > 100) 
    {
        control_ = 100;
	}
    else if (control_ < -100) 
    {
        control_ = -100;
    }
    else if(control_ <= 1 || control_ <= -1)
    {
        control_= 0;
    }
    
    if (Mode == Follow)                             //If mode is follow continue regulating
    {
        if (control_ >= 0)
        {           
            MotorPtr_->GoBackward(control_);        //Regulate
        }
        else
        {
            MotorPtr_->GoForward(control_*-1);      //Regulate
        }
    }
    else                                            //If mode is not follow stop motor
    {
        MotorPtr_->GoForward(0);
    }
    
    //Set old error and control
    old_error_ = error_;                            
    old_control_ = control_;
}