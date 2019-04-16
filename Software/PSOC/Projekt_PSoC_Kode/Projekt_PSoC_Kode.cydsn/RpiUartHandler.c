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

#include "RpiUartHandler.h"

extern int i;

RpiUartHandler::RpiUartHandler()
{
    
}

RpiUartHandler::~RpiUartHandler()
{
    
}

void RpiUartHandler::UARTreaddata(MotorController * motorPtr)
{
    uint8_t DataLen = UART_1_GetRxBufferSize();
     
    if(DataLen > 1)
    {
        uint8_t byteReceived[DataLen];
        for (uint8_t i = 0; i < DataLen; i++)         
        {
            byteReceived[i] = UART_1_ReadRxData();
        }
        handleByteReceived(byteReceived, motorPtr);
    }
}

void RpiUartHandler::handleByteReceived(uint8_t byteReceived[], MotorController * MotorPtr)
{
    switch(byteReceived[0])
    {
        case 'f' :
        {
            MotorPtr->GoForward(byteReceived[1]);
            UART_1_PutString(" Going forward    ");
            if (byteReceived[1] == 97)
            {
                 UART_1_PutChar(byteReceived[1]);
            }
        }
        break;
        case 'b' :
        {
            MotorPtr->GoBackward(byteReceived[1]);
            UART_1_PutString("Going backward");
            UART_1_PutChar(byteReceived[1]);
        }
        break;
        case 'l' :
        {
            MotorPtr->Turn(byteReceived[1], 'l');
            CyDelay(500);
            MotorPtr->GoForward(0);
            UART_1_PutString("Going left");
            UART_1_PutChar(byteReceived[1]);
        }
        break;
        case 'r' :
        {
            MotorPtr->Turn(byteReceived[1], 'r');
            CyDelay(500);
            MotorPtr->GoForward(0);
            UART_1_PutString("Going right");
            UART_1_PutChar(byteReceived[1]);
        }
        break;
        case 'i' :
        {
            i++;
        }
        break;
        case 'k' :
        {
            i--;
        }
        break;
        default :
        {
            //UART_1_PutString("Hello");
        }
        break;
    }
}

