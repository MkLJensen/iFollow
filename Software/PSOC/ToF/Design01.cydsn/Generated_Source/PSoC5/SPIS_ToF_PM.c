/*******************************************************************************
* File Name: SPIS_ToF_PM.c
* Version 2.70
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIS_ToF_PVT.h"

static SPIS_ToF_BACKUP_STRUCT SPIS_ToF_backup = 
{
    SPIS_ToF_DISABLED,
    SPIS_ToF_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPIS_ToF_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIS_ToF_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIS_ToF_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPIS_ToF_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPIS_ToF_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPI Slave Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIS_ToF_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIS_ToF_Sleep(void) 
{
    /* Save components enable state */
    if ((SPIS_ToF_TX_STATUS_ACTL_REG & SPIS_ToF_INT_ENABLE) != 0u)
    {
        SPIS_ToF_backup.enableState = 1u;
    }
    else /* Components block is disabled */
    {
        SPIS_ToF_backup.enableState = 0u;
    }

    SPIS_ToF_Stop();

}


/*******************************************************************************
* Function Name: SPIS_ToF_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPIS_ToF_backup - used when non-retention registers are restored.
*  SPIS_ToF_txBufferWrite - modified every function call - resets to
*  zero.
*  SPIS_ToF_txBufferRead - modified every function call - resets to
*  zero.
*  SPIS_ToF_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPIS_ToF_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPIS_ToF_Wakeup(void) 
{
    #if (SPIS_ToF_TX_SOFTWARE_BUF_ENABLED)
        SPIS_ToF_txBufferFull = 0u;
        SPIS_ToF_txBufferRead = 0u;
        SPIS_ToF_txBufferWrite = 0u;
    #endif /* SPIS_ToF_TX_SOFTWARE_BUF_ENABLED */

    #if (SPIS_ToF_RX_SOFTWARE_BUF_ENABLED)
        SPIS_ToF_rxBufferFull = 0u;
        SPIS_ToF_rxBufferRead = 0u;
        SPIS_ToF_rxBufferWrite = 0u;
    #endif /* SPIS_ToF_RX_SOFTWARE_BUF_ENABLED */

    SPIS_ToF_ClearFIFO();

    /* Restore components block enable state */
    if (SPIS_ToF_backup.enableState != 0u)
    {
         /* Components block was enabled */
         SPIS_ToF_Enable();
    } /* Do nothing if components block was disabled */
}


/* [] END OF FILE */
