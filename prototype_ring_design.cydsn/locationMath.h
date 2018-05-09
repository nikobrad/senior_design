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
    #define PI 3.142 //regular-pis
    #define STEP_SIZE 7.500 // regular-degrees
    #define FRAME_DIAMETER 13.500 //All in regular-inches
    #define SPOOL_DIAMETER 1.000
    #define PAYLOAD_SIDELEN 2.500
    #define MAX_MOTOR_STEP_SPEED 195.0

    extern float MOUNT_POINTS[4][2];
    extern float PAYLOAD_CENTER[2];
    extern float PAYLOAD_CORNERS[4][2];

    void updateEncoderCount(uint8 motorNum);

    void linearConv(uint8 motorNum);
    void payloadCorners();
    void lineLengthToPayloadCenter(uint8 motorNum);
    
    void deltaLToSpeed();
    void payloadToLineLength();

#endif