/* ========================================
 *
 * SAIL, USC, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include <main.h>
#include "Pulse_Timestamp.h"
#include "Pulse_Init.h"

uint16 temp_data[DATA_PER_FRAME];

CY_ISR(MS_ISR) {
    
    if(charNotificationEnabled == TRUE) {
        time_stamp++;
        if( (time_stamp % 20) == 0) {
        
            uint8 index = (time_stamp % 100) / 20;
            temp_data[index] = ReadPulseData();
            
            /* Send 5 Sensor Data Out Every 100ms with Timestamp */
            if(index == 4) {
                
                temp_data[DATA_QUEUE_TIME_STAMP_LOW]   = (time_stamp & 0xFFFF);
                temp_data[DATA_QUEUE_TIME_STAMP_HIGH]  = ( (time_stamp >> 16) & 0xFFFF);
                UpdateDataBack(temp_data);
                
                sendDataEnabled = TRUE;
                
                Reset_Temp_Data();
            }
        
        }
        
    }
    
    /*
    if( (time_stamp % 20) == 0) {
        
        uint8 index = (time_stamp % 100) / 20;
        temp_data[index] = ReadPulseData();
        
        if( ( (time_stamp % 100) / 20 ) == 4 ) {
            if(DataQueue_IsFull(&pulse_raw_data) ){
                DataQueue_RemoveData(&pulse_raw_data);
            }
            temp_data[TIME_STAMP_LOW]   = (time_stamp & 0xFFFF);
            temp_data[TIME_STAMP_HIGH]  = ( (time_stamp >> 16) & 0xFFFF);
            
            DataQueue_AddData(&pulse_raw_data, temp_data);
            
            Reset_Temp_Data();
        }
        
    }*/
}

inline void Reset_Temp_Data() {
    uint8 i = 0;
    for (i = 0; i < DATA_PER_FRAME; i++) {
        temp_data[i] = 0;
    }
}

/* [] END OF FILE */
