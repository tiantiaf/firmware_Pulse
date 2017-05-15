/*******************************************************************************
* File Name: Pulse_ADC_SAR_Seq_intClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Pulse_ADC_SAR_Seq_intClock_H)
#define CY_CLOCK_Pulse_ADC_SAR_Seq_intClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Pulse_ADC_SAR_Seq_intClock_StartEx(uint32 alignClkDiv);
#define Pulse_ADC_SAR_Seq_intClock_Start() \
    Pulse_ADC_SAR_Seq_intClock_StartEx(Pulse_ADC_SAR_Seq_intClock__PA_DIV_ID)

#else

void Pulse_ADC_SAR_Seq_intClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Pulse_ADC_SAR_Seq_intClock_Stop(void);

void Pulse_ADC_SAR_Seq_intClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Pulse_ADC_SAR_Seq_intClock_GetDividerRegister(void);
uint8  Pulse_ADC_SAR_Seq_intClock_GetFractionalDividerRegister(void);

#define Pulse_ADC_SAR_Seq_intClock_Enable()                         Pulse_ADC_SAR_Seq_intClock_Start()
#define Pulse_ADC_SAR_Seq_intClock_Disable()                        Pulse_ADC_SAR_Seq_intClock_Stop()
#define Pulse_ADC_SAR_Seq_intClock_SetDividerRegister(clkDivider, reset)  \
    Pulse_ADC_SAR_Seq_intClock_SetFractionalDividerRegister((clkDivider), 0u)
#define Pulse_ADC_SAR_Seq_intClock_SetDivider(clkDivider)           Pulse_ADC_SAR_Seq_intClock_SetDividerRegister((clkDivider), 1u)
#define Pulse_ADC_SAR_Seq_intClock_SetDividerValue(clkDivider)      Pulse_ADC_SAR_Seq_intClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Pulse_ADC_SAR_Seq_intClock_DIV_ID     Pulse_ADC_SAR_Seq_intClock__DIV_ID

#define Pulse_ADC_SAR_Seq_intClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Pulse_ADC_SAR_Seq_intClock_CTRL_REG   (*(reg32 *)Pulse_ADC_SAR_Seq_intClock__CTRL_REGISTER)
#define Pulse_ADC_SAR_Seq_intClock_DIV_REG    (*(reg32 *)Pulse_ADC_SAR_Seq_intClock__DIV_REGISTER)

#define Pulse_ADC_SAR_Seq_intClock_CMD_DIV_SHIFT          (0u)
#define Pulse_ADC_SAR_Seq_intClock_CMD_PA_DIV_SHIFT       (8u)
#define Pulse_ADC_SAR_Seq_intClock_CMD_DISABLE_SHIFT      (30u)
#define Pulse_ADC_SAR_Seq_intClock_CMD_ENABLE_SHIFT       (31u)

#define Pulse_ADC_SAR_Seq_intClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Pulse_ADC_SAR_Seq_intClock_CMD_DISABLE_SHIFT))
#define Pulse_ADC_SAR_Seq_intClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Pulse_ADC_SAR_Seq_intClock_CMD_ENABLE_SHIFT))

#define Pulse_ADC_SAR_Seq_intClock_DIV_FRAC_MASK  (0x000000F8u)
#define Pulse_ADC_SAR_Seq_intClock_DIV_FRAC_SHIFT (3u)
#define Pulse_ADC_SAR_Seq_intClock_DIV_INT_MASK   (0xFFFFFF00u)
#define Pulse_ADC_SAR_Seq_intClock_DIV_INT_SHIFT  (8u)

#else 

#define Pulse_ADC_SAR_Seq_intClock_DIV_REG        (*(reg32 *)Pulse_ADC_SAR_Seq_intClock__REGISTER)
#define Pulse_ADC_SAR_Seq_intClock_ENABLE_REG     Pulse_ADC_SAR_Seq_intClock_DIV_REG
#define Pulse_ADC_SAR_Seq_intClock_DIV_FRAC_MASK  Pulse_ADC_SAR_Seq_intClock__FRAC_MASK
#define Pulse_ADC_SAR_Seq_intClock_DIV_FRAC_SHIFT (16u)
#define Pulse_ADC_SAR_Seq_intClock_DIV_INT_MASK   Pulse_ADC_SAR_Seq_intClock__DIVIDER_MASK
#define Pulse_ADC_SAR_Seq_intClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Pulse_ADC_SAR_Seq_intClock_H) */

/* [] END OF FILE */
