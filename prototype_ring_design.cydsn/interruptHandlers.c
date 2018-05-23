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
}

// Inclinometer decoder interrupt handlers

CY_ISR(IncInt)
{
    IncIsr_Disable();
    
    IncIsr_ClearPending();
    uint8 intSrc = IncDec_ClearInterrupt();
    int i;
    for(i = 0;i < 8;i = i + 1)
    {
        if(intSrc & (0x01 << i))
        {
            angle = ROTATION_SCALAR * i;
            if(i == (prevAngle + 1) % 8) // Figure out which way it's turning; 
                position = position + ((FRAME_DIAMETER * PI) / 8);
            else if((i + 1) % 8 == prevAngle) // If it's not either of these, it skipped at least one segment and we can't be sure anymore
                position = position + ((FRAME_DIAMETER * PI) / 8); // Or it's just bouncy and should be ignored
            prevAngle = i;
        }
    }
    
    char prt[32];
    sprintf(prt,"Rotation: %d miliradians\n\r",(int)(angle * 1000));
    UART_UartPutString(prt);
    IncIsr_Enable();
}

//UART interrupt handlers

CY_ISR(UartInt)
{
    UartIsr_ClearPending();
    UART_ClearRxInterruptSource(UART_GetRxInterruptSource());
}