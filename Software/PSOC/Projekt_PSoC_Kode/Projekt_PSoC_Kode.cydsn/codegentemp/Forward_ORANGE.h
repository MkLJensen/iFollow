/*******************************************************************************
* File Name: Forward_ORANGE.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Forward_ORANGE_H) /* Pins Forward_ORANGE_H */
#define CY_PINS_Forward_ORANGE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Forward_ORANGE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Forward_ORANGE__PORT == 15 && ((Forward_ORANGE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Forward_ORANGE_Write(uint8 value);
void    Forward_ORANGE_SetDriveMode(uint8 mode);
uint8   Forward_ORANGE_ReadDataReg(void);
uint8   Forward_ORANGE_Read(void);
void    Forward_ORANGE_SetInterruptMode(uint16 position, uint16 mode);
uint8   Forward_ORANGE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Forward_ORANGE_SetDriveMode() function.
     *  @{
     */
        #define Forward_ORANGE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Forward_ORANGE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Forward_ORANGE_DM_RES_UP          PIN_DM_RES_UP
        #define Forward_ORANGE_DM_RES_DWN         PIN_DM_RES_DWN
        #define Forward_ORANGE_DM_OD_LO           PIN_DM_OD_LO
        #define Forward_ORANGE_DM_OD_HI           PIN_DM_OD_HI
        #define Forward_ORANGE_DM_STRONG          PIN_DM_STRONG
        #define Forward_ORANGE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Forward_ORANGE_MASK               Forward_ORANGE__MASK
#define Forward_ORANGE_SHIFT              Forward_ORANGE__SHIFT
#define Forward_ORANGE_WIDTH              1u

/* Interrupt constants */
#if defined(Forward_ORANGE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Forward_ORANGE_SetInterruptMode() function.
     *  @{
     */
        #define Forward_ORANGE_INTR_NONE      (uint16)(0x0000u)
        #define Forward_ORANGE_INTR_RISING    (uint16)(0x0001u)
        #define Forward_ORANGE_INTR_FALLING   (uint16)(0x0002u)
        #define Forward_ORANGE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Forward_ORANGE_INTR_MASK      (0x01u) 
#endif /* (Forward_ORANGE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Forward_ORANGE_PS                     (* (reg8 *) Forward_ORANGE__PS)
/* Data Register */
#define Forward_ORANGE_DR                     (* (reg8 *) Forward_ORANGE__DR)
/* Port Number */
#define Forward_ORANGE_PRT_NUM                (* (reg8 *) Forward_ORANGE__PRT) 
/* Connect to Analog Globals */                                                  
#define Forward_ORANGE_AG                     (* (reg8 *) Forward_ORANGE__AG)                       
/* Analog MUX bux enable */
#define Forward_ORANGE_AMUX                   (* (reg8 *) Forward_ORANGE__AMUX) 
/* Bidirectional Enable */                                                        
#define Forward_ORANGE_BIE                    (* (reg8 *) Forward_ORANGE__BIE)
/* Bit-mask for Aliased Register Access */
#define Forward_ORANGE_BIT_MASK               (* (reg8 *) Forward_ORANGE__BIT_MASK)
/* Bypass Enable */
#define Forward_ORANGE_BYP                    (* (reg8 *) Forward_ORANGE__BYP)
/* Port wide control signals */                                                   
#define Forward_ORANGE_CTL                    (* (reg8 *) Forward_ORANGE__CTL)
/* Drive Modes */
#define Forward_ORANGE_DM0                    (* (reg8 *) Forward_ORANGE__DM0) 
#define Forward_ORANGE_DM1                    (* (reg8 *) Forward_ORANGE__DM1)
#define Forward_ORANGE_DM2                    (* (reg8 *) Forward_ORANGE__DM2) 
/* Input Buffer Disable Override */
#define Forward_ORANGE_INP_DIS                (* (reg8 *) Forward_ORANGE__INP_DIS)
/* LCD Common or Segment Drive */
#define Forward_ORANGE_LCD_COM_SEG            (* (reg8 *) Forward_ORANGE__LCD_COM_SEG)
/* Enable Segment LCD */
#define Forward_ORANGE_LCD_EN                 (* (reg8 *) Forward_ORANGE__LCD_EN)
/* Slew Rate Control */
#define Forward_ORANGE_SLW                    (* (reg8 *) Forward_ORANGE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Forward_ORANGE_PRTDSI__CAPS_SEL       (* (reg8 *) Forward_ORANGE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Forward_ORANGE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Forward_ORANGE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Forward_ORANGE_PRTDSI__OE_SEL0        (* (reg8 *) Forward_ORANGE__PRTDSI__OE_SEL0) 
#define Forward_ORANGE_PRTDSI__OE_SEL1        (* (reg8 *) Forward_ORANGE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Forward_ORANGE_PRTDSI__OUT_SEL0       (* (reg8 *) Forward_ORANGE__PRTDSI__OUT_SEL0) 
#define Forward_ORANGE_PRTDSI__OUT_SEL1       (* (reg8 *) Forward_ORANGE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Forward_ORANGE_PRTDSI__SYNC_OUT       (* (reg8 *) Forward_ORANGE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Forward_ORANGE__SIO_CFG)
    #define Forward_ORANGE_SIO_HYST_EN        (* (reg8 *) Forward_ORANGE__SIO_HYST_EN)
    #define Forward_ORANGE_SIO_REG_HIFREQ     (* (reg8 *) Forward_ORANGE__SIO_REG_HIFREQ)
    #define Forward_ORANGE_SIO_CFG            (* (reg8 *) Forward_ORANGE__SIO_CFG)
    #define Forward_ORANGE_SIO_DIFF           (* (reg8 *) Forward_ORANGE__SIO_DIFF)
#endif /* (Forward_ORANGE__SIO_CFG) */

/* Interrupt Registers */
#if defined(Forward_ORANGE__INTSTAT)
    #define Forward_ORANGE_INTSTAT            (* (reg8 *) Forward_ORANGE__INTSTAT)
    #define Forward_ORANGE_SNAP               (* (reg8 *) Forward_ORANGE__SNAP)
    
	#define Forward_ORANGE_0_INTTYPE_REG 		(* (reg8 *) Forward_ORANGE__0__INTTYPE)
#endif /* (Forward_ORANGE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Forward_ORANGE_H */


/* [] END OF FILE */
