#include "locationMath.h"

void getMotor0()
{
    int tmp = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorPos[0].index * STEP_CONSTANT);
    motorPos[0].counter = tmp;
}
void getMotor1()
{
    int tmp = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorPos[1].index * STEP_CONSTANT);
    motorPos[1].counter = tmp;
}
void getMotor2()
{
    int tmp = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorPos[2].index * STEP_CONSTANT);
    motorPos[2].counter = tmp;
}
void getMotor3()
{
    int tmp = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorPos[3].index * STEP_CONSTANT);
    motorPos[3].counter = tmp;
}

void linearConv(uint8 MA) // milli-inche
{
    motorPos[MA].lineLength = (motorPos[MA].counter * STEP_SIZE * PI * SPOOL_DIAMETER) / 360; // milli-inches
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