#include "interruptHandlers.h"
#include "project.h"

extern int indices[4];
extern int motorRotations[4];

//Quadrature decoder interrupt handlers

CY_ISR(QuadInt0)
{
    int tmp = QuadDec_0_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        indices[0] = indices[0] + 1;
    else if(tmp < 0x8000)
        indices[0] = indices[0] - 1;
    QuadDec_0_ClearInterrupt(QuadDec_0_GetInterruptSource());
}

CY_ISR(QuadInt1)
{
    int tmp = QuadDec_1_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        indices[1] = indices[1] + 1;
    else if(tmp < 0x8000)
        indices[1] = indices[1] - 1;
    QuadDec_1_ClearInterrupt(QuadDec_1_GetInterruptSource());
}

CY_ISR(QuadInt2)
{
    int tmp = QuadDec_2_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        indices[2] = indices[2] + 1;
    else if(tmp < 0x8000)
        indices[2] = indices[2] - 1;
    QuadDec_2_ClearInterrupt(QuadDec_2_GetInterruptSource());
}

CY_ISR(QuadInt3)
{
    int tmp = QuadDec_3_ReadCapture();
    if(tmp > 0x8000)    //Change index counter
        indices[3] = indices[3] + 1;
    else if(tmp < 0x8000)
        indices[3] = indices[3] - 1;
    QuadDec_3_ClearInterrupt(QuadDec_3_GetInterruptSource());
}

//Timer interrupt handlers