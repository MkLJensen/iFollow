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
#ifndef MOTORCLASS_H_
#define MOTORCLASS_H_

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

class MotorClass 
{
public:
   MotorClass()
      {
         setLeftPWM(0);
         setRightPWM(0);
         setDir(FORWARD);
      }

   ~MotorClass()
      {
         
      }
      
   void GoForward(int pwm)
      {
         setLeftPWM(pwm);
         setRightPWM(pwm);
         setDir(FORWARD);
      }
      
   void GoBackward(int pwm)
      {
         setLeftPWM(pwm);
         setRightPWM(pwm);
         setDir(BARCKWARD);
      }
      
   void Turn(signed int pwm)
      {
        if (pwm > 0)
        {
            if (Rightpwm_ > (100-pwm))
            {
                setLeftPWM(100-pwm);
            }
            setRightPWM(pwm+Rightpwm_);
            setDir(FORWARD);
        }
        else if (pwm < 0)
        {
            if (Leftpwm_ > (100-pwm))
            {
                setRightPWM(100-pwm);
            }
            setLeftPWM(pwm+Leftpwm_);
            setDir(FORWARD); 
        }
      }
      
   void setLeftPWM(int pwm)
      {
         Leftpwm_ = pwm;
         PWM_1_WriteCompare1(pwm);
      }
      
   int getLeftPWM(void) const
      {
         return Leftpwm_;
      }
    
   void setRightPWM(int pwm)
      {
         Leftpwm_ = pwm;
         PWM_1_WriteCompare2(pwm);
      }
      
   int getRightPWM(void) const
      {
         return Leftpwm_;
      }
      
   void setDir(bool dir)
      {
         direction_ = dir;
         Pin_3_Write(dir);
         Pin_4_Write(!dir);
      }
      
   bool getDir(void) const
      {
         return direction_;
      }

private:
    int Leftpwm_ = 0, Rightpwm_ = 0;
    bool direction_ = FORWARD;
    
};

#endif