/*******************************************************************************
* File Name: Pulse_ADC_SAR_Seq_INT.c
* Version 2.40
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Pulse_ADC_SAR_Seq.h"



/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(Pulse_ADC_SAR_Seq_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: Pulse_ADC_SAR_Seq_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( Pulse_ADC_SAR_Seq_ISR )
    {
        uint32 intr_status;

        /* Read interrupt status register */
        intr_status = Pulse_ADC_SAR_Seq_SAR_INTR_REG;

        #ifdef Pulse_ADC_SAR_Seq_ISR_INTERRUPT_CALLBACK
            Pulse_ADC_SAR_Seq_ISR_InterruptCallback();
        #endif /* Pulse_ADC_SAR_Seq_ISR_INTERRUPT_CALLBACK */


        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
        /* `#START MAIN_ADC_ISR`  */

        /* `#END`  */
        
        /* Clear handled interrupt */
        Pulse_ADC_SAR_Seq_SAR_INTR_REG = intr_status;
    }

#endif   /* End Pulse_ADC_SAR_Seq_IRQ_REMOVE */


/* [] END OF FILE */
