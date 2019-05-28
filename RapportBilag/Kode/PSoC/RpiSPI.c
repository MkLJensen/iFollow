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

/***************************************************
* Default constructor for object creation. Initalizes
* member-variables
* @param  <pointer to Gyro-object, pointer to Motor-object>
* @return void
****************************************************/
RpiSPI::RpiSPI(Gyro * Gyro, MotorController * Motor)
{
    MotorPtr_ = Motor;
    GyroPtr_ = Gyro;
}

RpiSPI::~RpiSPI()
{
    
}

/***************************************************
* Used to transmit data 
* @param uint8_t 8 bits of data
* @return none
****************************************************/
void RpiSPI::TransmitData(uint8_t Data)
{
    SPIS_ClearTxBuffer();
    SPIS_WriteTxData(Data);
}

/***************************************************
* Used to read data, transmit mode and act on recived byte. 
* @param none
* @return <uint8_t 'o' if control mode is suppose to turn on
          'c' if control mode is supposte to turn off>
****************************************************/
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

/***************************************************
* Used to Act on recived byte. 
* @param <uint8_t data - recived from Readdata()>
* @return <uint8_t 'o' if control mode is suppose to turn on,
          'c' if control mode is supposte to turn off, else 0>
****************************************************/
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