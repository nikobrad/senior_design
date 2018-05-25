#include "controls.h"

void demoA()
{
    float coordX[16];
    float coordY[16];
    int i;
    for(i = 0;i < 16;i = i + 1)
    {
        coordX[i] = USABLE_RADIUS * cos((PI * i) / 8);
        coordY[i] = USABLE_RADIUS * sin((PI * i) / 8);
    }
    while(1)
    {
        while(!executeFlag);
        executeFlag = 0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = coordX[(int)(goalUpdateTimer / 30)];
        NEXT_PAYLOAD_GOAL[1] = coordY[(int)(goalUpdateTimer / 30)];
        if(goalUpdateTimer >= 480)
            goalUpdateTimer = 0;
    } 
}

void demoB()
{
   float coordX[16] = {3,-3,3,-3,-3,-2,-3,-1,-3,0,-3,1,-3,2,-3,3};
   float coordY[16] = {3,3,-3,-3,-2,-3,-1,-3,0,-3,1,-3,2,-3,3,-3};
   while(1)
    {
        while(!executeFlag);
        executeFlag = 0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = coordX[(int)(goalUpdateTimer / 150)];
        NEXT_PAYLOAD_GOAL[1] = coordY[(int)(goalUpdateTimer / 150)];
        if(goalUpdateTimer >= 2400)
            goalUpdateTimer = 0;
    } 
}

void demoLinear()
{
    nextPosition = 20;
    while(1)
    {
        while(!executeFlag);
        executeFlag = 0;
        controlAlgorithm();
    }
}

void controlAlgorithm()
{
    IncIsr_Disable();
    char prt[64];
    sprintf(prt,"Payload: %d,%d\t\tPayload goal: %d,%d\n\r",(int)(PAYLOAD_CENTER[0]*1000),(int)(PAYLOAD_CENTER[1]*1000),(int)(NEXT_PAYLOAD_GOAL[0]*1000),(int)(NEXT_PAYLOAD_GOAL[1]*1000));
    //UART_UartPutString(prt);
    
    updateEncoderCount();
    lineLengthToPayloadCenter();
    findNextPayloadCenter(); // Commented out so we can test working code in chassis before implementing physics
    float errorDist = pointDistance(NEXT_PAYLOAD_GOAL,PAYLOAD_CENTER);
    
    int i;
    if(errorDist > ACCEPTABLE_ERROR)
    {
        
        findNextPayloadSlice();
        payloadToLineLength(NEXT_PAYLOAD_SLICE);
        for(i = 0;i < 4;i = i + 1)
        {
            motorDat[i].nextLineLength = lineLengths[i];
        }
        lToDeltaL();
        deltaLToSpeed();
        for(i = 0;i < 4;i = i + 1)
        {
            motorSetSpeed(motorDat[i].addr,(motorDat[i].stepSpeed)); 
        }
        
    }
    else
    {
        for(i = 0;i < 4;i = i + 1)
            motorSetSpeed(motorDat[i].addr,0);
    }
    IncIsr_Enable();
}

void mainLoop()
{
    PAYLOAD_CENTER[0] = 0.0;
    PAYLOAD_CENTER[1] = 0.0;
    NEXT_PAYLOAD_GOAL[0] = 1.0;
    NEXT_PAYLOAD_GOAL[1] = 3.0;
    int i;
    
    payloadToLineLength(PAYLOAD_CENTER);
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].lineLength = lineLengths[i];
    }
    
    controlAlgorithm();
    for(i = 0;i < 3;i = i + 1)
    {
        NEXT_PAYLOAD_GOAL[0] = 3.0;
        NEXT_PAYLOAD_GOAL[1] = -1.0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = 1.0;
        NEXT_PAYLOAD_GOAL[1] = -3.0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = -3.0;
        NEXT_PAYLOAD_GOAL[1] = 1.0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = 1.0;
        NEXT_PAYLOAD_GOAL[1] = 3.0;
        controlAlgorithm();
    }
    
}

void testGetLineLengths()
{
    UART_UartPutString("Got into the function\n\r");
    char prt[32];
    int i;
    updateEncoderCount();
    int tmp = (int)(1000 * motorDat[0].lineLength);
    sprintf(prt,"Motor 0 line length: %d milliinches\n\r",tmp);
    UART_UartPutString(prt);
    motorSetSpeed(Motor0,2000);
    for(i = 0;i < 5;i = i + 1)
    {
        CyDelay(1000);
        updateEncoderCount();
        tmp = (int)(1000 * motorDat[0].lineLength);
        sprintf(prt,"Motor 0 line length: %d milliinches\n\r",tmp);
        UART_UartPutString(prt);
    }
    motorSetSpeed(Motor0,-2000);
    for(i = 0;i < 10;i = i + 1)
    {
        CyDelay(1000);
        updateEncoderCount();
        tmp = (int)(1000 * motorDat[0].lineLength);
        sprintf(prt,"Motor 0 line length: %d milliinches\n\r",tmp);
        UART_UartPutString(prt);
    }
    motorSetSpeed(Motor0,0);
    return;
}