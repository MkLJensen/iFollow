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

#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

#include "i2c.h"
#include "Gyro.h"
#include <stdio.h>

/*ADDITIONAL MACROS*/
#define WAIT_DELAY      (250)       // Delay in ms     
#define CLEAR_SCREEN    "\x1b[2J"   // Clears terminal when printed

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    I2C_1_Start();
    char buf[255];
    UART_1_PutString("Done intializing UART and I2C!\r\n");
	
	Gyro gyro;
	gyro.getSensorData();
    
    for(;;)
    {

        /*Delay so it is possible to read the data!*/
        CyDelay(WAIT_DELAY);
    }
    
    return 0;
}

/* [] END OF FILE */
