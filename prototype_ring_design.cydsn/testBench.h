#ifndef testBench_h
    #define testBench_h
    
    #include "i2cFunctions.h"
    #include "interruptHandlers.h"
    #include "locationMath.h"
    #include "project.h"
    #include <stdlib.h>
    
    #define ACCEPTABLE_ERROR 0.25 // inches
    
    void mainLoop();
    
#endif