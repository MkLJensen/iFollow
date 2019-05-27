/*******************************************************************************
* File Name: Tester.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Tester_H)
#define CY_ISR_Tester_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Tester_Start(void);
void Tester_StartEx(cyisraddress address);
void Tester_Stop(void);

CY_ISR_PROTO(Tester_Interrupt);

void Tester_SetVector(cyisraddress address);
cyisraddress Tester_GetVector(void);

void Tester_SetPriority(uint8 priority);
uint8 Tester_GetPriority(void);

void Tester_Enable(void);
uint8 Tester_GetState(void);
void Tester_Disable(void);

void Tester_SetPending(void);
void Tester_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Tester ISR. */
#define Tester_INTC_VECTOR            ((reg32 *) Tester__INTC_VECT)

/* Address of the Tester ISR priority. */
#define Tester_INTC_PRIOR             ((reg8 *) Tester__INTC_PRIOR_REG)

/* Priority of the Tester interrupt. */
#define Tester_INTC_PRIOR_NUMBER      Tester__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Tester interrupt. */
#define Tester_INTC_SET_EN            ((reg32 *) Tester__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Tester interrupt. */
#define Tester_INTC_CLR_EN            ((reg32 *) Tester__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Tester interrupt state to pending. */
#define Tester_INTC_SET_PD            ((reg32 *) Tester__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Tester interrupt. */
#define Tester_INTC_CLR_PD            ((reg32 *) Tester__INTC_CLR_PD_REG)


#endif /* CY_ISR_Tester_H */


/* [] END OF FILE */
