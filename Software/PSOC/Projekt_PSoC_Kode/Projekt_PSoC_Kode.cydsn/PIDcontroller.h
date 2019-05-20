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

class PIDcontroller : public MotorController
{
public:
   PIDcontroller(float a0, float a1, float b1, float reference, MotorController *MotorPtr);
   ~PIDcontroller();      
   void setReference(float reference);
   float getReference(void) const;
   void setMeasurement(float sensorData);
   float getMeasurement(void) const;
   void calculateError(float midSensor);
   void calculateControl(float leftSensor, float rightSensor);
   void setControlSignal(float control);
   void setControl();

private:
   float a0_ = 0, a1_ = 0, b1_ = 0;
   float ref_ = 0, data_ = 0;
   float error_ = 0, old_error_ = 0;
   float control_ = 0, old_control_ = 0;
   MotorController *MotorPtr_;

};


#endif