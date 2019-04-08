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

#ifdef __cplusplus
extern "C" {
#endif

    // PSoC include, this has to be wrapped
    #include "project.h"

#ifdef __cplusplus
}
#endif

#include "i2c.h"
#include "Laser.h"
#include <stdio.h>

/*DEFINES FOR TERATERM TERMINAL*/
#define WAIT_DELAY      (250)       // Delay in ms     
#define CLEAR_SCREEN    "\x1b[2J"   // Clears terminal when printed

volatile uint16_t range = 0;
char* buf;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    UART_1_PutString("Program started!\r\n");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Laser VL53L0X;
    UART_1_PutString("Created Laser Object!\r\n");
    VL53L0X.Init(false);
    UART_1_PutString("Initialized VL53L0X\r\n");
    VL53L0X.SetTimeout(500);
    UART_1_PutString("Set timeout!\r\n");
    VL53L0X.StartContinuous();
    UART_1_PutString("Started continuous!\r\n");
    
    for(;;)
    {
        range = VL53L0X.ReadRangeContinuousMillimeters();
        /*Print out range to screen*/
        UART_1_PutString(CLEAR_SCREEN);
        sprintf(buf,"------ RANGING DATA ------\r\nDistance: %d mm\r\n",
            range
        );
        UART_1_PutString(buf);
        
        /*Delay so it is possible to read the data!*/
        CyDelay(WAIT_DELAY);  
    }
    
    return 0;
}
/* [] END OF FILE */
