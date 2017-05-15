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

#ifndef DATA_QUEUE_H
#define DATA_QUEUE_H

#include "project.h"
#include "main.h"    

#define DATA_QUEUE_TIME_STAMP_LOW  5
#define DATA_QUEUE_TIME_STAMP_HIGH 6
    
#define DATA_PER_FRAME  7
#define DATA_QUEUE_SIZE_MAX 60
    
typedef struct DataQueue{
    uint16 data[DATA_QUEUE_SIZE_MAX][DATA_PER_FRAME];
    uint8 front;
    uint8 rear;
    uint8 size;
    uint8 count;
}DATA_QUEUE;  

void DataQueue_Init(DATA_QUEUE *q, uint8 sizeOfQueue);

uint8 DataQueue_IsFull(DATA_QUEUE *q);
uint8 DataQueue_IsEmpty(DATA_QUEUE *q);
    
void DataQueue_AddData(DATA_QUEUE *q, uint16* data);
uint16* DataQueue_RemoveData(DATA_QUEUE * q);
uint16* DataQueue_GetData(DATA_QUEUE *q, uint8 index);
uint16* DataQueue_Peek(DATA_QUEUE *q);

uint8 DataQueue_GetSize(DATA_QUEUE *q);
uint8 DataQueue_GetCount(DATA_QUEUE *q);

extern DATA_QUEUE pulse_raw_data;

    
#endif
