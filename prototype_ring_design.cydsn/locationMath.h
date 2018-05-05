#include "i2cFunctions.h"
#include "project.h"

#define STEP_CONSTANT 48
#define DECODER_RESOLUTION 2;
#define BASE_DECODER_REGISTER 0x8000

void getMotor0();
void getMotor1();
void getMotor2();
void getMotor3();