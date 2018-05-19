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
    
    motorSetSpeed(motorDat[0].addr,1000);
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
    
    motorSetSpeed(motorDat[1].addr,1000);
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
    
    motorSetSpeed(motorDat[2].addr,1000);
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
    
    motorSetSpeed(motorDat[3].addr,1000);
    while((motorDat[3].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[3].addr,HaltAndHold,0);
    
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        motorSetSpeed(motorDat[i].addr,0);
    }
    CyDelay(500);
}

void updateEncoderCount() // Now contains contents of linearConv as well
{
    int i;
    int counter[4];
    int indices[4];
    counter[0] = QuadDec_0_ReadCounter() - BASE_DECODER_REGISTER;
    counter[1] = QuadDec_1_ReadCounter() - BASE_DECODER_REGISTER;
    counter[2] = QuadDec_2_ReadCounter() - BASE_DECODER_REGISTER;
    counter[3] = QuadDec_3_ReadCounter() - BASE_DECODER_REGISTER;
    for(i = 0;i < 4;i = i + 1) // Save indices to avoid disparity
    {
        indices[i] = motorDat[i].index;
    }
    
    for(i = 0;i < 4;i = i + 1)
    {
        //we should either disable interrupts or aquire a lock on motorDat to prevent index from changing 
        // Update: Imported local copies of all indices higher up; should no longer be an issue
        motorDat[i].counter = counter[i] + (indices[i] * ENCODER_RESOLUTION) + motorDat[i].calibrationSteps;
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

void lineLengthToPayloadCenter()
{
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        /*
        float sideA = motorDat[i].lineLength; // Scale triangle sides to actual size for float math
        float sideB = motorDat[(i + 1) % 4].lineLength;
        float tmp = ((sideA*sideA) + (sideC*sideC) - (sideB*sideB)) / (2*sideA*sideC); // Law of Cosines; find angle theta of line attached to motor motorNum
        tmp = acos(tmp) + ((float)PI/4.0); // Take acos to find angle; add pi/4 = 45 degrees to switch frames of reference
        tmp = sideA * sin(tmp); // Convert to offset and scale by line length
        char prt[32];
        if(i < 2)
            tmp = FRAME_RADIUS - tmp;
        else
            tmp = tmp - FRAME_RADIUS;

        if(i == 0) // Once we get motor 3 to stop just reeling in, we should average opposed encoder readings maybe
            PAYLOAD_CENTER[0] = tmp;
        else if(i == 1)
            PAYLOAD_CENTER[1] = tmp;
        //sprintf(prt,"Motor %d: Coordinate %d\n\r",i,(int)(tmp*1000));
        UART_UartPutString(prt);
        */
        
        //char prt[32];
               
        float sideA = motorDat[i].lineLength;           // current motor's line length
        float sideB = motorDat[(i + 1) % 4].lineLength; // next motor's line length, going counter-clockwise (eg. if m0, this is m1)
        float unadjusted_ang = ((sideB*sideB) + (sideC*sideC) - (sideA*sideA)) / (2*sideB*sideC);       // Law of Cosines
        unadjusted_ang = acos(unadjusted_ang) * (180 / PI);                                                          // arccos to find actual angle
        
        float adjusted_ang = 0;
        float offset = 0;
        
        if (unadjusted_ang > 45){                   // if the angle is larger than 45 degrees 
            adjusted_ang = unadjusted_ang - 45;     // adjust the angle to use for x or y calculations from the x or y axis
            offset = sideB * cos(adjusted_ang * (PI / 180)); 
            
        } else if (unadjusted_ang < 45) {           // if the angle is smaller than 45 degrees
            adjusted_ang = 45 - unadjusted_ang;     // angle calculated is not relative to x or y axis, need to adjust
            offset = sideB * cos(adjusted_ang * (PI / 180)); 
        } else {                                    // the angle was exactly 0 degrees
            offset = 0;                             // there's no offset so x or y is 0
        }
        
       // convert to coordinate from offset
        if (i < 2) {
            offset = FRAME_RADIUS - offset;   
        } else {
            offset = offset - FRAME_RADIUS;
        }
        
        //sprintf(prt,"Motor %d: Angle %d, Coordinate %d\n\r",i,(int)(unadjusted_ang*1000),(int)(offset*1000));
        //UART_UartPutString(prt);
        
        // use this info to get either x or y offset, depending which motor we're on
        if (i % 2 == 0) {                           // we're getting an x val
            PAYLOAD_CENTER[0] = offset;
        } else {                                    // we're getting a y val
            PAYLOAD_CENTER[1] = offset;
        } 
    }
}


void payloadToLineLength(float* payload) // payload should be any of the 1x2 payload coordinates arrays listed in locationMath.h
{
    float tmp;
    tmp = ((MOUNT_POINTS[0][0]-payload[0])*(MOUNT_POINTS[0][0]-payload[0])) // Magnitude of vector
    + ((MOUNT_POINTS[0][1]-payload[1])*(MOUNT_POINTS[0][1]-payload[1])); // a^2 + b^2 = c^2
    lineLengths[0] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[1][0]-payload[0])*(MOUNT_POINTS[1][0]-payload[0]))
    + ((MOUNT_POINTS[1][1]-payload[1])*(MOUNT_POINTS[1][1]-payload[1]));
    lineLengths[1] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[2][0]-payload[0])*(MOUNT_POINTS[2][0]-payload[0]))
    + ((MOUNT_POINTS[2][1]-payload[1])*(MOUNT_POINTS[2][1]-payload[1]));
    lineLengths[2] = sqrt(tmp);
    tmp = ((MOUNT_POINTS[3][0]-payload[0])*(MOUNT_POINTS[3][0]-payload[0]))
    + ((MOUNT_POINTS[3][1]-payload[1])*(MOUNT_POINTS[3][1]-payload[1]));
    lineLengths[3] = sqrt(tmp);
}

void findNextPayloadCenter()
{
    NEXT_PAYLOAD_GOAL[0] = NEXT_PAYLOAD_GOAL[0];
    NEXT_PAYLOAD_GOAL[1] = NEXT_PAYLOAD_GOAL[1];
    // Use physics calculations/arbitrary requests here, e.g.
    // NEXT_PAYLOAD_GOAL = {10.3,0.125};
    char prt[32];
    sprintf(prt,"Payload goal: %d,%d\n\r",(int)(1000*NEXT_PAYLOAD_GOAL[0]),(int)(1000*NEXT_PAYLOAD_GOAL[1]));
    UART_UartPutString(prt);
}

void findNextPayloadSlice()
{
    
    /* Time slice calculation (sort of)
    float biggestMove;
    if(abs((int)payloadDiff[0]) > abs((int)payloadDiff[1]))
        biggestMove = payloadDiff[0];
    else
        biggestMove = payloadDiff[1];
    float divisor = biggestMove;
    */
    /*
    NEXT_PAYLOAD_SLICE[0] = PAYLOAD_CENTER[0] - (payloadDiff[0] / SLICE_DIVIDER); // I don't know if this is the best way to do this right now
    NEXT_PAYLOAD_SLICE[1] = PAYLOAD_CENTER[1] - (payloadDiff[1] / SLICE_DIVIDER); // It's a placeholder at least
    */
    
    char prt[64];
    float payloadDiff = pointDistance(PAYLOAD_CENTER,NEXT_PAYLOAD_GOAL);
    if(payloadDiff < 0.5) // If it's under half an inch from the destination, just go to the destination
    {
        NEXT_PAYLOAD_SLICE[0] = NEXT_PAYLOAD_GOAL[0];
        NEXT_PAYLOAD_SLICE[1] = NEXT_PAYLOAD_GOAL[1];
    }
    else // Otherwise, move half an inch toward the destination
    {
        NEXT_PAYLOAD_SLICE[0] = (PAYLOAD_CENTER[0] + ((NEXT_PAYLOAD_GOAL[0] - PAYLOAD_CENTER[0]) / (2 * payloadDiff)));
        NEXT_PAYLOAD_SLICE[1] = (PAYLOAD_CENTER[1] + ((NEXT_PAYLOAD_GOAL[1] - PAYLOAD_CENTER[1]) / (2 * payloadDiff)));
    }
    
    payloadDiff = sqrt((NEXT_PAYLOAD_SLICE[0]*NEXT_PAYLOAD_SLICE[0]) + (NEXT_PAYLOAD_SLICE[1]*NEXT_PAYLOAD_SLICE[1])); // Check that it's 0.5, should display as 500
    
    sprintf(prt,"Current location: \t\t%d, %d",(int)(1000*PAYLOAD_CENTER[0]),(int)(1000*PAYLOAD_CENTER[1]));
    UART_UartPutString(prt);
    sprintf(prt,"Next payload slice: \t\t%d,%d;\t\tDistance: %d\n\r",(int)(1000*NEXT_PAYLOAD_SLICE[0]),(int)(1000*NEXT_PAYLOAD_SLICE[1]),(int)(1000*payloadDiff));
    UART_UartPutString(prt);
}

void lToDeltaL()
{
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        //motorDat[i].deltaL = motorDat[i].nextLineLength - motorDat[i].lineLength; // Positive for longer line; negative for shorter line; doesn't match speed inputs
        motorDat[i].deltaL = motorDat[i].lineLength - motorDat[i].nextLineLength; // Signs match speed control inputs
    }
}

void deltaLToSpeed()
{
    
    int i;
    float q = 0.0;
    float speed[4];
    //char prt[32];
    for(i = 0;i < 4;i = i + 1)
    {
        speed[i] = (motorDat[i].deltaL * 360.0) / (PI * SPOOL_DIAMETER * TIME_SLICE * STEP_SIZE);
        if(abs((int)speed[i]) > abs((int)q))
            q = speed[i];
        //sprintf(prt,"Motor %d speed: %d\n\r",i,(int)(motorDat[i].deltaL*1000));
        //UART_UartPutString(prt);
    }
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].stepSpeed = (int)((speed[i] * MAX_MOTOR_STEP_SPEED) / (float)abs((int)q));
    }
    
    
    // re-try
    
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