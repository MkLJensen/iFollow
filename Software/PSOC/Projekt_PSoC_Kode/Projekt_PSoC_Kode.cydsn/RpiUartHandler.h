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
#ifndef RPIUARTHANDLER_H_
#define RPIUARTHANDLER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif
    
#include "MotorController.h"

#define FORWARD 1
#define BARCKWARD 0

class RpiUartHandler 
{
public:
   RpiUartHandler();
   ~RpiUartHandler();
   void UARTreaddata(MotorController * motorPtr);
   void handleByteReceived(uint8_t byteReceived[], MotorController * motorPtr);

private:
    uint8_t DataLen = 0;
 };

#endif