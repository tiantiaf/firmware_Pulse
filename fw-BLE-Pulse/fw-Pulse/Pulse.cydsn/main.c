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

#include <main.h>
#include "BLEApplications.h"
#include "Pulse_Init.h"

uint32 time_stamp = 0;
uint32 last_time = 0;



int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    InitializeSystem();
    
    for(;;)
    {
        /* Place your application code here. */
        /*Process event callback to handle BLE events. The events generated and 
		* used for this application are inside the 'CustomEventHandler' routine*/
        CyBle_ProcessEvents();
		
		if(TRUE == deviceConnected)
		{
            
            if (sendDataEnabled){
                if (CyBle_GattGetBusStatus() == CYBLE_STACK_STATE_FREE)
    			{
    				UpdateConnectionParam();
    			}
            }            
          
		}
        
        if (restartAdvertisement)
		{
			/* Reset 'restartAdvertisement' flag*/
			restartAdvertisement = FALSE;

			/* Start Advertisement and enter Discoverable mode*/
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);

			/* Process BLE Events, including the above Advertisement restart */
			CyBle_ProcessEvents();
		}
    }
}


/* [] END OF FILE */
