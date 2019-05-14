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
#ifndef RPIUART_H_
#define RPIUART_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif
#define true 1
#define false 0

#include "MotorController.h"
#include "Gyro.h"

class RpiSPI 
{
public:
   RpiSPI(Gyro * GyroPtr, MotorController * MotorPtr);
   ~RpiSPI();
   uint8_t ReadData();
   uint8_t handleByteReceived(uint8_t byteReceived);
   void TransmitData(uint8_t Data);

private:
   uint8_t ControlModeActive = false;
   MotorController * MotorPtr_;
   Gyro * GyroPtr_;
   int GyroState_ = 0;
    
 };

#endif