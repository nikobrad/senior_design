#include "locationMath.h"

void updateEncoderCount(uint8 motorNum)
{
    int tmp;
    switch(motorNum)
    {
        case 0:
        {
            tmp = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 1:
        {
            tmp = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 2:
        {
            tmp = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 3:
        {
            tmp = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        default:
        {
            tmp = BASE_DECODER_REGISTER;
        }
    }
    //TODO: Figure out actual calculations here 
    tmp = tmp / DECODER_RESOLUTION;
    tmp = tmp + (motorDat[motorNum].index * STEP_CONSTANT); //shouldn't scale with STEP_CONSTANT, encoder pulse != motor step
    motorDat[motorNum].counter = tmp;
    //TODO: call linearConv()? any reason not to?
}

void linearConv(uint8 motorNum) // milli-inche
{
    motorDat[motorNum].lineLength = (motorDat[motorNum].counter * STEP_SIZE * PI * SPOOL_DIAMETER) / 360; // milli-inches
}

void payloadCorners() // milli-inches
{
    PAYLOAD_CORNERS[0][0] = PAYLOAD_CENTER[0] + ((PAYLOAD_SIDELEN * 1414) / 2000); // Add to and subtract from payload center coordinates using payload dimensions to find corner coordinates
    PAYLOAD_CORNERS[0][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[1][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[1][1] = PAYLOAD_CENTER[1] + ((PAYLOAD_SIDELEN * 1414) / 2000);
    
    PAYLOAD_CORNERS[2][0] = PAYLOAD_CENTER[0] - ((PAYLOAD_SIDELEN * 1414) / 2000);
    PAYLOAD_CORNERS[2][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[3][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[3][1] = PAYLOAD_CENTER[1] - ((PAYLOAD_SIDELEN * 1414) / 2000);
}

void calcPayloadCenter(uint8 motorNum)
{
    int i;
    for(i = 0;i < 2;i = i + 1)
    {
        float sideA = (float)motorDat[motorNum % 4].lineLength / 1000.0; // Scale triangle sides to actual size for float math
        float sideB = (float)motorDat[(motorNum + 1) % 4].lineLength / 1000.0;
        float sideC = (float)FRAME_DIAMETER / 1414.0;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
        tmp = acos(tmp) + (3.14159/4); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
        tmp = sideA * cos(tmp); // Convert to offset and scale by line length
        tmp = tmp * 1000; // Convert back to milli-inches
        int ret = (int) tmp; // Integer milli-inches
        PAYLOAD_CENTER[(motorNum + 1) % 2] = ret; // For even motorNum, calculates py and stores in PAYLOAD_CENTER[1]; for odd motorNum, calculates px and stores in PAYLOAD_CENTER[0]
        char prt[16]; // Print findings to UART terminal for verification
        sprintf(prt,"Motor %d: Coordinate %d\n\r",(motorNum % 4),ret);
        UART_UartPutString(prt);
        motorNum = motorNum + 1; // Increment motorNum to do it all over again; find other part of coordinates, verify calculations, etc
    }
    for(i = 0;i < 2;i = i + 1) // Same code, but doesn't change any values; just calculating same values from other two line lengths for confirmation
    {
        float sideA = (float)motorDat[motorNum % 4].lineLength / 1000.0;
        float sideB = (float)motorDat[(motorNum + 1) % 4].lineLength / 1000.0;
        float sideC = (float)FRAME_DIAMETER / 1414.0;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC);
        tmp = acos(tmp) + (3.14159/4);
        tmp = cos(tmp);
        tmp = tmp * 1000;
        int ret = (int) tmp;
        //PAYLOAD_CENTER[(MA + 1) % 2] = ret;
        char prt[16];
        sprintf(prt,"Motor %d: Coordinate %d\n\r",(motorNum % 4),ret);
        UART_UartPutString(prt);
        motorNum = motorNum + 1;
    }
}