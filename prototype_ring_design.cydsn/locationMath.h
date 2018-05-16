#ifndef locationMath_h
#define locationMath_h
        
    #include "project.h"
    #include "i2cFunctions.h"
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define MEASUREMENT_SCALE 1000 //scale values up to 
    #define STEP_CONSTANT 48
    #define ENCODER_RESOLUTION 500 //quadrature states per revolution (125 ppr, 4x resolution)
    #define BASE_DECODER_REGISTER 0x8000
    #define TIME_SLICE 0.050
    #define SLICE_DIVIDER 5 // Change later; arbitrary value and equally arbitrary scalar idea
    #define PI 3.142 //regular-pis
    #define STEP_SIZE 7.5 // regular-degrees
    #define MAX_MOTOR_STEP_SPEED 195
    #define FRAME_DIAMETER 15.75 //All in regular-inches
    #define SPOOL_DIAMETER 1.000
    #define PAYLOAD_DIAMETER 1.0
    #define USABLE_RADIUS (FRAME_DIAMETER/2.828)
    #define LINE_START_LENGTH (FRAME_DIAMETER/2)
    #define sideC (FRAME_DIAMETER/1.414)
    
    #define MAX_POSITION_ERROR 0.125
    
    #define CALIBRATION_LENGTH_0 10.125
    #define CALIBRATION_LENGTH_1 10.75
    #define CALIBRATION_LENGTH_2 8.95
    #define CALIBRATION_LENGTH_3 10.625
    
    #define CALIBRATION_INDEX_0 3
    #define CALIBRATION_INDEX_1 3
    #define CALIBRATION_INDEX_2 3
    #define CALIBRATION_INDEX_3 3

    extern float lineLengths[4];
    extern float MOUNT_POINTS[4][2];
    extern float PAYLOAD_CENTER[2];
    extern float NEXT_PAYLOAD_GOAL[2];
    extern float NEXT_PAYLOAD_SLICE[2];
    extern uint8 calFlags[4];

    // void linearConv(uint8 motorNum); // Now contained in updateEncoderCount
    // void payloadCorners(); // Moot; unneeded
    void calibrateEncoders();
    void updateEncoderCount();
    void lineLengthToPayloadCenter();
    void payloadToLineLength(float* payload,float* length);
    void findNextPayloadSlice();
    void lToDeltaL();
    void deltaLToSpeed();
    float pointDistance(float* payloadObserved,float* payloadExpected);

#endif