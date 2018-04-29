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

#include "i2cFunctions.h"
#include "interruptHandlers.h"
#include "project.h"
#include <stdlib.h>

#define DELAY 500

MotorPositions motorPos[4];

int main(void)
{
    CyGlobalIntDisable;
    QuadDec_0_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();
    QuadDec_3_Start();
    QuadIsr_0_StartEx(QuadInt0);
    QuadIsr_1_StartEx(QuadInt1);
    QuadIsr_2_StartEx(QuadInt2);
    QuadIsr_3_StartEx(QuadInt3);
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    motorPos[0].index = 0;
    motorPos[1].index = 0;
    motorPos[2].index = 0;
    motorPos[3].index = 0;

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    // start and enable master
    I2C_Start();
    I2C_Enable();
    LED_Write(0);
    LED_Write(1);
    // exit safe start
    motorSafeStartExit(Motor0);
    motorSafeStartExit(Motor1);
    motorSafeStartExit(Motor2);
    motorSafeStartExit(Motor3);
    LED_Write(0);
    LED_Write(1);
    LED_Write(0);
    //re-energize
    motorEnergize(Motor0);
    motorEnergize(Motor1);
    motorEnergize(Motor2);
    motorEnergize(Motor3);    
    int vel0 = 2500;
    int vel1 = 2500;
    int vel2 = -2500;
    int vel3 = -2500;

    motorSetSpeed(Motor0,vel0);
    motorSetSpeed(Motor1,vel1);
    motorSetSpeed(Motor2,vel2);
    motorSetSpeed(Motor3,vel3);
    
    for(;;)
    {
        /*
        motorSetSpeed(Motor0,50);
        motorSetSpeed(Motor2,-50);
        
        LED_Write(0);
        CyDelay(DELAY);
       
        motorSetSpeed(Motor0,0);
        motorSetSpeed(Motor2,0);
        
        LED_Write(1);
        CyDelay(DELAY);
        
        motorSetSpeed(Motor0,-50);
        motorSetSpeed(Motor2,50);
        
        LED_Write(0);
        CyDelay(DELAY);
        
        motorSetSpeed(Motor0,0);
        motorSetSpeed(Motor2,0);
        
        LED_Write(1);
        CyDelay(DELAY);
    
        */
    }
    
    return(0);
    
}

/* [] END OF FILE */