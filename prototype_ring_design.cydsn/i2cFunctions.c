#include "i2cFunctions.h"

void motorSetSpeed(MotorAddress addr,float targetVelocity)
{
	uint8 buf[5];	//Set up a buffer for command code and argument
	int stepVelocity = (int)(targetVelocity * STEP_SCALE);	//Normalize for internal scaling; targetVelocity is in steps * 10^(-4)
	buf[0] = 0xE3;	//Command code for set velocity
	buf[1] = stepVelocity & 0xFF;	//Shift normalized argument value and save bytes in buffer
	buf[2] = (stepVelocity >> 8) & 0xFF;
	buf[3] = (stepVelocity >> 16) & 0xFF;
	buf[4] = (stepVelocity >> 24) & 0xFF;
	
    
	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set speed of selected motor through I2C connection
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSetSpeed()


void motorSetPosition(MotorAddress addr,int targetPosition)
{
	uint8 buf[5];	//Set up a buffer for command code and argument
	
	buf[0] = 0xE0;	//Command code for set position
	buf[1] = targetPosition & 0xFF;	//Shift argument value and save bytes in buffer
	buf[2] = (targetPosition >> 8) & 0xFF;
	buf[3] = (targetPosition >> 16) & 0xFF;
	buf[4] = (targetPosition >> 24) & 0xFF;
	
	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set position of selected motor through I2C connection
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSetPosition()

void motorSafeStartExit(MotorAddress addr)
{
	uint8 buf = 0x83;	//Set up buffer for command code
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start command to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorSafeStartExit()

void motorEnergize(MotorAddress addr)
{
	uint8 buf = 0x85;	//Set up buffer for command code
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start command to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorEnergize()

void motorDeenergize(MotorAddress addr)
{
	uint8 buf = 0x86;	//Set up buffer for command code
	
	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start command to I2C
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}	//motorDeenergize()

void motorCommand(MotorAddress addr,uint8 cmd,uint32 arg)
{
    if(arg)
    {
        uint8 buf[5];	//Set up a buffer for command code and argument
    	
    	buf[0] = cmd;	//Command code for set position
    	buf[1] = arg & 0xFF;	//Shift argument value and save bytes in buffer
    	buf[2] = (arg >> 8) & 0xFF;
    	buf[3] = (arg >> 16) & 0xFF;
    	buf[4] = (arg >> 24) & 0xFF;
    	
    	I2C_I2CMasterWriteBuf(addr,buf,5,I2C_I2C_MODE_COMPLETE_XFER);	//Set position of selected motor through I2C connection
    }
    else
    {
        uint8 buf = cmd;	//Set up buffer for command code
    	
    	I2C_I2CMasterWriteBuf(addr,&buf,1,I2C_I2C_MODE_COMPLETE_XFER);	//Transmit safe start command to I2C
    }
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}   //motorCommand32

void accelerometerReadXY(uint8* result)
{
    result[0] = 0x32;
    I2C_I2CMasterWriteBuf(Accel1,result,1,I2C_I2C_MODE_COMPLETE_XFER);
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
    I2C_I2CMasterReadBuf(Accel1,result,4,I2C_I2C_MODE_COMPLETE_XFER);
    while(I2C_I2CMasterStatus() == I2C_I2C_MSTAT_XFER_INP); //Wait for any previous transmission to end
}