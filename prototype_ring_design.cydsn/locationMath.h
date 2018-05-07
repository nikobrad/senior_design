#ifndef locationMath_h
#define locationMath_h
        
    #include "project.h"
    #include "i2cFunctions.h"
    #include <math.h>
    #include <stdio.h>

    #define MEASUREMENT_SCALE 1000 //scale values up to 
    #define STEP_CONSTANT 48
    #define ENCODER_RESOLUTION 500 //quadrature states per revolution (125 ppr, 4x resolution)
    #define BASE_DECODER_REGISTER 0x8000
    #define PI 3142 //milli-pis
    #define STEP_SIZE 7500 // milli-degrees
    #define FRAME_DIAMETER 13500 //All in milli-inches
    #define SPOOL_DIAMETER 1000
    #define PAYLOAD_SIDELEN 2500
    #define MOUNT_POINTS {{(FRAME_DIAMETER/2),0},{0,(FRAME_DIAMETER/2)},{(-1*FRAME_DIAMETER/2),0},{0,(-1*FRAME_DIAMETER/2)}}

    extern int PAYLOAD_CENTER[2];
    extern int PAYLOAD_CORNERS[4][2];

    void updateEncoderCount(uint8 motorNum);

    void linearConv(uint8 motorNum);
    void payloadCorners();
    void calcPayloadCenter(uint8 motorNum);

#endif