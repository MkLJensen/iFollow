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

PIDcontroller::PIDcontroller(float P, float I, float D, float goal)
{
    kp_ = P;
    ki_ = I;
    kd_ = D;
    goal_ = goal;
}

PIDcontroller::~PIDcontroller()
{
}

void PIDcontroller::setGoal(float goal)
{
    goal_ = goal;
}

float PIDcontroller::getGoal(void) const
{
    return goal_;
}

void PIDcontroller::calculateError(float Signal)
{
    /*Calculate Error (P)*/
	error_ = goal_ - Signal;
}

float PIDcontroller::calculateControl(MotorController * MotorPtr)
{
    /*Calculate integral (I)*/
	integral_ += error_;

    /*Calculate the derivative (D)*/
	derivative_ = error_ - last_error_;

	/*Calculate the control variable*/
	control_ = (kp_*error_) + (ki_*integral_) + (kd_*derivative_);
    
    /*Limit control*/
	if (control_ > 100) 
    {
        control_ = 100;
	}
    else if (control_ < -100) 
    {
        control_ = -100;
    }
    
    if (control_ >= 0)
    {
        MotorPtr->GoForward(control_);
    }
    else
    {
        MotorPtr->GoBackward(control_*-1);
    }
    
    return control_;
}