/* ========================================
 *
 * Copyright Nicklas Grunert, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Nicklas Grunert.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

/*ADRESSES FOR I2C-COMMUNICATION WITH MP1202*/
#define MP1202_ADD      (0x70)      // 7-bit Device / Slave address
#define RANGE_COMMAND   (81)        // Range reader command
#define RANGE_BYTES     (2)         // Number of bytes to read from reg-address

/*ADDITIONAL MACROS*/
#define WAIT_DELAY      (250)       // Delay in ms     
#define CLEAR_SCREEN    "\x1b[2J"   // Clears terminal when printed

/*Variable for sonar-sensor*/
int16_t range_value = 0.0f;

/*TODO: PUT IN HEADER!!*/
void I2CReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
void I2CWriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
void I2CWriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value);
void readSonarSensor(int16_t *range);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    Clock_Start();
    I2C_1_Start();
    char buf[255];
    UART_1_PutString("Done intializing UART and I2C!\r\n");
        
    for(;;)
    {
        /*Read data from gyrosensor with I2C*/
        readSonarSensor(&range_value);
        
        //UART_1_PutString(CLEAR_SCREEN);
        
        /*Print out range in cm*/
        sprintf(buf,"------ SONAR RANGE DATA ------\r\nRange: %d cm\r\n",
            range_value
        );
        UART_1_PutString(buf);
        
        //UART_1_PutString(CLEAR_SCREEN);
        /*Delay so it is possible to read the data!*/
        CyDelay(WAIT_DELAY);
    }
    
}

void I2CWriteBytes(uint8_t device_add, uint8_t reg_add, uint8_t nobytes, uint8_t *data) {
    
    uint8_t i=0;    //Index for loop
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Begin writing to register address*/
    I2C_1_MasterWriteByte(reg_add);
    
    while (i++ < nobytes) 
    {
        /*Keep writing bytes untill nobytes is reached*/
        I2C_1_MasterWriteByte(*data++);
    }
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();
}

void I2CWriteByte(uint8_t device_add, uint8_t reg_add, uint8_t data) {
    /*Just call I2CWriteBytes function*/
	I2CWriteBytes(device_add, reg_add, 1, &data);
}

void I2CReadBytes(uint8_t device_add, uint8_t reg_add, uint8_t nobytes, uint8_t *data)
{
    uint8_t i=0;    //Index for loop
    
    /*Send start condition*/
    I2C_1_MasterSendStart(device_add, I2C_1_WRITE_XFER_MODE);
    
    /*Specify register address to read from*/
    I2C_1_MasterWriteByte(reg_add);
    
    
    /*Go into read-mode*/
    CyDelay(100);
    I2C_1_MasterSendRestart(device_add, I2C_1_READ_XFER_MODE);
    
    /*Start reading nobytes bytes*/
    while (i++ < (nobytes-1)) {
        *data++ = I2C_1_MasterReadByte(I2C_1_ACK_DATA); // ACK to signal keep reading
    }
    *data = I2C_1_MasterReadByte(I2C_1_NAK_DATA); // NAK to signal stop reading
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();
}

void readSonarSensor(int16_t *range)
{
    uint8_t rx_buffer[2];
    uint16_t range_buffer;
    
    /*Read data into buffer*/
    I2CReadBytes(MP1202_ADD, RANGE_COMMAND, RANGE_BYTES, rx_buffer);
    
    /** For debug
    char buffer[255];
    sprintf(buffer,"%d -- %d", rx_buffer[0],rx_buffer[1]);
    
    UART_1_PutString(buffer);
    */
    
    /*Extract raw data*/
    range_buffer = rx_buffer[0] << 8 | rx_buffer[1];
    
    /*Convert to float*/
    *range = range_buffer;   //You might want to divide by constant
}

void handleErrors(uint8 error)
{
    switch(error){
        case I2C_1_MSTR_NO_ERROR:
            UART_1_PutString("MSTR NO ERROR\r\n");
            break;
        case I2C_1_MSTR_BUS_BUSY:
            UART_1_PutString("MSTR BUS BUSY\r\n");
            break;
        case I2C_1_MSTR_NOT_READY:
            UART_1_PutString("MSTR NOT READY\r\n");
            break;
        case I2C_1_MSTR_ERR_LB_NAK:
            UART_1_PutString("MSTR ERR LB NAK\r\n");
            break;
        case I2C_1_MSTR_ERR_ARB_LOST:
            UART_1_PutString("MSTR ERR ARB LOST\r\n");
            break;
    };
}
/* [] END OF FILE */
