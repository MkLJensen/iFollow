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

#include "MotorController.h"

MotorController::MotorController()
{
    
}

MotorController::~MotorController()
{
}

void MotorController::GoForward(int pwm)
{
    setLeftPWM(pwm);
    setRightPWM(pwm);
    setDir(FORWARD);
}
    
void MotorController::GoBackward(int pwm)
{
    setLeftPWM(pwm);
    setRightPWM(pwm);
    setDir(BARCKWARD);
}
      
void MotorController::Turn(int pwm, char dir)
{
    if (dir == 'l')
    {
        if (Rightpwm_ > (100-pwm))
        {
            setLeftPWM(100-pwm);
        }
        setRightPWM(pwm+Rightpwm_);
        setDir(FORWARD);
    }
    else if (dir == 'r')
    {
        if (Leftpwm_ > (100-pwm))
        {
            setRightPWM(100-pwm);
        }
        setLeftPWM(pwm+Leftpwm_);
        setDir(FORWARD); 
    }
}
      
void MotorController::setLeftPWM(int pwm)
{
    Leftpwm_ = pwm;
    PWM_1_WriteCompare1(pwm);
}
      
int MotorController::getLeftPWM(void) const
{
    return Leftpwm_;
}
    
void MotorController::setRightPWM(int pwm)
{
    Rightpwm_ = pwm;
    PWM_1_WriteCompare2(pwm);
}
      
int MotorController::getRightPWM(void) const
{
    return Rightpwm_;
}
      
void MotorController::setDir(bool dir)
{
    direction_ = dir;
    Pin_3_Write(dir);
    Pin_4_Write(!dir);
}
      
bool MotorController::getDir(void) const
{
    return direction_;
}