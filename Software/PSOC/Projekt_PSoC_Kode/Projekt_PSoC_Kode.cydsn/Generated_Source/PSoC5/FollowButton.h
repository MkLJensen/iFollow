/*******************************************************************************
* File Name: FollowButton.h  
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

#if !defined(CY_PINS_FollowButton_H) /* Pins FollowButton_H */
#define CY_PINS_FollowButton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FollowButton_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FollowButton__PORT == 15 && ((FollowButton__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FollowButton_Write(uint8 value);
void    FollowButton_SetDriveMode(uint8 mode);
uint8   FollowButton_ReadDataReg(void);
uint8   FollowButton_Read(void);
void    FollowButton_SetInterruptMode(uint16 position, uint16 mode);
uint8   FollowButton_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FollowButton_SetDriveMode() function.
     *  @{
     */
        #define FollowButton_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FollowButton_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FollowButton_DM_RES_UP          PIN_DM_RES_UP
        #define FollowButton_DM_RES_DWN         PIN_DM_RES_DWN
        #define FollowButton_DM_OD_LO           PIN_DM_OD_LO
        #define FollowButton_DM_OD_HI           PIN_DM_OD_HI
        #define FollowButton_DM_STRONG          PIN_DM_STRONG
        #define FollowButton_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FollowButton_MASK               FollowButton__MASK
#define FollowButton_SHIFT              FollowButton__SHIFT
#define FollowButton_WIDTH              1u

/* Interrupt constants */
#if defined(FollowButton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FollowButton_SetInterruptMode() function.
     *  @{
     */
        #define FollowButton_INTR_NONE      (uint16)(0x0000u)
        #define FollowButton_INTR_RISING    (uint16)(0x0001u)
        #define FollowButton_INTR_FALLING   (uint16)(0x0002u)
        #define FollowButton_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FollowButton_INTR_MASK      (0x01u) 
#endif /* (FollowButton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FollowButton_PS                     (* (reg8 *) FollowButton__PS)
/* Data Register */
#define FollowButton_DR                     (* (reg8 *) FollowButton__DR)
/* Port Number */
#define FollowButton_PRT_NUM                (* (reg8 *) FollowButton__PRT) 
/* Connect to Analog Globals */                                                  
#define FollowButton_AG                     (* (reg8 *) FollowButton__AG)                       
/* Analog MUX bux enable */
#define FollowButton_AMUX                   (* (reg8 *) FollowButton__AMUX) 
/* Bidirectional Enable */                                                        
#define FollowButton_BIE                    (* (reg8 *) FollowButton__BIE)
/* Bit-mask for Aliased Register Access */
#define FollowButton_BIT_MASK               (* (reg8 *) FollowButton__BIT_MASK)
/* Bypass Enable */
#define FollowButton_BYP                    (* (reg8 *) FollowButton__BYP)
/* Port wide control signals */                                                   
#define FollowButton_CTL                    (* (reg8 *) FollowButton__CTL)
/* Drive Modes */
#define FollowButton_DM0                    (* (reg8 *) FollowButton__DM0) 
#define FollowButton_DM1                    (* (reg8 *) FollowButton__DM1)
#define FollowButton_DM2                    (* (reg8 *) FollowButton__DM2) 
/* Input Buffer Disable Override */
#define FollowButton_INP_DIS                (* (reg8 *) FollowButton__INP_DIS)
/* LCD Common or Segment Drive */
#define FollowButton_LCD_COM_SEG            (* (reg8 *) FollowButton__LCD_COM_SEG)
/* Enable Segment LCD */
#define FollowButton_LCD_EN                 (* (reg8 *) FollowButton__LCD_EN)
/* Slew Rate Control */
#define FollowButton_SLW                    (* (reg8 *) FollowButton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FollowButton_PRTDSI__CAPS_SEL       (* (reg8 *) FollowButton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FollowButton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FollowButton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FollowButton_PRTDSI__OE_SEL0        (* (reg8 *) FollowButton__PRTDSI__OE_SEL0) 
#define FollowButton_PRTDSI__OE_SEL1        (* (reg8 *) FollowButton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FollowButton_PRTDSI__OUT_SEL0       (* (reg8 *) FollowButton__PRTDSI__OUT_SEL0) 
#define FollowButton_PRTDSI__OUT_SEL1       (* (reg8 *) FollowButton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FollowButton_PRTDSI__SYNC_OUT       (* (reg8 *) FollowButton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FollowButton__SIO_CFG)
    #define FollowButton_SIO_HYST_EN        (* (reg8 *) FollowButton__SIO_HYST_EN)
    #define FollowButton_SIO_REG_HIFREQ     (* (reg8 *) FollowButton__SIO_REG_HIFREQ)
    #define FollowButton_SIO_CFG            (* (reg8 *) FollowButton__SIO_CFG)
    #define FollowButton_SIO_DIFF           (* (reg8 *) FollowButton__SIO_DIFF)
#endif /* (FollowButton__SIO_CFG) */

/* Interrupt Registers */
#if defined(FollowButton__INTSTAT)
    #define FollowButton_INTSTAT            (* (reg8 *) FollowButton__INTSTAT)
    #define FollowButton_SNAP               (* (reg8 *) FollowButton__SNAP)
    
	#define FollowButton_0_INTTYPE_REG 		(* (reg8 *) FollowButton__0__INTTYPE)
#endif /* (FollowButton__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FollowButton_H */


/* [] END OF FILE */
