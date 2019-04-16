/*******************************************************************************
* File Name: MotorPWM_2.h  
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

#if !defined(CY_PINS_MotorPWM_2_H) /* Pins MotorPWM_2_H */
#define CY_PINS_MotorPWM_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MotorPWM_2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MotorPWM_2__PORT == 15 && ((MotorPWM_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MotorPWM_2_Write(uint8 value);
void    MotorPWM_2_SetDriveMode(uint8 mode);
uint8   MotorPWM_2_ReadDataReg(void);
uint8   MotorPWM_2_Read(void);
void    MotorPWM_2_SetInterruptMode(uint16 position, uint16 mode);
uint8   MotorPWM_2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MotorPWM_2_SetDriveMode() function.
     *  @{
     */
        #define MotorPWM_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MotorPWM_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MotorPWM_2_DM_RES_UP          PIN_DM_RES_UP
        #define MotorPWM_2_DM_RES_DWN         PIN_DM_RES_DWN
        #define MotorPWM_2_DM_OD_LO           PIN_DM_OD_LO
        #define MotorPWM_2_DM_OD_HI           PIN_DM_OD_HI
        #define MotorPWM_2_DM_STRONG          PIN_DM_STRONG
        #define MotorPWM_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MotorPWM_2_MASK               MotorPWM_2__MASK
#define MotorPWM_2_SHIFT              MotorPWM_2__SHIFT
#define MotorPWM_2_WIDTH              1u

/* Interrupt constants */
#if defined(MotorPWM_2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MotorPWM_2_SetInterruptMode() function.
     *  @{
     */
        #define MotorPWM_2_INTR_NONE      (uint16)(0x0000u)
        #define MotorPWM_2_INTR_RISING    (uint16)(0x0001u)
        #define MotorPWM_2_INTR_FALLING   (uint16)(0x0002u)
        #define MotorPWM_2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MotorPWM_2_INTR_MASK      (0x01u) 
#endif /* (MotorPWM_2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MotorPWM_2_PS                     (* (reg8 *) MotorPWM_2__PS)
/* Data Register */
#define MotorPWM_2_DR                     (* (reg8 *) MotorPWM_2__DR)
/* Port Number */
#define MotorPWM_2_PRT_NUM                (* (reg8 *) MotorPWM_2__PRT) 
/* Connect to Analog Globals */                                                  
#define MotorPWM_2_AG                     (* (reg8 *) MotorPWM_2__AG)                       
/* Analog MUX bux enable */
#define MotorPWM_2_AMUX                   (* (reg8 *) MotorPWM_2__AMUX) 
/* Bidirectional Enable */                                                        
#define MotorPWM_2_BIE                    (* (reg8 *) MotorPWM_2__BIE)
/* Bit-mask for Aliased Register Access */
#define MotorPWM_2_BIT_MASK               (* (reg8 *) MotorPWM_2__BIT_MASK)
/* Bypass Enable */
#define MotorPWM_2_BYP                    (* (reg8 *) MotorPWM_2__BYP)
/* Port wide control signals */                                                   
#define MotorPWM_2_CTL                    (* (reg8 *) MotorPWM_2__CTL)
/* Drive Modes */
#define MotorPWM_2_DM0                    (* (reg8 *) MotorPWM_2__DM0) 
#define MotorPWM_2_DM1                    (* (reg8 *) MotorPWM_2__DM1)
#define MotorPWM_2_DM2                    (* (reg8 *) MotorPWM_2__DM2) 
/* Input Buffer Disable Override */
#define MotorPWM_2_INP_DIS                (* (reg8 *) MotorPWM_2__INP_DIS)
/* LCD Common or Segment Drive */
#define MotorPWM_2_LCD_COM_SEG            (* (reg8 *) MotorPWM_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define MotorPWM_2_LCD_EN                 (* (reg8 *) MotorPWM_2__LCD_EN)
/* Slew Rate Control */
#define MotorPWM_2_SLW                    (* (reg8 *) MotorPWM_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MotorPWM_2_PRTDSI__CAPS_SEL       (* (reg8 *) MotorPWM_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MotorPWM_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MotorPWM_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MotorPWM_2_PRTDSI__OE_SEL0        (* (reg8 *) MotorPWM_2__PRTDSI__OE_SEL0) 
#define MotorPWM_2_PRTDSI__OE_SEL1        (* (reg8 *) MotorPWM_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MotorPWM_2_PRTDSI__OUT_SEL0       (* (reg8 *) MotorPWM_2__PRTDSI__OUT_SEL0) 
#define MotorPWM_2_PRTDSI__OUT_SEL1       (* (reg8 *) MotorPWM_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MotorPWM_2_PRTDSI__SYNC_OUT       (* (reg8 *) MotorPWM_2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MotorPWM_2__SIO_CFG)
    #define MotorPWM_2_SIO_HYST_EN        (* (reg8 *) MotorPWM_2__SIO_HYST_EN)
    #define MotorPWM_2_SIO_REG_HIFREQ     (* (reg8 *) MotorPWM_2__SIO_REG_HIFREQ)
    #define MotorPWM_2_SIO_CFG            (* (reg8 *) MotorPWM_2__SIO_CFG)
    #define MotorPWM_2_SIO_DIFF           (* (reg8 *) MotorPWM_2__SIO_DIFF)
#endif /* (MotorPWM_2__SIO_CFG) */

/* Interrupt Registers */
#if defined(MotorPWM_2__INTSTAT)
    #define MotorPWM_2_INTSTAT            (* (reg8 *) MotorPWM_2__INTSTAT)
    #define MotorPWM_2_SNAP               (* (reg8 *) MotorPWM_2__SNAP)
    
	#define MotorPWM_2_0_INTTYPE_REG 		(* (reg8 *) MotorPWM_2__0__INTTYPE)
#endif /* (MotorPWM_2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MotorPWM_2_H */


/* [] END OF FILE */
