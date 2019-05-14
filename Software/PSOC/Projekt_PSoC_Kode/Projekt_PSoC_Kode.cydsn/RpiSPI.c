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

extern uint8_t Mode;
enum State {Off = 0, Init = 1, Sleep = 2, Control = 3, Follow = 4, Fallen = 5};

RpiSPI::RpiSPI(Gyro * Gyro, MotorController * Motor)
{
    MotorPtr_ = Motor;
    GyroPtr_ = Gyro;
    SPIS_WriteTxDataZero(GyroState_);
}

RpiSPI::~RpiSPI()
{
    
}

void RpiSPI::TransmitData(uint8_t Data)
{
    SPIS_ClearTxBuffer();
    SPIS_WriteTxData(Data);
}

uint8_t RpiSPI::ReadData()
{
    GyroState_ = GyroPtr_->hasFallen();
    if (GyroState_ == 1)
    {
        TransmitData(Fallen);
    }
    else
    {
        TransmitData(Mode);
    }
    /*  
    int State = GyroPtr_->hasFallen();
    
    if (SPIS_GetTxBufferSize() == 0)
    {
        SPIS_ClearTxBuffer();
        GyroState_ = State;
        SPIS_WriteTxData(GyroState_);
        
    }
    else if (State != GyroState_)
    {
        SPIS_ClearTxBuffer();
        GyroState_ = State;
        SPIS_WriteTxData(State);
    }*/
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

