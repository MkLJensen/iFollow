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

void PIDcontroller::setReference(float reference)
{
    ref_ = reference;
}

float PIDcontroller::getReference(void) const
{
    return ref_;
}

void PIDcontroller::calculateError(float MidSensor)
{
    error_ = ref_ - MidSensor;
}

void PIDcontroller::calculateControl(float leftSensor, float rightSensor)
{
	/*Calculate the control variable*/
	control_ = (b1_*old_control_) + (a0_*error_) + (a1_*old_error_); 
    
    control_ = control_/6;
    
    /*Limit control*/
	if (control_ > 100) 
    {
        control_ = 100;
	}
    else if (control_ < -100) 
    {
        control_ = -100;
    }
    
    if (Mode == Follow)
    {
        if (control_ >= 0)
        {           
            MotorPtr_->GoBackward(control_);
        }
        else
        {
            /*if (leftSensor-10 > rightSensor)
            {
                MotorPtr_->TurnLeft(control_);
                
            }
            else if (rightSensor-10 > leftSensor)
            {
                 MotorPtr_->TurnRight(control_);
            }
            else
            {
                 MotorPtr_->GoForward(control_*-1);
            }*/
            MotorPtr_->GoForward(control_*-1);
        }
    }
    else
    {
        MotorPtr_->GoForward(0);
    }
    
    old_error_ = error_;
    old_control_ = control_;
}