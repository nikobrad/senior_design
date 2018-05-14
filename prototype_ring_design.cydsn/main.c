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
#include "testBench.h"
#include <stdlib.h>

#define DELAY 500

MotorData motorDat[4];
float MOUNT_POINTS[4][2] = {{(FRAME_DIAMETER/2.0),0},{0,(FRAME_DIAMETER/2.0)},{(-1*FRAME_DIAMETER/2.0),0},{0,(-1*FRAME_DIAMETER/2.0)}};
float PAYLOAD_CENTER[2];
float NEXT_PAYLOAD_GOAL[2];
float NEXT_PAYLOAD_SLICE[2];
uint8 calFlags[4];

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
    
    motorDat[0].addr = Motor0;
    motorDat[1].addr = Motor1;
    motorDat[2].addr = Motor2;
    motorDat[3].addr = Motor3;
    
    motorDat[0].calibrationSteps = CALIBRATION_0;
    motorDat[1].calibrationSteps = CALIBRATION_1;
    motorDat[2].calibrationSteps = CALIBRATION_2;
    motorDat[3].calibrationSteps = CALIBRATION_3;
    
    motorDat[0].index = 0;
    motorDat[1].index = 0;
    motorDat[2].index = 0;
    motorDat[3].index = 0;
    
    calFlags[0] = 0;
    calFlags[1] = 0;
    calFlags[2] = 0;
    calFlags[3] = 0;
    
    float* lineLengths = malloc(4*sizeof(*lineLengths)); // for use in payloadToLineLength in locationMath.{c,h}; declared extern for use elsewhere
    
    UART_UartPutString("Welcome to Senior Design\n\r");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    
    // start and enable master
    I2C_Start();
    I2C_Enable();
    LED_Write(0);
    LED_Write(1);
    // exit safe start
    motorSafeStartExit(motorDat[0].addr);
    motorSafeStartExit(motorDat[1].addr);
    motorSafeStartExit(motorDat[2].addr);
    motorSafeStartExit(motorDat[3].addr);
    LED_Write(0);
    LED_Write(1);
    LED_Write(0);
    //re-energize
    motorEnergize(motorDat[0].addr);
    motorEnergize(motorDat[1].addr);
    motorEnergize(motorDat[2].addr);
    motorEnergize(motorDat[3].addr);   
    
    mainLoop();
    /*
    int vel0 = 2500;
    int vel1 = 2500;
    int vel2 = -2500;
    int vel3 = -2500;

    motorSetSpeed(motorDat[0].addr,vel0);
    motorSetSpeed(motorDat[1].addr,vel1);
    motorSetSpeed(motorDat[2].addr,vel2);
    motorSetSpeed(motorDat[3].addr,vel3);
    
    CyDelay(5000);
    
    motorSetSpeed(motorDat[0].addr,0);
    motorSetSpeed(motorDat[1].addr,0);
    motorSetSpeed(motorDat[2].addr,0);
    motorSetSpeed(motorDat[3].addr,0);
    
    for(;;)
    {
        
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
    
        
    }
*/
    
    motorDeenergize(motorDat[0].addr);
    motorDeenergize(motorDat[1].addr);
    motorDeenergize(motorDat[2].addr);
    motorDeenergize(motorDat[3].addr); 
    
    free(lineLengths);
    
    return(0);
    
}

/* [] END OF FILE */