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

#include <main.h>
#include "BLEApplications.h"


CYBLE_CONN_HANDLE_T  connectionHandle;

CYBLE_GATT_HANDLE_VALUE_PAIR_T      setHandle;
CYBLE_GATTS_HANDLE_VALUE_NTF_T      pulseHandle;

uint8 deviceConnected           = FALSE;
uint8 ledUpdateEnabled          = FALSE;
uint8 charNotificationEnabled   = FALSE;
uint8 restartAdvertisement      = FALSE;
uint8 sendDataEnabled           = FALSE;

uint32 negotiatedMtu            = 23;

uint8 stoneMotorUpdateEnable    = FALSE;

uint32 frameNumber = 0;

static uint8 isConnectionUpdateRequested = TRUE;
static CYBLE_GAP_CONN_UPDATE_PARAM_T ConnectionParam =
{
	CONN_PARAM_UPDATE_MIN_CONN_INTERVAL,
	CONN_PARAM_UPDATE_MAX_CONN_INTERVAL,
	CONN_PARAM_UPDATE_SLAVE_LATENCY,
	CONN_PARAM_UPDATE_SUPRV_TIMEOUT
};

uint8 busyStatus = 0;
uint8 data_to_send[DATA_PER_PACKET];

void CustomEventHandler(uint32 event, void * eventParam)
{
    
    /* Local variable to store the data received as part of the Write request
	* events */
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch (event)
	{
        case CYBLE_EVT_STACK_ON:
    		restartAdvertisement = TRUE;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;

    	case CYBLE_EVT_TIMEOUT:
            restartAdvertisement = TRUE;
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    		break;
       
        /**********************************************************
		*                       GAP Events
		***********************************************************/
    	case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:

    		/* If the current BLE state is Disconnected, then the Advertisement
    		* Start Stop event implies that advertisement has stopped */
    		if (CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    		{
    			/* Set restartAdvertisement flag to allow calling Advertisement
    			* API from main function */
    			restartAdvertisement = TRUE;
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);   
    		}
    		break;

    	case CYBLE_EVT_GAP_DEVICE_CONNECTED:
    		/* This event is received when device is connected over GAP layer */
            if (CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    		{ 
                negotiatedMtu            = 23;
    		}
    		break;

    	case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    		restartAdvertisement = TRUE;
    		break;
            
        /**********************************************************
		*                       GATT Events
		***********************************************************/
        case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
    		negotiatedMtu = (((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu < CYBLE_GATT_MTU) ?
    			((CYBLE_GATT_XCHG_MTU_PARAM_T *)eventParam)->mtu : CYBLE_GATT_MTU;
    		break;    
            
    	case CYBLE_EVT_GATT_CONNECT_IND:
    		connectionHandle = *(CYBLE_CONN_HANDLE_T  *)eventParam;
    		deviceConnected = TRUE;
    		break;

    	case CYBLE_EVT_GATT_DISCONNECT_IND:
    		deviceConnected = FALSE;
    		isConnectionUpdateRequested = TRUE;
    		break;

    	case CYBLE_EVT_GATTS_WRITE_REQ:
    		wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            
            if (CYBLE_BT_PULSE_PULSE_DATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE == wrReqParam->handleValPair.attrHandle)
    		{
    			charNotificationEnabled = wrReqParam->handleValPair.value.val[0];
    			CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, FALSE, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    		}
            
    		CyBle_GattsWriteRsp(connectionHandle);
    		break;
            
        case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            break;
           

    	case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
    		isConnectionUpdateRequested = FALSE;
    		break;

    	case CYBLE_EVT_STACK_BUSY_STATUS:
    		busyStatus = *(uint8*)eventParam;
    		break;

    	default:

    		break;
              
    }
        
}

void UpdateSettings(void)
{
    if (deviceConnected && isConnectionUpdateRequested)
	{
		isConnectionUpdateRequested = FALSE;

		CyBle_L2capLeConnectionParamUpdateRequest(connectionHandle.bdHandle, &ConnectionParam);
	}

}

void UpdateMotorCharacteristic(uint8* motorData, uint8 len)
{
    setHandle.attrHandle = CYBLE_BT_PULSE_CTR_MOTOR_CHAR_HANDLE;
	setHandle.value.val = motorData;
	setHandle.value.len = len;

	CyBle_GattsWriteAttributeValue(&setHandle, FALSE, &connectionHandle, FALSE);
	CyBle_ProcessEvents();
    
}


void UpdateDataBack(uint16* temp_data)
{   
    uint8 i = 0;
    
    data_to_send[SENSOR_HEADER] = 0xFE;
    
    data_to_send[SENSOR_TIME_FIRST]  = temp_data[DATA_QUEUE_TIME_STAMP_LOW] & 0xFF;
    data_to_send[SENSOR_TIME_SECOND] = (temp_data[DATA_QUEUE_TIME_STAMP_LOW] >> 8) & 0xFF;
    data_to_send[SENSOR_TIME_THIRD]  = temp_data[DATA_QUEUE_TIME_STAMP_HIGH] & 0xFF;
    data_to_send[SENSOR_TIME_FORTH]  = (temp_data[DATA_QUEUE_TIME_STAMP_HIGH] >> 8) & 0xFF;
    
    
    for (i = 0; i < NUMBER_OF_SENSOR_PER_PACKET; i++) {
        data_to_send[SENSOR_1_LOW  + i * 2] = temp_data[i] & 0xFF;
        data_to_send[SENSOR_1_HIGH + i * 2] = (temp_data[i] >> 8) & 0xFF;
    }
    
    data_to_send[SENSOR_FOOTER] = 0xFE;
    
}

void BLE_SendStreamingData(){
    pulseHandle.attrHandle = CYBLE_BT_PULSE_PULSE_DATA_CHAR_HANDLE;
    pulseHandle.value.val = data_to_send;
    pulseHandle.value.len = DATA_PER_PACKET;
    CyBle_GattsNotification(cyBle_connHandle, &pulseHandle);
    
    CyBle_ProcessEvents();
}

void UpdateConnectionParam()
{
	if (deviceConnected && isConnectionUpdateRequested)
	{
		isConnectionUpdateRequested = FALSE;
		CyBle_L2capLeConnectionParamUpdateRequest(connectionHandle.bdHandle, &ConnectionParam);
	}
	if (charNotificationEnabled == TRUE)
	{
		BLE_SendStreamingData();
        sendDataEnabled = FALSE;
	}
	CyBle_GattsWriteRsp(connectionHandle);
}










