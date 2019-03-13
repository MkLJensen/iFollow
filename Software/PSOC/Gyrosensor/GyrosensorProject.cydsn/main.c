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

/*ADDRESSES FOR I2C-COMMUNICATION WITH MPU6050*/
#define MPU6050_ADD     (0x68)      // Device / Slave Address
#define PWR_MGMT_1      (0x6B)      // Reset with 0x00 to wakeup
#define SMPRT_DIV       (0x19)      // Register for holding sample rate 109
#define GYRO_CONFIG     (0x1b)      // Register for self-test and scale 0x18 for fullscale
#define ACCEL_CONFIG    (0x1c)      // --||-- 0x08 fullscale +- 4g
#define USER_CTRL       (0x6a)      // 0x00 to disable master mode | 0x20 to enable
#define INT_PIN_CFG     (0x37)      // 0x02 I2C bypass enable
#define CONFIG          (0x1A)      // For setting DLPF - fast or slow
#define START_GYRO_DATA (0x43)      // First address in gyro registers      | 6bytes long
#define START_ACC_DATA  (0x3b)      // First address in accelerometer       | 6bytes long
#define START_TEMP_DATA (0x41)      // First address in temperature sensor  | 2bytes long

/*ADDITIONAL MACROS*/
#define WAIT_DELAY      (250)       // Delay in ms     
#define CLEAR_SCREEN    "\x1b[2J"   // Clears terminal when printed

/*Structure for gyrosensor data*/
typedef struct gyro_data {
    int16_t x;
    int16_t y;
    int16_t z;
    float x_rad;
    float y_rad;
    float z_rad;
} gyro_data;

/*Structure for accelerometer data*/
typedef struct acc_data {
    int16_t x;
    int16_t y;
    int16_t z;
    float x_G;
    float y_G;
    float z_G;
} acc_data;

/*Structure for all sensor data*/
typedef struct sensor_data {
    gyro_data gyro;
    acc_data acc;
    float temperature;
} sensor_data;


/*TODO: PUT IN HEADER!!*/
void readGyroData(gyro_data*);
void I2CReadBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
void I2CWriteBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *value);
void I2CWriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t value);
void readGyroData(gyro_data* gp);
void readAccData(acc_data* ap);
void readTemp(float *temperature);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    I2C_1_Start();
    char buf[255];
    UART_1_PutString("Done intializing UART and I2C!\r\n");
    
    //Initializing MPU6050 -- Might need some tweaking
    UART_1_PutString("Intializing MPU6050..\r\n");
    I2CWriteByte(MPU6050_ADD, PWR_MGMT_1, 0x00);
    I2CWriteByte(MPU6050_ADD,SMPRT_DIV,109);
    I2CWriteByte(MPU6050_ADD,GYRO_CONFIG,0x18); // FULLSCALE
    I2CWriteByte(MPU6050_ADD,USER_CTRL,0x20);
    I2CWriteByte(MPU6050_ADD,INT_PIN_CFG,0x37);
    I2CWriteByte(MPU6050_ADD,CONFIG,6);         //6 very slow
    
    
    //Struct for gyro-data
    gyro_data gdata;
    
    //Structure for accelerometer-data
    acc_data adata;
    
    float temperature_C;
    
    for(;;)
    {
        /*Read data from gyrosensor with I2C*/
        readGyroData(&gdata);
        readAccData(&adata);
        readTemp(&temperature_C);
        
        /*Print out gyro-data*/
        UART_1_PutString(CLEAR_SCREEN);
        sprintf(buf,"------ GYRO-DATA ------\r\nX: %d\r\nY: %d\r\nZ: %d\r\n",
            gdata.x,
            gdata.y,
            gdata.z
        );
        UART_1_PutString(buf);
        
        /*Print out float gyro-data*/
        sprintf(buf,"------ GYRO-DATA (Rad/s) ------\r\nX: %f\r\nY: %f\r\nZ: %f\r\n",
            gdata.x_rad,
            gdata.y_rad,
            gdata.z_rad
        );
        UART_1_PutString(buf);
        
        /*Print out acc-data*/
        sprintf(buf,"------ ACC-DATA (G's) ------\r\nX: %f\r\nY: %f\r\nZ: %f\r\n",
            adata.x_G,
            adata.y_G,
            adata.z_G
        );
        UART_1_PutString(buf);

        /*Print out temperature*/
        sprintf(buf,"------ Temperature (C) ------\r\nTemperature: %f\r\n",
            temperature_C
        );
        UART_1_PutString(buf);
        
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
    I2C_1_MasterSendRestart(device_add, I2C_1_READ_XFER_MODE);
    
    /*Start reading nobytes bytes*/
    while (i++ < (nobytes-1)) {
        *data++ = I2C_1_MasterReadByte(I2C_1_ACK_DATA); // ACK to signal keep reading
    }
    *data = I2C_1_MasterReadByte(I2C_1_NAK_DATA); // NAK to signal stop reading
    
    /*Send stop condition*/
    I2C_1_MasterSendStop();    
}

void readGyroData(gyro_data* gp)
{
    //Buffer for sensor data
    uint8_t rx_buffer[6];

    /*Read data into buffer*/
    I2CReadBytes(MPU6050_ADD,START_GYRO_DATA, 6, rx_buffer);
    
    //Extract raw data
    gp->x = rx_buffer[0] << 8 | rx_buffer[1];
    gp->y = rx_buffer[2] << 8 | rx_buffer[3];
    gp->z = rx_buffer[4] << 8 | rx_buffer[5];
    
    /*Convert into radians per second*/
    gp->x_rad = gp->x / 939.650784f;
    gp->y_rad = gp->y / 939.650784f;
    gp->z_rad = gp->z / 939.650784f;

}

void readAccData(acc_data* ap)
{
    //Buffer for sensor data
    uint8_t rx_buffer[6];

    /*Read data into buffer*/
    I2CReadBytes(MPU6050_ADD,START_ACC_DATA, 6, rx_buffer);
    
    //Extract raw data
    ap->x = rx_buffer[0] << 8 | rx_buffer[1];
    ap->y = rx_buffer[2] << 8 | rx_buffer[3];
    ap->z = rx_buffer[4] << 8 | rx_buffer[5];
    
    /*Convert into G's*/
    ap->x_G = ap->x / 8192.0f;
    ap->y_G = ap->y / 8192.0f;
    ap->z_G = ap->z / 8192.0f;
}

void readTemp(float *temperature)
{
    uint8_t rx_buffer[2];
    uint16_t temp_buffer;
    
    /*Read data into buffer*/
    I2CReadBytes(MPU6050_ADD,START_TEMP_DATA, 2, rx_buffer);
    
    /*Extract raw data*/
    temp_buffer = rx_buffer[0] << 8 | rx_buffer[1];
    
    /*Convert to celsius*/
    *temperature = temp_buffer / 340.0f + 36.53f;
}

void readAllSensorData(sensor_data *sp)
{
    /*Read data from all sensors*/
    readAccData(&sp->acc);      //Accelerometer data
    readGyroData(&sp->gyro);    //Gyro data
    readTemp(&sp->temperature); //Temperature
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
