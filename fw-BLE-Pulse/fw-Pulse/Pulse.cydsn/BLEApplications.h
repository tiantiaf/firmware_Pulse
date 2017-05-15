/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
/********************************************************************************
* Contains all macros and function declaration used in the BLEApplications.c 
* file.
********************************************************************************/
#if !defined(BLEAPPLICATIONS_H)
#define BLEAPPLICATIONS_H
#include <project.h>
#include "Data_Queue.h"

#define ENABLE_LOW_POWER_MODE
    
#define MODE0   						(0)
#define MODE1						    (1)
#define MODE2						    (2)
#define MODE3					        (3)
#define MODE4					        (4)
    
    
#define SENSOR_HEADER       0
    
#define SENSOR_TIME_FIRST   1
#define SENSOR_TIME_SECOND  2
#define SENSOR_TIME_THIRD   3
#define SENSOR_TIME_FORTH   4

#define SENSOR_1_LOW        5
#define SENSOR_1_HIGH       6
#define SENSOR_2_LOW        7
#define SENSOR_2_HIGH       8
#define SENSOR_3_LOW        9
#define SENSOR_3_HIGH       10     
#define SENSOR_4_LOW        11
#define SENSOR_4_HIGH       12   
#define SENSOR_5_LOW        13
#define SENSOR_5_HIGH       14
    
#define SENSOR_FOOTER       15    
#define DATA_PER_PACKET     16
    
#define NUMBER_OF_SENSOR_PER_PACKET 5
    
/**************************Function Declarations*****************************/
void CustomEventHandler(uint32 event, void * eventParam);
void UpdateConnectionParam();
void UpdateSettings();
void UpdateDataBack(uint16* temp_data);
void HandleStatusLED(void);
void UpdateLEDCharacteristic(uint8* ledData, uint8 len);
void UpdateMotorCharacteristic(uint8* MotorData, uint8 len);
void BLE_SendStreamingData();
/****************************************************************************/


/* LED Blink rate values for different stages of BLE connection */
#ifdef ENABLE_LOW_POWER_MODE
#define	LED_ADV_BLINK_PERIOD_ON			5
#define LED_ADV_BLINK_PERIOD_OFF		20
#else
#define	LED_ADV_BLINK_PERIOD_ON			10000
#define LED_ADV_BLINK_PERIOD_OFF		15000
#endif


/****************************************************************************/

/* Minimum connection interval = CONN_PARAM_UPDATE_MIN_CONN_INTERVAL * 1.25 ms*/
#define CONN_PARAM_UPDATE_MIN_CONN_INTERVAL 50        	
/* Maximum connection interval = CONN_PARAM_UPDATE_MAX_CONN_INTERVAL * 1.25 ms */
#define CONN_PARAM_UPDATE_MAX_CONN_INTERVAL	52        	
/* Slave latency = Number of connection events */
#define CONN_PARAM_UPDATE_SLAVE_LATENCY		0          
/* Supervision timeout = CONN_PARAM_UPDATE_SUPRV_TIMEOUT * 10*/
#define CONN_PARAM_UPDATE_SUPRV_TIMEOUT		200   



/*****************************************************************************
* Extern variables
*****************************************************************************/
extern uint8 deviceConnected;
extern uint8 restartAdvertisement;
extern uint8 charNotificationEnabled;
extern uint8 sendDataEnabled;
    
    
#endif

