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
#include "locationMath.h"
#include "project.h"
#include <stdlib.h>

#define DELAY 500

MotorData motorDat[4];
int PAYLOAD_CENTER[2];
int PAYLOAD_CORNERS[4][2];

int main(void)
{
    
    
    CyGlobalIntDisable;
    QuadDec_0_Start();
    QuadDec_1_Start();
    QuadDec_2_Start();
    QuadDec_3_Start();
    UART_Start();
    QuadIsr_0_StartEx(QuadInt0);
    QuadIsr_1_StartEx(QuadInt1);
    QuadIsr_2_StartEx(QuadInt2);
    QuadIsr_3_StartEx(QuadInt3);
    //UartIsr_StartEx(UartInt);
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    motorDat[0].MA = Motor0;
    motorDat[1].MA = Motor1;
    motorDat[2].MA = Motor2;
    motorDat[3].MA = Motor3;
    
    motorDat[0].index = 0;
    motorDat[1].index = 0;
    motorDat[2].index = 0;
    motorDat[3].index = 0;
    
    UART_UartPutString("Welcome to Senior Design\n\r");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    // start and enable master
    I2C_Start();
    I2C_Enable();
    LED_Write(0);
    LED_Write(1);
    // exit safe start
    motorSafeStartExit(0);
    motorSafeStartExit(1);
    motorSafeStartExit(2);
    motorSafeStartExit(3);
    LED_Write(0);
    LED_Write(1);
    LED_Write(0);
    //re-energize
    motorEnergize(0);
    motorEnergize(1);
    motorEnergize(2);
    motorEnergize(3);    
    int vel0 = 2500;
    int vel1 = 2500;
    int vel2 = -2500;
    int vel3 = -2500;

    motorSetSpeed(0,vel0);
    motorSetSpeed(1,vel1);
    motorSetSpeed(2,vel2);
    motorSetSpeed(3,vel3);
    
    CyDelay(5000);
    
    motorSetSpeed(0,0);
    motorSetSpeed(1,0);
    motorSetSpeed(2,0);
    motorSetSpeed(3,0);
    
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
    
    motorDeenergize(0);
    motorDeenergize(1);
    motorDeenergize(2);
    motorDeenergize(3); 
    
    return(0);
    
}

/* [] END OF FILE */