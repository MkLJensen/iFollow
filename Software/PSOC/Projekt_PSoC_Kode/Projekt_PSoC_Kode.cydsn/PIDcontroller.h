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

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif

#include "MotorController.h"

class PIDcontroller 
{
public:
   PIDcontroller(float P, float I, float D, float goal);
   ~PIDcontroller();      
   void setGoal(float Goal);
   float getGoal(void) const;
   void calculateError(float Signal);
   float calculateControl(MotorController * MotorPtr);

private:
   float kp_ = 0, ki_ = 0, kd_ = 0;
   float goal_ = 0;
   float error_ = 0, last_error_ = 0, integral_ = 0, derivative_ = 0, control_ = 0;

};


#endif