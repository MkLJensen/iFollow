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

class RpiUart 
{
public:
   RpiUart();
   ~RpiUart();
   uint8_t ReadData(MotorController * motorPtr);
   uint8_t handleByteReceived(uint8_t byteReceived[], MotorController * motorPtr);
   void TransmitData(uint8_t data[], uint8_t size);

private:
   uint8_t ControlModeActive = false;
    
 };

#endif