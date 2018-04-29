#include "i2cFunctions.h"
#include "interruptHandlers.h"
#include "project.h"
#include <stdio.h>

//Quadrature decoder interrupt handlers

CY_ISR(QuadInt0)
{
    int tmp = QuadDec_0_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorPos[0].index = motorPos[0].index + 1;
    else if(tmp < 0x8000)
        motorPos[0].index = motorPos[0].index - 1;
    QuadDec_0_ClearInterrupt(QuadDec_0_GetInterruptSource());
    char prt[24];
    sprintf(prt,"Motor 0 Index %d\n\r",motorPos[0].index);
    UART_UartPutString(prt);
}

CY_ISR(QuadInt1)
{
    int tmp = QuadDec_1_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorPos[1].index = motorPos[1].index + 1;
    else if(tmp < 0x8000)
        motorPos[1].index = motorPos[1].index - 1;
    QuadDec_1_ClearInterrupt(QuadDec_1_GetInterruptSource());
    char prt[24];
    sprintf(prt,"Motor 1 Index %d\n\r",motorPos[1].index);
    UART_UartPutString(prt);
}

CY_ISR(QuadInt2)
{
    int tmp = QuadDec_2_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorPos[2].index = motorPos[2].index + 1;
    else if(tmp < 0x8000)
        motorPos[2].index = motorPos[2].index;
    QuadDec_2_ClearInterrupt(QuadDec_2_GetInterruptSource());
    char prt[24];
    sprintf(prt,"Motor 2 Index %d\n\r",motorPos[2].index);
    UART_UartPutString(prt);
}

CY_ISR(QuadInt3)
{
    int tmp = QuadDec_3_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        motorPos[3].index = motorPos[3].index + 1;
    else if(tmp < 0x8000)
        motorPos[3].index = motorPos[3].index - 1;
    QuadDec_3_ClearInterrupt(QuadDec_3_GetInterruptSource());
    char prt[24];
    sprintf(prt,"Motor 3 Index %d\n\r",motorPos[3].index);
    UART_UartPutString(prt);
}

//Timer interrupt handlers

//UART interrupt handlers

CY_ISR(UartInt)
{
    UartIsr_ClearPending();
    UART_ClearRxInterruptSource(UART_GetRxInterruptSource());
}