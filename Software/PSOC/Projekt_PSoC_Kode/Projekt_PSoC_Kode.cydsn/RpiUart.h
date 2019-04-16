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
    
#include "MotorController.h"

#define FORWARD 1
#define BARCKWARD 0

class RpiUart 
{
public:
   RpiUart();
   ~RpiUart();
   void ReadData(MotorController * motorPtr);
   void handleByteReceived(uint8_t byteReceived[], MotorController * motorPtr);
   void TransmitData(uint8_t data[], uint8_t size);

private:
    
 };

#endif