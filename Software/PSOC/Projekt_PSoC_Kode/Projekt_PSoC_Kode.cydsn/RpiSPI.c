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

RpiSPI::RpiSPI()
{
    
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

uint8_t RpiSPI::ReadData(MotorController * motorPtr)
{     
    if (SPIS_ReadTxStatus() == SPIS_STS_TX_FIFO_EMPTY)
    {
        //GET SENSOR DATA!!!!
        SPIS_WriteTxData(0/*SENSORDATA*/);
        
    }
    //else if (//GET SONSOR DATA != OLD SENSOR DATA)
    {
        SPIS_ClearTxBuffer();
        SPIS_WriteTxData(1/*SENSORDATA*/);
    }
    if(SPIS_ReadRxStatus() == SPIS_STS_RX_FIFO_NOT_EMPTY)
    {
        int DataLen = 10;
            uint8_t byteReceived[DataLen];
        int i = 0;
        while(SPIS_ReadRxStatus() != SPIS_STS_RX_FIFO_EMPTY)        
        {
            byteReceived[i] = UART_1_ReadRxData();
            i++;
        }
        return handleByteReceived(byteReceived, motorPtr);
    }
    return 0;
    
}

uint8_t RpiSPI::handleByteReceived(uint8_t byteReceived[], MotorController * MotorPtr)
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

