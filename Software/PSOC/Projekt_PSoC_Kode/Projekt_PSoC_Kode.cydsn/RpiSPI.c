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

#include "RpiSPI.h"

extern int power_;

RpiSPI::RpiSPI(Gyro * Gyro, MotorController * Motor)
{
    MotorPtr_ = Motor;
    GyroPtr_ = Gyro;
    SPIS_WriteTxDataZero(GyroState_);
}

RpiSPI::~RpiSPI()
{
    
}

void RpiSPI::TransmitData(uint8_t data[], uint8_t size)
{
    for (uint8_t i = 0; i <= size; i++)
    {       
        UART_1_PutChar(data[i]);
    }
}

uint8_t RpiSPI::ReadData()
{     
    int State = GyroPtr_->hasFallen();
    
    if (SPIS_GetTxBufferSize() == 0)
    {
        GyroState_ = State;
        SPIS_WriteTxData(GyroState_);
        
    }
    else if (State != GyroState_)
    {
        SPIS_ClearTxBuffer();
        GyroState_ = State;
        SPIS_WriteTxData(State);
    }
    if(SPIS_GetRxBufferSize() > 0)
    {
        uint8_t byteReceived;
        byteReceived = SPIS_ReadRxData();
        /*uint8_t byteReceived[SPIS_GetRxBufferSize()];
        int i = 0;
        while(SPIS_GetRxBufferSize() != 0)        
        {
            byteReceived[i] = SPIS_ReadRxData();
            i++;
        }*/
        
        UART_1_PutString("Modtaget char er: ");
        UART_1_PutChar(byteReceived);
        UART_1_PutString("\r\n");
        return handleByteReceived(byteReceived);
    }
    return 0;
    
}

uint8_t RpiSPI::handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case 'f' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'b' :
        {  
            if (ControlModeActive == true)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'l' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'r' :
        {
            if (ControlModeActive == true)
            {
                MotorPtr_->Control(byteReceived);
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
            MotorPtr_->Stop();
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

