#include "testBench.h"

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
        while(!time);
        time = 0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = coordX[(int)(timerCount / 30)];
        NEXT_PAYLOAD_GOAL[1] = coordY[(int)(timerCount / 30)];
        if(timerCount >= 480)
            timerCount = 0;
    } 
}

void demoB()
{
   float coordX[16] = {3,-3,3,-3,-3,-2,-3,-1,-3,0,-3,1,-3,2,-3,3};
   float coordY[16] = {3,3,-3,-3,-2,-3,-1,-3,0,-3,1,-3,2,-3,3,-3};
   while(1)
    {
        while(!time);
        time = 0;
        controlAlgorithm();
        NEXT_PAYLOAD_GOAL[0] = coordX[(int)(timerCount / 150)];
        NEXT_PAYLOAD_GOAL[1] = coordY[(int)(timerCount / 150)];
        if(timerCount >= 2400)
            timerCount = 0;
    } 
}

void controlAlgorithm()
{
    TEST_MEAS_Write(0);
    //char tmp[64];
    //sprintf(tmp,"Payload: %d,%d\n\rPayload goal: %d,%d\n\r",(int)(PAYLOAD_CENTER[0]*1000),(int)(PAYLOAD_CENTER[1]*1000),(int)(NEXT_PAYLOAD_GOAL[0]*1000),(int)(NEXT_PAYLOAD_GOAL[1]*1000));
    //UART_UartPutString(tmp);
    updateEncoderCount();
    lineLengthToPayloadCenter();
    float errorDist = pointDistance(NEXT_PAYLOAD_GOAL,PAYLOAD_CENTER);
    
    int i;
    if(errorDist > ACCEPTABLE_ERROR)
    {
        
        //sprintf(tmp,"Error: %d\n\r",(int)(errorDist*1000));
        //UART_UartPutString(tmp);
        //sprintf(tmp,"Motor 3 speed: %d\n\r",motorDat[3].stepSpeed);
        //UART_UartPutString(tmp);
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
        //sprintf(tmp,"Speed: M0:%d\t\tM1:%d\t\tM2:%d\t\tM3:%d\n\r",motorDat[0].stepSpeed,motorDat[1].stepSpeed,motorDat[2].stepSpeed,motorDat[3].stepSpeed);
        //UART_UartPutString(tmp);
        //updateEncoderCount();
        //lineLengthToPayloadCenter();
        findNextPayloadCenter();
        //sprintf(tmp,"Payload Center: (%d,%d)\n\r", (int)(PAYLOAD_CENTER[0] * 100000),(int)(PAYLOAD_CENTER[1] * 100000));
        //UART_UartPutString(tmp);
        
    }
    else
    {
        for(i = 0;i < 4;i = i + 1)
            motorSetSpeed(motorDat[i].addr,0);
    }
    //UART_UartPutString("Goal reached.\n\r");
    TEST_MEAS_Write(1);
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