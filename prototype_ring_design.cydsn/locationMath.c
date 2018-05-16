#include "locationMath.h"

void calibrateEncoders()
{
    
    char prt[60];
    float offsetLength;
    
    for(int i = 0; i< 4; i++)
    {
        motorDat[i].index = 0;   
    }

    //######################## MOTOR 0 #########################################
    
    motorSetSpeed(motorDat[0].addr, -1000); 
    while(motorDat[0].index == 0) {} //no index pulses have been read yet
    motorCommand(motorDat[0].addr, HaltAndHold, 0);
    
    motorDat[0].index = CALIBRATION_INDEX_0;
    updateEncoderCount();
    
    sprintf(prt,"Motor 0: Calculated Length: %d\n\r", (int)(motorDat[0].lineLength * 100000));
    UART_UartPutString(prt);
    
    sprintf(prt,"Motor 0: Counter value: %d\n\r", (int)(QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER));
    UART_UartPutString(prt);
    
    offsetLength = CALIBRATION_LENGTH_0 - motorDat[0].lineLength;
    motorDat[0].calibrationSteps = (offsetLength * ENCODER_RESOLUTION) / (PI * SPOOL_DIAMETER);
    
    motorSetSpeed(motorDat[0].addr,500);
    while((motorDat[0].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[0].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 1 #########################################
    
    motorSetSpeed(motorDat[1].addr, -1000); 
    while(motorDat[1].index == 0) {} //no index pulses have been read yet
    motorCommand(motorDat[1].addr, HaltAndHold, 0);
    
    motorDat[1].index = CALIBRATION_INDEX_1;
    updateEncoderCount();
    
    sprintf(prt,"Motor 1: Calculated Length: %d\n\r", (int)(motorDat[1].lineLength * 100000));
    UART_UartPutString(prt);
    
    sprintf(prt,"Motor 1: Counter value: %d\n\r", (int)(QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER));
    UART_UartPutString(prt);
    
    offsetLength = CALIBRATION_LENGTH_1 - motorDat[1].lineLength;
    motorDat[1].calibrationSteps = (offsetLength * ENCODER_RESOLUTION) / (PI * SPOOL_DIAMETER);
    
    motorSetSpeed(motorDat[1].addr,500);
    while((motorDat[1].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[1].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 2 #########################################
    
    motorSetSpeed(motorDat[2].addr, -1000); 
    while(motorDat[2].index == 0) {} //no index pulses have been read yet
    motorCommand(motorDat[2].addr, HaltAndHold, 0);
    
    motorDat[2].index = CALIBRATION_INDEX_2;
    updateEncoderCount();
    
    sprintf(prt,"Motor 2: Calculated Length: %d\n\r", (int)(motorDat[2].lineLength * 100000));
    UART_UartPutString(prt);
    
    sprintf(prt,"Motor 2: Counter value: %d\n\r", (int)(QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER));
    UART_UartPutString(prt);
    
    offsetLength = CALIBRATION_LENGTH_2 - motorDat[2].lineLength;
    motorDat[2].calibrationSteps = (offsetLength * ENCODER_RESOLUTION) / (PI * SPOOL_DIAMETER);
    
    motorSetSpeed(motorDat[2].addr,500);
    while((motorDat[2].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[2].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 3 #########################################    
    
    motorSetSpeed(motorDat[3].addr, -1000); 
    while(motorDat[3].index == 0) {} //no index pulses have been read yet
    motorCommand(motorDat[3].addr, HaltAndHold, 0);
    
    motorDat[3].index = CALIBRATION_INDEX_3;
    updateEncoderCount();

    sprintf(prt,"Motor 3: Calculated Length: %d\n\r", (int)(motorDat[3].lineLength * 100000));
    UART_UartPutString(prt);
    
    sprintf(prt,"Motor 3: Counter value: %d\n\r", (int)(QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER));
    UART_UartPutString(prt);

    offsetLength = CALIBRATION_LENGTH_3 - motorDat[3].lineLength;
    motorDat[3].calibrationSteps = (offsetLength * ENCODER_RESOLUTION) / (PI * SPOOL_DIAMETER);
    
    motorSetSpeed(motorDat[3].addr,500);
    while((motorDat[3].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[3].addr,HaltAndHold,0);  
}

void updateEncoderCount() // Now contains contents of linearConv as well
{
    int counter[4];
    counter[0] = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
    counter[1] = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
    counter[2] = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
    counter[3] = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
    
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        //we should wither disable interrupts or aquire a lock on motorDat to prevent index from changing 
        motorDat[i].counter = counter[i] + (motorDat[i].index * ENCODER_RESOLUTION) + motorDat[i].calibrationSteps;
        motorDat[i].lineLength = (((float)(motorDat[i].counter)) / (float)ENCODER_RESOLUTION) * PI * SPOOL_DIAMETER; // normal-inches
    }
}

/*
void payloadCorners() // moot; not needed
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
*/
/*
void lineLengthToPayloadCenter()
{
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        float sideA = motorDat[i].lineLength; // Scale triangle sides to actual size for float math
        float sideB = motorDat[(i + 1) % 4].lineLength;
        float sideC = FRAME_DIAMETER / 1.414;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
        tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
        tmp = sideA * cos(tmp); // Convert to offset and scale by line length
        if(i == 0)
            PAYLOAD_CENTER[1] = tmp; // For even motorNum, calculates py and stores in PAYLOAD_CENTER[1]; for odd motorNum, calculates px and stores in PAYLOAD_CENTER[0]
        else if(i == 3)
            PAYLOAD_CENTER[0] = tmp;
        else
            tmp = tmp * (-1);
        char prt[16]; // Print findings to UART terminal for verification
        sprintf(prt,"Motor %d: Coordinate %d\n\r",i,(int)(tmp*1000));
        UART_UartPutString(prt);
    }
}
*/

void lineLengthToPayloadCenter()
{
    float sideA = motorDat[0].lineLength; // Scale triangle sides to actual size for float math
    float sideB = motorDat[1].lineLength;
    float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
    tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
    tmp = sideA * cos(tmp); // Convert to offset and scale by line length
    PAYLOAD_CENTER[1] = tmp;
    char prt[16]; // Print findings to UART terminal for verification
    sprintf(prt,"Motor %d: Coordinate %d\n\r",0,(int)(tmp*1000));
    UART_UartPutString(prt);
    
    sideA = motorDat[1].lineLength; // Scale triangle sides to actual size for float math
    sideB = motorDat[2].lineLength;
    tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
    tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
    tmp = sideA * cos(tmp);
    tmp = tmp * (-1);
    sprintf(prt,"Motor %d: Coordinate %d\n\r",1,(int)(tmp*1000));
    UART_UartPutString(prt);
    
    sideA = motorDat[2].lineLength; // Scale triangle sides to actual size for float math
    sideB = motorDat[3].lineLength;
    tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
    tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
    tmp = sideA * cos(tmp); // Convert to offset and scale by line length
    tmp = tmp * (-1);
    sprintf(prt,"Motor %d: Coordinate %d\n\r",2,(int)(tmp*1000));
    UART_UartPutString(prt);
    
    sideA = motorDat[3].lineLength; // Scale triangle sides to actual size for float math
    sideB = motorDat[0].lineLength;
    tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
    tmp = acos(tmp) + (PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
    tmp = sideA * cos(tmp); // Convert to offset and scale by line length
    PAYLOAD_CENTER[0] = tmp;
    sprintf(prt,"Motor %d: Coordinate %d\n\r",3,(int)(tmp*1000));
    UART_UartPutString(prt);
}

void payloadToLineLength(float* payload,float* length) // length should be an array of length 4 allocated on the heap
{ // payload should be any of the 1x2 payload coordinates arrays listed in locationMath.h
    float tmp;
    tmp = ((MOUNT_POINTS[0][0]-payload[0])*(MOUNT_POINTS[0][0]-payload[0]))
    + ((MOUNT_POINTS[0][1]-payload[1])*(MOUNT_POINTS[0][1]-payload[1]));
    length[0] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[1][0]-payload[0])*(MOUNT_POINTS[1][0]-payload[0]))
    + ((MOUNT_POINTS[1][1]-payload[1])*(MOUNT_POINTS[1][1]-payload[1]));
    length[1] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[2][0]-payload[0])*(MOUNT_POINTS[2][0]-payload[0]))
    + ((MOUNT_POINTS[2][1]-payload[1])*(MOUNT_POINTS[2][1]-payload[1]));
    length[2] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[3][0]-payload[0])*(MOUNT_POINTS[3][0]-payload[0]))
    + ((MOUNT_POINTS[3][1]-payload[1])*(MOUNT_POINTS[3][1]-payload[1]));
    length[3] = sqrt(tmp);
}

void findNextPayloadCenter()
{
    // Use physics calculations/arbitrary requests here, e.g.
    // NEXT_PAYLOAD_GOAL = {10.3,0.125};
}

void findNextPayloadSlice()
{
    float payloadDiff[2] = {(NEXT_PAYLOAD_GOAL[0] - PAYLOAD_CENTER[0]),(NEXT_PAYLOAD_GOAL[1] - PAYLOAD_CENTER[1])};
    /* Time slice calculation (sort of)
    float biggestMove;
    if(abs((int)payloadDiff[0]) > abs((int)payloadDiff[1]))
        biggestMove = payloadDiff[0];
    else
        biggestMove = payloadDiff[1];
    float divisor = biggestMove;
    */
    NEXT_PAYLOAD_SLICE[0] = PAYLOAD_CENTER[0] + (payloadDiff[0] / SLICE_DIVIDER); // I don't know if this is the best way to do this right now
    NEXT_PAYLOAD_SLICE[1] = PAYLOAD_CENTER[1] + (payloadDiff[1] / SLICE_DIVIDER); // It's a placeholder at least
}

void lToDeltaL()
{
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].deltaL = motorDat[i].nextLineLength - motorDat[i].lineLength;
    }
}

void deltaLToSpeed()
{
    int i;
    float q = 0.0;
    float speed[4];
    for(i = 0;i < 4;i = i + 1)
    {
        speed[i] = (motorDat[i].deltaL * 360.0) / (PI * SPOOL_DIAMETER * TIME_SLICE * STEP_SIZE);
        if(abs((int)speed[i]) > abs((int)q))
            q = speed[i];
    }
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].stepSpeed = (int)((speed[i] * MAX_MOTOR_STEP_SPEED) / (float)abs((int)q));
    }
}

float pointDistance(float* payloadObserved,float* payloadExpected)
{
    float distance;
    float dx = payloadObserved[0] - payloadExpected[0];
    float dy = payloadObserved[1] - payloadExpected[1];
    
    dx = dx * dx;
    dy = dy * dy;
    
    distance = sqrt(dx + dy);
    return distance;
}