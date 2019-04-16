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
   void GoForward(int pwm);
   void GoBackward(int pwm);
   void Turn(int pwm, char dir);
   void setLeftPWM(int pwm);
   int getLeftPWM(void) const;
   void setRightPWM(int pwm);
   int getRightPWM(void) const;
   void setDir(bool dir);
   bool getDir(void) const;

private:
    int Leftpwm_ = 0, Rightpwm_ = 0;
    bool direction_ = FORWARD;
    
};

#endif