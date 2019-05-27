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
    PWM_1_Start();      //Start PWM Modul
}

MotorController::~MotorController()
{
}

void MotorController::GoForward(int pwm)
{
    if (pwm == 0)
    {
        //If PWM = 0 then set to 0
        setLeftPWM(0);           
        setRightPWM(0);
    }
    else
    {   
        //If PWM > 0 set PWM to value (Compare value starts at 500 because 500 = motor not moving)
        setLeftPWM(500+(4*pwm));
        setRightPWM(500+(4*pwm));
    }
    //Set direction to forward
    setDir(FORWARD);
}
    
void MotorController::GoBackward(int pwm)
{
     if (pwm == 0)
    {
        //If PWM = 0 then set to 0
        setLeftPWM(0);
        setRightPWM(0);
    }
    else
    {
        //If PWM > 0 set PWM to value (Compare value starts at 500 because 500 = motor not moving)
        setLeftPWM(500+(4*pwm));
        setRightPWM(500+(4*pwm));
    }
    //Set direction to backward
    setDir(BARCKWARD);
}

void MotorController::TurnRight(int pwm)
{
    //Calculate compare value
    int CMP = 500+(4*pwm);
    
    //Set compare value 200 higher on one side to turn
    setLeftPWM(CMP);
    setRightPWM(CMP-300);
    
    if (CMP-300 < 0)
    {
        setRightPWM(0);
    }
    //Set direction to backward
    setDir(FORWARD);
}

void MotorController::TurnLeft(int pwm)
{
    //Calculate compare value
    int CMP = 500+(4*pwm);
    
    //Set compare value 200 higher on one side to turn
    setRightPWM(CMP);
    setLeftPWM(CMP-300);
    if (CMP-300 < 0)
    {
        setLeftPWM(0);
    }
    //Set direction to backward
    setDir(FORWARD);
}

void MotorController::Control(char dir)
{
    //Increments power_ 
    if (power_ < 25)
    {
        setPower(25); 
    }
    else
    {
        setPower(getPower() + 10);
    }
        
    if ((oldDir_ == 'f' && dir == 'b') || (oldDir_ == 'b' && dir == 'f'))
    {
        setPower(25);
    }
    
    //Sets oldpower_
    setOldPower();
    
    //Makes iFollow move depending on argument
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
    oldDir_ = dir;
}

int MotorController::getPower(void) const
{
    //Returns private variable power_
    return power_;
}

void MotorController::setPower(int power)
{
    //Sets power to arguments
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
    //Returns private variable oldpower_
    return oldpower_;
}

void MotorController::setOldPower(void)
{
    //Sets oldpower_ to power_
    oldpower_ = power_;
}
      
void MotorController::setLeftPWM(int pwm)
{
    //Sets private variable and write compare value
    Leftpwm_ = pwm;
    if (direction_ == FORWARD)
    {
        PWM_1_WriteCompare1(pwm); 
    }
    else
    {
        PWM_1_WriteCompare1(pwm); 
    }
}
      
int MotorController::getLeftPWM(void) const
{
    //Returns private variable Leftpwm_
    return Leftpwm_;
}
    
void MotorController::setRightPWM(int pwm)
{
    //Sets private variable and write compare value
    Rightpwm_ = pwm;
    PWM_1_WriteCompare2(pwm);
}
      
int MotorController::getRightPWM(void) const
{
    //Returns private variable Rightpwm_
    return Rightpwm_;
}
      
void MotorController::setDir(bool dir)
{
    //Sets direction_ variable and changes direction on pins
    direction_ = dir;
    Forward_ORANGE_Write(dir);
    Backward_GUL_Write(!dir);
}
      
bool MotorController::getDir(void) const
{
    //Returns private variable direction_
    return direction_;
}