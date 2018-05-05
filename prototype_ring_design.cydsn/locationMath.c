#include "locationMath.h"
#include "i2cFunctions.h"

void getMotor0()
{
    int tmp = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorDat[0].index * STEP_CONSTANT);
    motorDat[0].counter = tmp;
}
void getMotor1()
{
    int tmp = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorDat[1].index * STEP_CONSTANT);
    motorDat[1].counter = tmp;
}
void getMotor2()
{
    int tmp = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorDat[2].index * STEP_CONSTANT);
    motorDat[2].counter = tmp;
}
void getMotor3()
{
    int tmp = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorDat[3].index * STEP_CONSTANT);
    motorDat[3].counter = tmp;
}

void linearConv(uint8 MA) // milli-inche
{
    motorDat[MA].lineLength = (motorDat[MA].counter * STEP_SIZE * PI * SPOOL_DIAMETER) / 360; // milli-inches
}

void payloadCorners() // milli-inches
{
    PAYLOAD_CORNERS[0][0] = PAYLOAD_CENTER[0] + (PAYLOAD_SIDELEN * 1414 / 2);
    PAYLOAD_CORNERS[0][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[1][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[1][1] = PAYLOAD_CENTER[1] + (PAYLOAD_SIDELEN * 1414 / 2);
    
    PAYLOAD_CORNERS[2][0] = PAYLOAD_CENTER[0] - (PAYLOAD_SIDELEN * 1414 / 2);
    PAYLOAD_CORNERS[2][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[3][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[3][1] = PAYLOAD_CENTER[1] - (PAYLOAD_SIDELEN * 1414 / 2);
}

void wheresthepayload()
{
    
}