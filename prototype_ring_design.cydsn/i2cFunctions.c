#include "i2cFunctions.h"

void motorSetSpeed(uint8 motorIndex,int targetVelocity)
{
	uint8 buf[5];	//Set up a buffer for commotorIndexnd code and argument
	uint8 addr = (uint8)motorDat[motorIndex].MA;
	int stepVelocity = targetVelocity * STEP_SCALE;	//NormotorIndexlize for internal scaling; targetVelocity is in steps * 10^(-4)
	
	buf[0] = 0xE3;	//CommotorIndexnd code for set velocity
	buf[1] = stepVelocity & 0xFF;	//Shift normotorIndexlized argument value and save bytes in buffer
	buf[2] = (stepVelocity >> 8) & 0xFF;
	buf[3] = (stepVelocity >> 16) & 0xFF;
	buf[4] = (stepVelocity >> 24) & 0xFF;
	
    
	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set speed of selected motor through I2C connection
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSetSpeed()


void motorSetPosition(uint8 motorIndex,int targetPosition)
{
	uint8 buf[5];	//Set up a buffer for commotorIndexnd code and argument
	uint8 addr = (uint8)motorDat[motorIndex].MA;
	 
	buf[0] = 0xE0;	//CommotorIndexnd code for set position
	buf[1] = targetPosition & 0xFF;	//Shift argument value and save bytes in buffer
	buf[2] = (targetPosition >> 8) & 0xFF;
	buf[3] = (targetPosition >> 16) & 0xFF;
	buf[4] = (targetPosition >> 24) & 0xFF;
	
	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set position of selected motor through I2C connection
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSetPosition()

void motorSafeStartExit(uint8 motorIndex)
{
	uint8 buf = 0x83;	//Set up buffer for commotorIndexnd code
	uint8 addr = (uint8)motorDat[motorIndex].MA;
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start commotorIndexnd to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSafeStartExit()

void motorEnergize(uint8 motorIndex)
{
	uint8 buf = 0x85;	//Set up buffer for commotorIndexnd code
	uint8 addr = (uint8)motorDat[motorIndex].MA;
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start commotorIndexnd to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorEnergize()

void motorDeenergize(uint8 motorIndex)
{
	uint8 buf = 0x86;	//Set up buffer for commotorIndexnd code
	uint8 addr = (uint8)motorDat[motorIndex].MA;
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start commotorIndexnd to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorDeenergize()

void motorCommotorIndexnd32(uint8 motorIndex,uint8 cmd,uint32 arg)
{
    uint8 addr = (uint8)motorDat[motorIndex].MA;
    if(arg)
    {
        uint8 buf[5];	//Set up a buffer for commotorIndexnd code and argument
    	buf[0] = cmd;	//CommotorIndexnd code for set position
    	buf[1] = arg & 0xFF;	//Shift argument value and save bytes in buffer
    	buf[2] = (arg >> 8) & 0xFF;
    	buf[3] = (arg >> 16) & 0xFF;
    	buf[4] = (arg >> 24) & 0xFF;
    	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set position of selected motor through I2C connection
    }
    else
    {
        uint8 buf = cmd;	//Set up buffer for commotorIndexnd code
    	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start commotorIndexnd to I2C
    }
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}   //motorCommotorIndexnd32

//***Experimental/in development

/*

int* getCounters()
{
	int counters[4];
	counters[0] = QuadDec0_GetCounter();	//Just get all the counters
	counters[1] = QuadDec1_GetCounter();
	counters[2] = QuadDec2_GetCounter();
	counters[3] = QuadDec3_GetCounter();
	return(counters);
}	//getCounters()
	
int* getAbsPositions()
{
	int i;
	int counters[4] = getCounters();	//Just get all the counters
	int absPos[4];	//Each step is 7.5 degrees; 360 degrees/revolution / 7.5 degrees/step = 48 steps per revolution
	for(i=0;i<4;i=i+1)
	{
		absPos[i] = (48 * decInd[i]) + counters[i];
	}
	return(absPos);
}	//getAbsPosition()

int radialToLinear(float rotVal)
{
	float linear = rotVal * (float)(1.0/48.0) * (float)(2.0*PI*SPOOL_RADIUS);	//rotVal steps * 1/48 rotations/step * 2*PI*SPOOL_RADIUS units/rotation = linear units
	return linear;
}	//radialToLinear()
*/