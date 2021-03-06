#ifndef interruptHandlers_h
#define interruptHandlers_h

    #include "i2cFunctions.h"
    #include "locationMath.h"
    #include "project.h"
    #include "controls.h"
    #include <stdio.h>
    
    //Quadrature decoder interrupt handlers
    CY_ISR(QuadInt0);
    CY_ISR(QuadInt1);
    CY_ISR(QuadInt2);
    CY_ISR(QuadInt3);

    //Timer interrupt handlers
    CY_ISR(TimerInt);
    
    //Inclinometer decoder interrupt handlers
    CY_ISR(IncInt);
    
    //UART interrupt handlers
    CY_ISR(UartInt);

#endif