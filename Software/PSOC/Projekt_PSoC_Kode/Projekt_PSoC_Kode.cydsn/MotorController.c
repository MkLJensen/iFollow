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

void MotorController::TurnRight(int pwm)
{
    int CMP = 500+(4*pwm);
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

void MotorController::TurnLeft(int pwm)
{
    int CMP = 500+(4*pwm);
    if ((Leftpwm_ - CMP) < 0)
    {
        setLeftPWM(CMP+(CMP-Leftpwm_));
        setRightPWM(0);
    }
    else 
    {
        setLeftPWM(Rightpwm_-CMP);
    }
    setDir(FORWARD);
}

void MotorController::Stop(void)
{
    setLeftPWM(0);
    setRightPWM(0);
}

void MotorController::Control(char dir)
{
    if (power_ < 25)
    {
        setPower(25); 
    }
    else
    {
        setPower(getPower() + 10);
    }
    setOldPower();
    if (dir == 'f')
    {
        GoForward(power_);
    }
    else if (dir == 'b')
    {
        GoBackward(power_);
    }
    else if (dir == 'r')
    {
        TurnRight(power_);
    }
    else if (dir == 'l')
    {
        TurnLeft(power_);
    }
}

int MotorController::getPower(void) const
{
    return power_;
}

void MotorController::setPower(int power)
{
    if (power > 100)
    {
        power_ = 100; 
    }
    else if (power <= 0)
    {
        power_ = 0;
    }
    else
    {
        power_ = power;
    }
}

int MotorController::getOldPower(void) const
{
    return oldpower_;
}

void MotorController::setOldPower(void)
{
    oldpower_ = power_;
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