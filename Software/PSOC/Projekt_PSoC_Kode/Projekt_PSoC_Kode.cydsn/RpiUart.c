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
                MotorPtr->GoForward(byteReceived[1]);
                UART_1_PutString(" Going forward    ");
                if (byteReceived[1] == 97)
                {
                     UART_1_PutChar(byteReceived[1]);
                }
            }
            return 0;
        }
        break;
        case 'b' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->GoBackward(byteReceived[1]);
                UART_1_PutString("Going backward");
                UART_1_PutChar(byteReceived[1]);
            }
            return 0;
        }
        break;
        case 'l' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->Turn(byteReceived[1], 'l');
                CyDelay(500);
                MotorPtr->GoForward(0);
                UART_1_PutString("Going left");
                UART_1_PutChar(byteReceived[1]);
            }
            return 0;
        }
        break;
        case 'r' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr->Turn(byteReceived[1], 'r');
                CyDelay(500);
                MotorPtr->GoForward(0);
                UART_1_PutString("Going right");
                UART_1_PutChar(byteReceived[1]);
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
            MotorPtr->GoForward(0);
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

