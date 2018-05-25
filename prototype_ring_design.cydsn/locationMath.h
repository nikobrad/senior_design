#ifndef locationMath_h
#define locationMath_h
        
    #include "project.h"
    #include "i2cFunctions.h"
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define CLOCK_SECONDS_CONVERSION 1000000 // 1 MHz clock; 1000000 ticks per second
    #define MEASUREMENT_SCALE 1000 //scale values up to 
    #define STEP_CONSTANT 48
    #define ENCODER_RESOLUTION 500 //quadrature states per revolution (125 ppr, 4x resolution)
    #define BASE_DECODER_REGISTER 0x8000
    #define TIME_SLICE 0.010
    #define SLICE_DIVIDER 5 // Change later; arbitrary value and equally arbitrary scalar idea
    #define PI 3.142 //regular-pis
    #define STEP_SIZE 7.5 // regular-degrees
    #define MAX_MOTOR_STEP_SPEED 85.0
    #define FRAME_DIAMETER 11.6 //All in regular-inches
    #define FRAME_RADIUS (FRAME_DIAMETER / 2.0)
    #define SPOOL_DIAMETER 1.000
    #define PAYLOAD_DIAMETER 1.0
    #define USABLE_RADIUS ((FRAME_DIAMETER/2.828) - 1.5)
    #define LINE_START_LENGTH (FRAME_RADIUS)
    #define sideC (FRAME_DIAMETER/1.414)
    #define MINIMUM_GOAL_DISTANCE 0.25
    #define DISTANCE_SCALAR 5.0
    #define ACCEPTABLE_ERROR 0.25
    #define ROTATION_SCALAR (PI / 4.0) // Radians per inclinometer section
    #define POSITION_ERROR_COEFFICIENT 0.5
    
    #define MAX_POSITION_ERROR 0.125
    
    #define CALIBRATION_LENGTH_0 8.125
    #define CALIBRATION_LENGTH_1 6.75
    #define CALIBRATION_LENGTH_2 7.0
    #define CALIBRATION_LENGTH_3 8.5
    
    #define CALIBRATION_INDEX_0 2
    #define CALIBRATION_INDEX_1 2
    #define CALIBRATION_INDEX_2 2
    #define CALIBRATION_INDEX_3 2

    extern float lineLengths[4];
    extern const float MOUNT_POINTS[4][2];
    extern float PAYLOAD_CENTER[2];
    extern float NEXT_PAYLOAD_GOAL[2];
    extern float NEXT_PAYLOAD_SLICE[2];
    
    extern uint8 prevAngle;
    extern float angle;
    extern float position;
    extern float nextPosition;
    
    extern uint8 executeFlag;
    extern uint32 goalUpdateTimer;

    // void linearConv(uint8 motorNum); // Now contained in updateEncoderCount
    // void payloadCorners(); // Moot; unneeded
    void calibrateEncoders();
    void updateEncoderCount();
    void lineLengthToPayloadCenter();
    void payloadToLineLength(float* payload);
    void findNextPayloadCenter();
    void findNextPayloadSlice();
    void lToDeltaL();
    void deltaLToSpeed();
    float pointDistance(float* payloadObserved,float* payloadExpected);
    void rotationMatrix(float theta);

#endif