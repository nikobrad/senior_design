#ifndef locationmotorIndexth_h
    #define locationmotorIndexth_h
        
    #include "project.h"
    #include "i2cFunctions.h"
    #include <math.h>
    #include <stdio.h>

    #define STEP_CONSTANT 48
    #define DECODER_RESOLUTION 2;
    #define BASE_DECODER_REGISTER 0x8000
    #define PI 3142 //milli-pis
    #define STEP_SIZE 7500 // milli-degrees
    #define FRAME_DIAMETER 13500 //All in milli-inches
    #define SPOOL_DIAMETER 2000
    #define PAYLOAD_SIDELEN 2500
    #define MOUNT_POINTS {{(FRAME_DIAMETER/2),0},{0,(FRAME_DIAMETER/2)},{(-1*FRAME_DIAMETER/2),0},{0,(-1*FRAME_DIAMETER/2)}}

    extern int PAYLOAD_CENTER[2];
    extern int PAYLOAD_CORNERS[4][2];

    void updateMotorRotation(uint8 motorIndex);
    void linearConv(uint8 motorIndex);
    void payloadCorners();
    void calcPayloadCenter(uint8 motorIndex);

    /* DEFUNCT
    void getMotor0();
    void getMotor1();
    void getMotor2();
    void getMotor3();
    */
#endif