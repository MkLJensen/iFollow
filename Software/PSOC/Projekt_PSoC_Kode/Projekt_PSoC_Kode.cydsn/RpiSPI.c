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
extern uint8_t oldMode;
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
    if(SPIS_GetRxBufferSize() > 0)
    {
        uint8_t byteReceived = SPIS_ReadRxData();
        
        if (GyroPtr_->hasFallen() == 1)        //Check if fallen
        {
            if (Mode != Fallen)
            {
                oldMode = Mode;                     //Save old mode
            }
            Mode = Fallen;                          //Set mode to fallen
            TransmitData(Mode);       //transmit mode
        }
        if (GyroPtr_->hasFallen() == 0 && Mode == Fallen)        //Check if not fallen
        {
            Mode = oldMode;                         //Reset mode
            TransmitData(Mode);       //Transmit mode
        }
        else  
        {
            TransmitData(Mode);       //Transmit mode
        }
               
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
            if (ControlModeActive == true && Mode == Control)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'b' :
        {  
            if (ControlModeActive == true && Mode == Control)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'l' :
        {
            if (ControlModeActive == true && Mode == Control)
            {
                MotorPtr_->Control(byteReceived);
            }
            return 0;
        }
        break;
        case 'r' :
        {
            if (ControlModeActive == true && Mode == Control)
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
            MotorPtr_->GoForward(0);
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