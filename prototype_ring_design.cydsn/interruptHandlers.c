#include "interruptHandlers.h"

//Quadrature decoder interrupt handlers

CY_ISR(QuadInt0)
{
    QuadIsr_0_ClearPending();
    QuadDec_0_ClearInterrupt(QuadDec_0_GetInterruptSource());
    int tmp = QuadDec_0_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorDat[0].index = motorDat[0].index + 1;
    else if(tmp < 0x8000)
        motorDat[0].index = motorDat[0].index - 1;
    QuadDec_0_ClearInterrupt(QuadDec_0_GetInterruptSource());
    //char prt[24];
    //sprintf(prt,"Motor 0 Index %d\n\r",motorDat[0].index);
    //UART_UartPutString(prt);
}

CY_ISR(QuadInt1)
{
    QuadIsr_1_ClearPending();
    QuadDec_1_ClearInterrupt(QuadDec_1_GetInterruptSource());
    int tmp = QuadDec_1_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorDat[1].index = motorDat[1].index + 1;
    else if(tmp < 0x8000)
        motorDat[1].index = motorDat[1].index - 1;
    QuadDec_1_ClearInterrupt(QuadDec_1_GetInterruptSource());
    //char prt[24];
    //sprintf(prt,"Motor 1 Index %d\n\r",motorDat[1].index);
    //UART_UartPutString(prt);
}

CY_ISR(QuadInt2)
{
    QuadIsr_2_ClearPending();
    QuadDec_2_ClearInterrupt(QuadDec_2_GetInterruptSource());
    int tmp = QuadDec_2_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorDat[2].index = motorDat[2].index + 1;
    else if(tmp < 0x8000)
        motorDat[2].index = motorDat[2].index - 1;
    QuadDec_2_ClearInterrupt(QuadDec_2_GetInterruptSource());
    //char prt[24];
    //sprintf(prt,"Motor 2 Index %d\n\r",motorDat[2].index);
    //UART_UartPutString(prt);
}

CY_ISR(QuadInt3)
{
    QuadIsr_3_ClearPending();
    QuadDec_3_ClearInterrupt(QuadDec_3_GetInterruptSource());
    int tmp = QuadDec_3_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorDat[3].index = motorDat[3].index + 1;
    else if(tmp < 0x8000)
        motorDat[3].index = motorDat[3].index - 1;
    QuadDec_3_ClearInterrupt(QuadDec_3_GetInterruptSource());
    //char prt[24];
    //sprintf(prt,"Motor 3 Index %d\n\r",motorDat[3].index);
    //UART_UartPutString(prt);
}

//Timer interrupt handlers

CY_ISR(TimerInt)
{
    TIMER_ClearInterrupt(TIMER_GetInterruptSource());
    TIMERISR_ClearPending();
    executeFlag = 1;
    goalUpdateTimer = goalUpdateTimer + 1;
    rotationTimer = rotationTimer + 1;
    if(rotationTimer > MAX_ROTATION_TIME) // Set velocity to 0 if rotation hasn't changed in over 2 seconds
    {
        velocity = 0;
        rotationTimer = 0; // Avoid ruining results if chassis starts moving again
    }
}

// Inclinometer decoder interrupt handlers

CY_ISR(IncInt)
{
    IncDec_ClearInterrupt(); // Get rid of interrupt
    IncIsr_ClearPending();
    
    rotationTimes[1] = rotationTimes[0]; // Shift old time values out; update with new value
    timerRegisters[1] = timerRegisters[0];
    timerRegisters[0] = TIMER_ReadCounter();
    rotationTimes[0] = timerRegisters[0] + (rotationTimer * 10000) - timerRegisters[1];
    rotationTimer = 0;
    
    int tmp = IncDec_Read();
    if(tmp == (int)(rotation / ROTATION_SCALAR)) // Accidentally retriggered; ignore interrupt
        return;
    
    char prt[16]; // Print value; for testing, delete later
    sprintf(prt,"%d\n\r",tmp);
    UART_UartPutString(prt);

    rotation = (float)tmp * ROTATION_SCALAR; // Get that sweet sweet value
    
    // Averaged velocity between two previous readings
    velocity = (ROTATION_SCALAR * (float)CLOCK_SECONDS_CONVERSION) / ((float)(rotationTimes[0] + rotationTimes[1]) * PI);
}

//UART interrupt handlers

CY_ISR(UartInt)
{
    UartIsr_ClearPending();
    UART_ClearRxInterruptSource(UART_GetRxInterruptSource());
}