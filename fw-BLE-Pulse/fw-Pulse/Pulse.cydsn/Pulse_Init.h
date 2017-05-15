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

#if !defined(PULSE_INIT_H)
#define PULSE_INIT_H

#include "main.h"

#define MOTOR_ON		0x01
#define MOTOR_OFF       0x00
    
void InitializeSystem(void);
void StopTimer(void);
uint16 ReadPulseData();

#endif

/* [] END OF FILE */
