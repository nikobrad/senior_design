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
    
    CyDelay(500);
    motorSetSpeed(motorDat[0].addr, -25.0); 
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
    
    motorSetSpeed(motorDat[0].addr,25.0);
    while((motorDat[0].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[0].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 1 #########################################
    
    CyDelay(500);
    motorSetSpeed(motorDat[1].addr, -25.0); 
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
    
    motorSetSpeed(motorDat[1].addr,25.0);
    while((motorDat[1].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();
        sprintf(prt,"Motor 1: Calculated Length: %d\n\r", (int)(motorDat[1].lineLength * 100000));
        UART_UartPutString(prt);
    }
    motorCommand(motorDat[1].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 2 #########################################
    
    CyDelay(500);
    motorSetSpeed(motorDat[2].addr, -25.0); 
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
    
    motorSetSpeed(motorDat[2].addr,25.0);
    while((motorDat[2].lineLength > (MAX_POSITION_ERROR + (FRAME_DIAMETER / 2))))// || (motorDat[i].lineLength < (MAX_POSITION_ERROR - (FRAME_DIAMETER / 2))))
    {
        updateEncoderCount();   
    }
    motorCommand(motorDat[2].addr,HaltAndHold,0);
    
    
    //######################## MOTOR 3 #########################################    
    
    CyDelay(500);
    motorSetSpeed(motorDat[3].addr, -25.0); 
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
    
    motorSetSpeed(motorDat[3].addr,25.0);
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

void lineLengthToPayloadCenter()
{
    float offsets[4];
    int i;
    for(i = 0;i < 4;i = i + 1)
    {   
        float sideA = motorDat[i].lineLength;           // current motor's line length
        float sideB = motorDat[(i + 1) % 4].lineLength; // next motor's line length, going counter-clockwise (eg. if m0, this is m1)
        float unadjusted_ang = ((sideB*sideB) + (sideC*sideC) - (sideA*sideA)) / (2*sideB*sideC);       // Law of Cosines
        unadjusted_ang = acos(unadjusted_ang);                                                          // arccos to find actual angle
        
        float adjusted_ang = 0;
        float offset = 0;
        
        if (unadjusted_ang > (PI / 4)){                   // if the angle is larger than 45 degrees 
            adjusted_ang = unadjusted_ang - (PI /4);     // adjust the angle to use for x or y calculations from the x or y axis
            offset = sideB * sin(adjusted_ang); 
            
            // convert to coordinate from offset
            if (i < 2) {
                offset = -offset;  
            }
            
        } 
        else if (unadjusted_ang < (PI / 4)) 
        {           // if the angle is smaller than 45 degrees
            adjusted_ang = (PI /4) - unadjusted_ang;     // angle calculated is not relative to x or y axis, need to adjust
            offset = sideB * sin(adjusted_ang); 
            
            // convert to coordinate from offset
            if (i > 1) 
            {
                offset = -offset;
            }
            
        } 
        else 
        {                                    // the angle was exactly 0 degrees
            offset = 0;                             // there's no offset so x or y is 0
        }
        offsets[i] = offset;
    }
    PAYLOAD_CENTER[0] = (offsets[0] + offsets[2]) / 2;
    PAYLOAD_CENTER[1] = (offsets[1] + offsets[3]) / 2;
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
    float error = nextPosition - position; // Position error in inches
    char prt[32];
    sprintf(prt,"Position: %d\tError: %d\n\r",(int)(position * 1000),(int)(error * 1000));
    //UART_UartPutString(prt);
    error = error * POSITION_ERROR_COEFFICIENT; // Scale to make sense compared with radians
    
    NEXT_PAYLOAD_GOAL[0] = 0.0; // Go to stable rest position
    NEXT_PAYLOAD_GOAL[1] = -USABLE_RADIUS;
    
    if(error > (PI / 2)) // Limit values to lower half of usable plane
        error = PI / 2;
    else if(error < (-PI / 2))
        error = -PI / 2;
    
    //error = error - angle; // Add measured chassis rotation to account for rotating coordinate system
    
    rotationMatrix(error); // Apply rotation matrix to NEXT_PAYLOAD_GOAL
    
    rotationMatrix(-angle);
    
    float origin[2] = {0.0,0.0};
    float tmp = pointDistance(NEXT_PAYLOAD_GOAL,origin); // Magnitude of goal vector
    if(tmp > USABLE_RADIUS) // If goal is outside usable radius, move it to the edge of the usable radius
    {
        NEXT_PAYLOAD_GOAL[0] = (NEXT_PAYLOAD_GOAL[0] * USABLE_RADIUS) / tmp;
        NEXT_PAYLOAD_GOAL[1] = (NEXT_PAYLOAD_GOAL[1] * USABLE_RADIUS) / tmp;
    }
}

void findNextPayloadSlice()
{   
    float payloadDiff = pointDistance(PAYLOAD_CENTER,NEXT_PAYLOAD_GOAL);
    

    if(payloadDiff < 0.5) // If it's under half an inch from the destination, just go to the destination
    {
        NEXT_PAYLOAD_SLICE[0] = NEXT_PAYLOAD_GOAL[0];
        NEXT_PAYLOAD_SLICE[1] = NEXT_PAYLOAD_GOAL[1];
    }
    else // Otherwise, move half an inch toward the destination
    {
        NEXT_PAYLOAD_SLICE[0] = (PAYLOAD_CENTER[0] + ((NEXT_PAYLOAD_GOAL[0] - PAYLOAD_CENTER[0]) / DISTANCE_SCALAR));
        NEXT_PAYLOAD_SLICE[1] = (PAYLOAD_CENTER[1] + ((NEXT_PAYLOAD_GOAL[1] - PAYLOAD_CENTER[1]) / DISTANCE_SCALAR));
    }
    
    
}

void lToDeltaL()
{
    int i;
    for(i = 0;i < 4;i = i + 1)
    {
        motorDat[i].deltaL = motorDat[i].lineLength - motorDat[i].nextLineLength; // Signs match speed control inputs
    }
}

void deltaLToSpeed()
{
    
    int i;
    float q = 0.0;
    float r = 0.0;
    float speed[4];
    char prt[32];
    for(i = 0;i < 4;i = i + 1)
    {
        if(abs((int)motorDat[i].stepSpeed) > abs((int)r))
            r = motorDat[i].stepSpeed;
        speed[i] = (motorDat[i].deltaL * 360.0) / (PI * SPOOL_DIAMETER * TIME_SLICE * STEP_SIZE * LINEAR_SPEED_SCALAR);
        if(abs((int)speed[i]) > abs((int)q))
            q = speed[i];
    }
    if(abs((int)q) > abs((int)r))
    {
        sprintf(prt,"Top speed: %d\n\r",(int)(1000*q));
        UART_UartPutString(prt);
    }
    if(abs((int)q) > MAX_MOTOR_STEP_SPEED)
    {
        for(i = 0;i < 4;i = i + 1)
        {
            motorDat[i].stepSpeed = (speed[i] * MAX_MOTOR_STEP_SPEED) / (float)abs((int)q);
        }
    }
    else
    {
        motorDat[i].stepSpeed = speed[i];
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

void rotationMatrix(float theta)
{
    float retval[2];
    retval[0] = (NEXT_PAYLOAD_GOAL[0] * cos(theta)) - (NEXT_PAYLOAD_GOAL[1] * sin(theta));
    retval[1] = (NEXT_PAYLOAD_GOAL[0] * sin(theta)) + (NEXT_PAYLOAD_GOAL[1] * cos(theta));
    NEXT_PAYLOAD_GOAL[0] = retval[0];
    NEXT_PAYLOAD_GOAL[1] = retval[1];
}