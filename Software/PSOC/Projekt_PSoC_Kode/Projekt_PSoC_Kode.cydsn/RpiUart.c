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

#include "RpiUart.h"

extern int power_;

RpiUart::RpiUart()
{
    
}

RpiUart::~RpiUart()
{
    
}

void RpiUart::TransmitData(uint8_t data[], uint8_t size)
{
    for (uint8_t i = 0; i <= size; i++)
    {       
        UART_1_PutChar(data[i]);
    }
    
}

uint8_t RpiUart::ReadData(MotorController * motorPtr)
{
    uint8_t DataLen = UART_1_GetRxBufferSize();
     
    if(DataLen > 1)
    {
        uint8_t byteReceived[DataLen];
        for (uint8_t i = 0; i < DataLen; i++)         
        {
            byteReceived[i] = UART_1_ReadRxData();
        }
        return handleByteReceived(byteReceived, motorPtr);
    }
    return 0;
    
}

uint8_t RpiUart::handleByteReceived(uint8_t byteReceived[], MotorController * MotorPtr)
{
    switch(byteReceived[0])
    {
        case 'f' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->Control(byteReceived[0]);
            }
            return 0;
        }
        break;
        case 'b' :
        {  
            if (ControlModeActive == true)
            {
                MotorPtr->Control(byteReceived[0]);
            }
            return 0;
        }
        break;
        case 'l' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->Control(byteReceived[0]);
            }
            return 0;
        }
        break;
        case 'r' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->Control(byteReceived[0]);
            }
            return 0;
        }
        break;
        case 'o' :
        {
            ControlModeActive = true;
            return 'o';
        }
        break;
         case 'c' :
        {
            ControlModeActive = false;
            MotorPtr->Stop();
            return 'c';
        }
        break;        
        default :
        {
            return 0;
        }
        break;
    }
}

