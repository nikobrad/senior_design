#include "locationMath.h"

void updateEncoderCount(uint8 motorNum)
{
    int counter;
    switch(motorNum)
    {
        case 0:
        {
            counter = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 1:
        {
            counter = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 2:
        {
            counter = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        case 3:
        {
            counter = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
            break;
        }
        default:
        {
            counter = BASE_DECODER_REGISTER;
            break;
        }
    }

    counter = counter + (motorDat[motorNum].index * ENCODER_RESOLUTION);
    motorDat[motorNum].counter = counter;
    motorDat[motorNum].lineLength = ((motorDat[motorNum].counter) / ENCODER_RESOLUTION) * PI * SPOOL_DIAMETER; // normal-inches
}

void payloadCorners() // regular-ol'-inches
{
    PAYLOAD_CORNERS[0][0] = PAYLOAD_CENTER[0] + (PAYLOAD_SIDELEN / 1.414); // Add to and subtract from payload center coordinates using payload dimensions to find corner coordinates
    PAYLOAD_CORNERS[0][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[1][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[1][1] = PAYLOAD_CENTER[1] + (PAYLOAD_SIDELEN / 1.414);
    
    PAYLOAD_CORNERS[2][0] = PAYLOAD_CENTER[0] - (PAYLOAD_SIDELEN / 1.414);
    PAYLOAD_CORNERS[2][1] = PAYLOAD_CENTER[1];
    
    PAYLOAD_CORNERS[3][0] = PAYLOAD_CENTER[0];
    PAYLOAD_CORNERS[3][1] = PAYLOAD_CENTER[1] - (PAYLOAD_SIDELEN / 1.414);
}

void lineLengthToPayloadCenter(uint8 motorNum)
{
    int i;
    for(i = 0;i < 2;i = i + 1)
    {
        float sideA = motorDat[motorNum % 4].lineLength; // Scale triangle sides to actual size for float math
        float sideB = motorDat[(motorNum + 1) % 4].lineLength;
        float sideC = FRAME_DIAMETER / 1.414;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
        tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
        tmp = sideA * cos(tmp); // Convert to offset and scale by line length
        PAYLOAD_CENTER[(motorNum + 1) % 2] = tmp; // For even motorNum, calculates py and stores in PAYLOAD_CENTER[1]; for odd motorNum, calculates px and stores in PAYLOAD_CENTER[0]
        char prt[16]; // Print findings to UART terminal for verification
        sprintf(prt,"Motor %d: Coordinate %f\n\r",(motorNum % 4),tmp);
        UART_UartPutString(prt);
        motorNum = motorNum + 1; // Increment motorNum to do it all over again; find other part of coordinates, verify calculations, etc
    }
    for(i = 0;i < 2;i = i + 1) // Same code, but doesn't change any values; just calculating same values from other two line lengths for confirmation
    {
        float sideA = motorDat[motorNum % 4].lineLength; // Scale triangle sides to actual size for float math
        float sideB = motorDat[(motorNum + 1) % 4].lineLength;
        float sideC = FRAME_DIAMETER / 1.414;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
        tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
        tmp = sideA * cos(tmp); // Convert to offset and scale by line length
        // PAYLOAD_CENTER[(motorNum + 1) % 2] = tmp; // For even motorNum, calculates py and stores in PAYLOAD_CENTER[1]; for odd motorNum, calculates px and stores in PAYLOAD_CENTER[0]
        char prt[16]; // Print findings to UART terminal for verification
        sprintf(prt,"Motor %d: Coordinate %f\n\r",(motorNum % 4),tmp);
        UART_UartPutString(prt);
        motorNum = motorNum + 1; // Increment motorNum to do it all over again; find other part of coordinates, verify calculations, etc
    }
}

void payloadToLineLength(float* length) // length should be an array of length 4 allocated on the heap
{
    float tmp = ((MOUNT_POINTS[0][0]-PAYLOAD_CENTER[0])*(MOUNT_POINTS[0][0]-PAYLOAD_CENTER[0]))
    + ((MOUNT_POINTS[0][1]-PAYLOAD_CENTER[1])*(MOUNT_POINTS[0][1]-PAYLOAD_CENTER[1]));
    length[0] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[1][0]-PAYLOAD_CENTER[0])*(MOUNT_POINTS[1][0]-PAYLOAD_CENTER[0]))
    + ((MOUNT_POINTS[1][1]-PAYLOAD_CENTER[1])*(MOUNT_POINTS[1][1]-PAYLOAD_CENTER[1]));
    length[1] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[2][0]-PAYLOAD_CENTER[0])*(MOUNT_POINTS[2][0]-PAYLOAD_CENTER[0]))
    + ((MOUNT_POINTS[2][1]-PAYLOAD_CENTER[1])*(MOUNT_POINTS[2][1]-PAYLOAD_CENTER[1]));
    length[2] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[3][0]-PAYLOAD_CENTER[0])*(MOUNT_POINTS[3][0]-PAYLOAD_CENTER[0]))
    + ((MOUNT_POINTS[3][1]-PAYLOAD_CENTER[1])*(MOUNT_POINTS[3][1]-PAYLOAD_CENTER[1]));
    length[3] = sqrt(tmp);
}

void deltaLToSpeed()
{
    int i;
    float q = 0.0;
    float speed[4];
    for(i = 0;i < 4;i = i + 1)
    {
        speed[i] = (motorDat[i].deltaL * 360.0 ) / (PI * SPOOL_DIAMETER * TIME_SLICE);
        if(abs((int)speed[i]) > abs((int)q))
            q = speed[i];
    }
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].stepSpeed = (int)((speed[i] * MAX_MOTOR_STEP_SPEED) / (float)abs((int)q));
    }
}