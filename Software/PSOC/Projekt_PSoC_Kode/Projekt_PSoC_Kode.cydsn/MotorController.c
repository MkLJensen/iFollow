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
    PWM_1_Start();
}

MotorController::~MotorController()
{
}

void MotorController::GoForward(int pwm)
{
    if (pwm == 0)
    {
        setLeftPWM(0);
        setRightPWM(0);
    }
    else
    {
        setLeftPWM(500+(4*pwm));
        setRightPWM(500+(4*pwm));
    }
    setDir(FORWARD);
}
    
void MotorController::GoBackward(int pwm)
{
     if (pwm == 0)
    {
        setLeftPWM(0);
        setRightPWM(0);
    }
    else
    {
        setLeftPWM(500+(4*pwm));
        setRightPWM(500+(4*pwm));
    }
    setDir(BARCKWARD);
}
      
void MotorController::Turn(int pwm, char dir)
{
    int CMP = 500+(4*pwm);
    if (dir == 'l')
    {
        if ((Rightpwm_ - CMP) < 0)
        {
            setRightPWM(CMP+(CMP-Rightpwm_));
            setLeftPWM(0);
        }
        else 
        {
            setRightPWM(Rightpwm_-CMP);
        }
        setDir(FORWARD);
    }
    else if (dir == 'r')
    {
        if ((CMP + Leftpwm_) > 100)
        {
            setLeftPWM(100);
            setRightPWM(100-CMP);
        }
        else 
        {
            setLeftPWM(Leftpwm_+CMP);
        }
        setDir(FORWARD);
        /*
        if (Leftpwm_ > (100-pwm))
        {
            setRightPWM(100-pwm);
        }
        setLeftPWM(pwm+Leftpwm_);
        setDir(FORWARD); 
        */
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
    Forward_ORANGE_Write(dir);
    Backward_GUL_Write(!dir);
}
      
bool MotorController::getDir(void) const
{
    return direction_;
}