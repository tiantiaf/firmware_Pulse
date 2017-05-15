/* ========================================
 *
 * Tiantian Feng, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "Pulse_Init.h"
#include "Pulse_Timestamp.h"

/*******************************************************************************
* Function Name: InitializeSystem
********************************************************************************
* Summary:
* Start the components and initialize system.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void InitializeSystem(void)
{
	/* Enable global interrupt mask */
	CyGlobalIntEnable; 
		
	/* Start BLE component and register the CustomEventHandler function. This 
	 * function exposes the events from BLE component for application use */
    CyBle_Start(CustomEventHandler);
    
    LED_Write(LED_ON);
    
    Timer_Pulse_Init();
    Timer_Pulse_Start();
    
    Pulse_ADC_SAR_Seq_Init();
    Pulse_ADC_SAR_Seq_Start();
    Pulse_ADC_SAR_Seq_StartConvert();
    
    Pulse_ADC_SAR_Seq_IsEndConversion(Pulse_ADC_SAR_Seq_WAIT_FOR_RESULT);
    
    ms_isr_StartEx(MS_ISR);
}


void StopTimer(void)
{
    ms_isr_Stop();
    
}

uint16 ReadPulseData(){
    uint16 pulse = 0;
    pulse = Pulse_ADC_SAR_Seq_GetResult16(0);
    return pulse;
}

/* [] END OF FILE */
