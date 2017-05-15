/*******************************************************************************
* File Name: Timer_Pulse_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Pulse.h"

static Timer_Pulse_backupStruct Timer_Pulse_backup;


/*******************************************************************************
* Function Name: Timer_Pulse_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Pulse_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Pulse_SaveConfig(void) 
{
    #if (!Timer_Pulse_UsingFixedFunction)
        Timer_Pulse_backup.TimerUdb = Timer_Pulse_ReadCounter();
        Timer_Pulse_backup.InterruptMaskValue = Timer_Pulse_STATUS_MASK;
        #if (Timer_Pulse_UsingHWCaptureCounter)
            Timer_Pulse_backup.TimerCaptureCounter = Timer_Pulse_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Pulse_UDB_CONTROL_REG_REMOVED)
            Timer_Pulse_backup.TimerControlRegister = Timer_Pulse_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Pulse_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Pulse_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Pulse_RestoreConfig(void) 
{   
    #if (!Timer_Pulse_UsingFixedFunction)

        Timer_Pulse_WriteCounter(Timer_Pulse_backup.TimerUdb);
        Timer_Pulse_STATUS_MASK =Timer_Pulse_backup.InterruptMaskValue;
        #if (Timer_Pulse_UsingHWCaptureCounter)
            Timer_Pulse_SetCaptureCount(Timer_Pulse_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Pulse_UDB_CONTROL_REG_REMOVED)
            Timer_Pulse_WriteControlRegister(Timer_Pulse_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Pulse_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Pulse_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Pulse_Sleep(void) 
{
    #if(!Timer_Pulse_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Pulse_CTRL_ENABLE == (Timer_Pulse_CONTROL & Timer_Pulse_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Pulse_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Pulse_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Pulse_Stop();
    Timer_Pulse_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Pulse_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Pulse_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Pulse_Wakeup(void) 
{
    Timer_Pulse_RestoreConfig();
    #if(!Timer_Pulse_UDB_CONTROL_REG_REMOVED)
        if(Timer_Pulse_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Pulse_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
