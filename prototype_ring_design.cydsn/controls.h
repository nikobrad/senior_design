#ifndef controls_h
#define controls_h
    
    #include "i2cFunctions.h"
    #include "interruptHandlers.h"
    #include "locationMath.h"
    #include "project.h"
    #include <stdlib.h>
    
    void controlAlgorithm();
    void mainLoop();
    void testGetLineLengths();
    
    void demoA();
    void demoB();
    
#endif