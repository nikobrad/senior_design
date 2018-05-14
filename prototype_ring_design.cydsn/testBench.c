#include "testBench.h"

void controlAlgorithm()
{
    char tmp[32];
    sprintf(tmp,"Payload goal: %.2f,%.2f.\n\r",NEXT_PAYLOAD_GOAL[0],NEXT_PAYLOAD_GOAL[1]);
    UART_UartPutString(tmp);
    float errorDist = pointDistance(NEXT_PAYLOAD_GOAL,PAYLOAD_CENTER);
    
    int i;
    while(errorDist > ACCEPTABLE_ERROR)
    {
        findNextPayloadSlice();
        payloadToLineLength(NEXT_PAYLOAD_SLICE,lineLengths);
        for(i = 0;i < 4;i = i + 1)
        {
            motorDat[i].nextLineLength = lineLengths[i];
        }
        lToDeltaL();
        deltaLToSpeed();
        for(i = 0;i < 4;i = i + 1)
        {
            motorSetSpeed(motorDat[i].addr,motorDat[i].stepSpeed);
        }
        CyDelay(20);
        updateEncoderCount();
        lineLengthToPayloadCenter();
        errorDist = pointDistance(NEXT_PAYLOAD_GOAL,PAYLOAD_CENTER);
    }
    UART_UartPutString("Goal reached.\n\r");
}

void mainLoop()
{
    PAYLOAD_CENTER[0] = 0.0;
    PAYLOAD_CENTER[1] = 0.0;
    NEXT_PAYLOAD_GOAL[0] = 0.0;
    NEXT_PAYLOAD_GOAL[1] = 5.0;
    int i;
    
    payloadToLineLength(PAYLOAD_CENTER,lineLengths);
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].lineLength = lineLengths[i];
    }
    
    controlAlgorithm();
    NEXT_PAYLOAD_GOAL[0] = 3.0;
    NEXT_PAYLOAD_GOAL[1] = -3.0;
    controlAlgorithm();
    NEXT_PAYLOAD_GOAL[0] = -5.0;
    NEXT_PAYLOAD_GOAL[1] = 0.0;
    controlAlgorithm();
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