/* ========================================
 *
 * USC SAIL, 2017 MAY 11th
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "Data_Queue.h"

DATA_QUEUE pulse_raw_data;

/** \brief Reset the elements of DATA_QUEUE
* \param q DATA_QUEUE to initialize. It should be pointer.
* \param sizeOfQueue 
* \see DATA_QUEUE
* \see DATA_QUEUE_SIZE_MAX
* \return void
* 
* This method does unbelievably useful things.  
* And returns exceptionally useful results.
* Use it everyday with good health.
*/
void DataQueue_Init(DATA_QUEUE *q, uint8 sizeOfQueue){
    q->front = 0;
    q->rear = 0;
    q->size = sizeOfQueue;
    q->count = 0;
}


/** \brief Initialize the elements of DATA_QUEUE
* \see DATA_QUEUE
* \see DATA_QUEUE_SIZE_MAX
* \return If
* 
* This method does unbelievably useful things.  
* And returns exceptionally useful results.
* Use it everyday with good health.
*/
uint8 DataQueue_IsFull(DATA_QUEUE *q){
    if(q->count == q->size)
        return TRUE;
    return FALSE;
}

uint8 DataQueue_IsEmpty(DATA_QUEUE *q){
    if(q->count == 0)
        return TRUE;
    return FALSE;
}


//Add data to last of queue
void DataQueue_AddData(DATA_QUEUE *q, uint16* data){
    
    if(!DataQueue_IsFull(q)){
        uint8 i = 0;
        for (i = 0; i < DATA_PER_FRAME; i++){
            q->data[q->rear][i] = *data++;
        }
        
        q->rear = (q->rear + 1) % q->size;
        q->count++;
    }
}

//Remove a data from 
uint16* DataQueue_RemoveData(DATA_QUEUE * q){
    uint16 *data;
    if(!DataQueue_IsEmpty(q)){
        data = q->data[q->front];
        q->front = (q->front+1) % q->size;
        q->count--; 
    }
    
    return data;
}

uint16* DataQueue_GetData(DATA_QUEUE *q, uint8 index){
    uint16 actualIndex=0;
    uint16 *data;
    if(!DataQueue_IsEmpty(q)){
        actualIndex = (q->front+index) % q->size;
        data = q->data[actualIndex];
    }
    return data;
}

uint16* DataQueue_Peek(DATA_QUEUE *q){
    uint16 actualIndex=0;
    uint16 *data;
    if(!DataQueue_IsEmpty(q)){
        actualIndex = (q->rear)-1;
        data = q->data[actualIndex];
    }
    return data;
}

uint8 DataQueue_GetSize(DATA_QUEUE *q){
    return q->size;
}

uint8 DataQueue_GetCount(DATA_QUEUE *q){
    return q->count;
}

