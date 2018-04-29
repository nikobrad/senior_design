#include "i2cFunctions.h"
#include "project.h"

extern MotorPositions motorPos[4];

//Quadrature decoder interrupt handlers
CY_ISR(QuadInt0);
CY_ISR(QuadInt1);
CY_ISR(QuadInt2);
CY_ISR(QuadInt3);

//Timer interrupt handlers

//UART interrupt handlers