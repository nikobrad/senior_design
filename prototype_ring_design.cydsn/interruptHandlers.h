#include "i2cFunctions.h"
#include "project.h"
#include <stdio.h>

//Quadrature decoder interrupt handlers
CY_ISR(QuadInt0);
CY_ISR(QuadInt1);
CY_ISR(QuadInt2);
CY_ISR(QuadInt3);

//Timer interrupt handlers

//UART interrupt handlers
CY_ISR(UartInt);