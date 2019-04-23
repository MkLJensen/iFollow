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
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif

#define FORWARD 1
#define BARCKWARD 0

class MotorController 
{
public:
   MotorController();
   ~MotorController();      
   void GoForward(int pwm = 0);
   void GoBackward(int pwm = 0);
   void TurnLeft(int pwm = 0);
   void TurnRight(int pwm = 0);
   void Stop(void);
   void Control(char dir);

   void setLeftPWM(int pwm);
   int getLeftPWM(void) const;
   void setRightPWM(int pwm);
   int getRightPWM(void) const;

   void setDir(bool dir);
   bool getDir(void) const;

   int getPower(void) const;
   void setPower(int);
   int getOldPower(void) const;
   void setOldPower(int);

private:
    int Leftpwm_ = 0, Rightpwm_ = 0;
    bool direction_ = FORWARD;
    int power_ = 0, oldpower_ = 0;
    
};

#endif