/*******************************************************************************
* File Name: Backward_GUL.h  
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

#if !defined(CY_PINS_Backward_GUL_H) /* Pins Backward_GUL_H */
#define CY_PINS_Backward_GUL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Backward_GUL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Backward_GUL__PORT == 15 && ((Backward_GUL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Backward_GUL_Write(uint8 value);
void    Backward_GUL_SetDriveMode(uint8 mode);
uint8   Backward_GUL_ReadDataReg(void);
uint8   Backward_GUL_Read(void);
void    Backward_GUL_SetInterruptMode(uint16 position, uint16 mode);
uint8   Backward_GUL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Backward_GUL_SetDriveMode() function.
     *  @{
     */
        #define Backward_GUL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Backward_GUL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Backward_GUL_DM_RES_UP          PIN_DM_RES_UP
        #define Backward_GUL_DM_RES_DWN         PIN_DM_RES_DWN
        #define Backward_GUL_DM_OD_LO           PIN_DM_OD_LO
        #define Backward_GUL_DM_OD_HI           PIN_DM_OD_HI
        #define Backward_GUL_DM_STRONG          PIN_DM_STRONG
        #define Backward_GUL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Backward_GUL_MASK               Backward_GUL__MASK
#define Backward_GUL_SHIFT              Backward_GUL__SHIFT
#define Backward_GUL_WIDTH              1u

/* Interrupt constants */
#if defined(Backward_GUL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Backward_GUL_SetInterruptMode() function.
     *  @{
     */
        #define Backward_GUL_INTR_NONE      (uint16)(0x0000u)
        #define Backward_GUL_INTR_RISING    (uint16)(0x0001u)
        #define Backward_GUL_INTR_FALLING   (uint16)(0x0002u)
        #define Backward_GUL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Backward_GUL_INTR_MASK      (0x01u) 
#endif /* (Backward_GUL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Backward_GUL_PS                     (* (reg8 *) Backward_GUL__PS)
/* Data Register */
#define Backward_GUL_DR                     (* (reg8 *) Backward_GUL__DR)
/* Port Number */
#define Backward_GUL_PRT_NUM                (* (reg8 *) Backward_GUL__PRT) 
/* Connect to Analog Globals */                                                  
#define Backward_GUL_AG                     (* (reg8 *) Backward_GUL__AG)                       
/* Analog MUX bux enable */
#define Backward_GUL_AMUX                   (* (reg8 *) Backward_GUL__AMUX) 
/* Bidirectional Enable */                                                        
#define Backward_GUL_BIE                    (* (reg8 *) Backward_GUL__BIE)
/* Bit-mask for Aliased Register Access */
#define Backward_GUL_BIT_MASK               (* (reg8 *) Backward_GUL__BIT_MASK)
/* Bypass Enable */
#define Backward_GUL_BYP                    (* (reg8 *) Backward_GUL__BYP)
/* Port wide control signals */                                                   
#define Backward_GUL_CTL                    (* (reg8 *) Backward_GUL__CTL)
/* Drive Modes */
#define Backward_GUL_DM0                    (* (reg8 *) Backward_GUL__DM0) 
#define Backward_GUL_DM1                    (* (reg8 *) Backward_GUL__DM1)
#define Backward_GUL_DM2                    (* (reg8 *) Backward_GUL__DM2) 
/* Input Buffer Disable Override */
#define Backward_GUL_INP_DIS                (* (reg8 *) Backward_GUL__INP_DIS)
/* LCD Common or Segment Drive */
#define Backward_GUL_LCD_COM_SEG            (* (reg8 *) Backward_GUL__LCD_COM_SEG)
/* Enable Segment LCD */
#define Backward_GUL_LCD_EN                 (* (reg8 *) Backward_GUL__LCD_EN)
/* Slew Rate Control */
#define Backward_GUL_SLW                    (* (reg8 *) Backward_GUL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Backward_GUL_PRTDSI__CAPS_SEL       (* (reg8 *) Backward_GUL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Backward_GUL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Backward_GUL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Backward_GUL_PRTDSI__OE_SEL0        (* (reg8 *) Backward_GUL__PRTDSI__OE_SEL0) 
#define Backward_GUL_PRTDSI__OE_SEL1        (* (reg8 *) Backward_GUL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Backward_GUL_PRTDSI__OUT_SEL0       (* (reg8 *) Backward_GUL__PRTDSI__OUT_SEL0) 
#define Backward_GUL_PRTDSI__OUT_SEL1       (* (reg8 *) Backward_GUL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Backward_GUL_PRTDSI__SYNC_OUT       (* (reg8 *) Backward_GUL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Backward_GUL__SIO_CFG)
    #define Backward_GUL_SIO_HYST_EN        (* (reg8 *) Backward_GUL__SIO_HYST_EN)
    #define Backward_GUL_SIO_REG_HIFREQ     (* (reg8 *) Backward_GUL__SIO_REG_HIFREQ)
    #define Backward_GUL_SIO_CFG            (* (reg8 *) Backward_GUL__SIO_CFG)
    #define Backward_GUL_SIO_DIFF           (* (reg8 *) Backward_GUL__SIO_DIFF)
#endif /* (Backward_GUL__SIO_CFG) */

/* Interrupt Registers */
#if defined(Backward_GUL__INTSTAT)
    #define Backward_GUL_INTSTAT            (* (reg8 *) Backward_GUL__INTSTAT)
    #define Backward_GUL_SNAP               (* (reg8 *) Backward_GUL__SNAP)
    
	#define Backward_GUL_0_INTTYPE_REG 		(* (reg8 *) Backward_GUL__0__INTTYPE)
#endif /* (Backward_GUL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Backward_GUL_H */


/* [] END OF FILE */
