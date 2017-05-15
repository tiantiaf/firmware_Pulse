/*******************************************************************************
* File Name: Pulse.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pulse_H) /* Pins Pulse_H */
#define CY_PINS_Pulse_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pulse_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Pulse_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Pulse_Read(void);
void    Pulse_Write(uint8 value);
uint8   Pulse_ReadDataReg(void);
#if defined(Pulse__PC) || (CY_PSOC4_4200L) 
    void    Pulse_SetDriveMode(uint8 mode);
#endif
void    Pulse_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pulse_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Pulse_Sleep(void); 
void Pulse_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Pulse__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Pulse_DRIVE_MODE_BITS        (3)
    #define Pulse_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pulse_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Pulse_SetDriveMode() function.
         *  @{
         */
        #define Pulse_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Pulse_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Pulse_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Pulse_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Pulse_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Pulse_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Pulse_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Pulse_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Pulse_MASK               Pulse__MASK
#define Pulse_SHIFT              Pulse__SHIFT
#define Pulse_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pulse_SetInterruptMode() function.
     *  @{
     */
        #define Pulse_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Pulse_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Pulse_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Pulse_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Pulse__SIO)
    #define Pulse_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Pulse__PC) && (CY_PSOC4_4200L)
    #define Pulse_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Pulse_USBIO_DISABLE              ((uint32)(~Pulse_USBIO_ENABLE))
    #define Pulse_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Pulse_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Pulse_USBIO_ENTER_SLEEP          ((uint32)((1u << Pulse_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Pulse_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pulse_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Pulse_USBIO_SUSPEND_SHIFT)))
    #define Pulse_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Pulse_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pulse_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Pulse__PC)
    /* Port Configuration */
    #define Pulse_PC                 (* (reg32 *) Pulse__PC)
#endif
/* Pin State */
#define Pulse_PS                     (* (reg32 *) Pulse__PS)
/* Data Register */
#define Pulse_DR                     (* (reg32 *) Pulse__DR)
/* Input Buffer Disable Override */
#define Pulse_INP_DIS                (* (reg32 *) Pulse__PC2)

/* Interrupt configuration Registers */
#define Pulse_INTCFG                 (* (reg32 *) Pulse__INTCFG)
#define Pulse_INTSTAT                (* (reg32 *) Pulse__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Pulse_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Pulse__SIO)
    #define Pulse_SIO_REG            (* (reg32 *) Pulse__SIO)
#endif /* (Pulse__SIO_CFG) */

/* USBIO registers */
#if !defined(Pulse__PC) && (CY_PSOC4_4200L)
    #define Pulse_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Pulse_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Pulse_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Pulse_DRIVE_MODE_SHIFT       (0x00u)
#define Pulse_DRIVE_MODE_MASK        (0x07u << Pulse_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Pulse_H */


/* [] END OF FILE */
