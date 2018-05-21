#include "i2cFunctions.h"
#include "interruptHandlers.h"
#include "locationMath.h"
#include "project.h"
#include "testBench.h"
#include <stdlib.h>

//Extern variables:
float MOUNT_POINTS[4][2] = {{FRAME_RADIUS,0},{0,FRAME_RADIUS},{(-1)*FRAME_RADIUS,0},{0,(-1)*FRAME_RADIUS}}; // Effectively a constant
MotorData motorDat[4]; // Stores motor state data
float lineLengths[4]; // for use in payloadToLineLength
float PAYLOAD_CENTER[2]; // Current payload location, Cartesian coordinates
float NEXT_PAYLOAD_GOAL[2]; // Point for payload to approach, Cartesian coordinates
float NEXT_PAYLOAD_SLICE[2]; // Immediate destination for payload

uint32 goalUpdateTimer = 0; // Counts timer interrupts, for use in static tests
uint8 executeFlag = 0; // High if control algorithm should execute; otherwise, low

uint32 rotationTimer = 0; // Tracks time between inclinometer interrupt triggers
int rotationTimes[2]; // Stores previous two delays between new inclinometer readings
float rotation; // Tracks current incline of chassis
float velocity = 0; // Tracks current velocity of chassis
float acceleration = 0; // Tracks current acceleration of chassis based on current and previous velocity
float nextVelocity = 0; // Desired velocity of chassis

void init();

int main(void)
{
    CyGlobalIntDisable;
    while(StartButton_Read()); // Wait for someone to press the button
    init(); // Run initialization code
    CyGlobalIntEnable;
    
    calibrateEncoders();
    
    TIMER_Enable();
    TIMERISR_Enable();
    
    //Pick a control function:
    
    //demoA();
    //demoB();

    int i;
    for(i = 0;i < 4;i = i + 1) // Deenergize motors
        motorDeenergize(motorDat[i].addr);
    
    return(0);
}

void init()
{
    QuadDec_0_Start(); // Initialize the quadrature decoders and interrupts
    QuadDec_1_Start();
    QuadDec_2_Start();
    QuadDec_3_Start();
    QuadIsr_0_StartEx(QuadInt0);
    QuadIsr_1_StartEx(QuadInt1);
    QuadIsr_2_StartEx(QuadInt2);
    QuadIsr_3_StartEx(QuadInt3);
    TIMER_Start(); // Initialize the timer and interrupt
    TIMERISR_StartEx(TimerInt);
    TIMERISR_Disable();
    IncIsr_StartEx(IncInt); // Initialize the inclinometer
    I2C_Start(); // Initialize the I2C master
    I2C_Enable();
    UART_Start(); // Initialize the UART
    
    motorDat[0].addr = Motor0;
    motorDat[1].addr = Motor1;
    motorDat[2].addr = Motor2;
    motorDat[3].addr = Motor3;
    
    rotationTimes[0] = 0;
    rotationTimes[1] = 0;
    
    int i;
    for(i = 0;i < 4;i = i + 1) // Set initial conditions for motors
    {
        motorDat[i].calibrationSteps = 0;
        motorDat[i].index = 0;
        lineLengths[i] = 0.0;
        motorCommand(motorDat[i].addr,HaltAndHold,0);
    }
    
    for(i = 0;i < 4;i = i + 1) // Exit safe start
        motorSafeStartExit(motorDat[i].addr);
        
    for(i = 0;i < 4;i = i + 1) // Energize motors
        motorEnergize(motorDat[0].addr);
}

/* [] END OF FILE */