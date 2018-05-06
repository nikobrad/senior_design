#ifndef i2cFunctions_h
    #define i2cFunctions_h

    #include "project.h"    

    #define STEP_SCALE 100

    typedef enum
    { 
    	Motor0 		= 	10,
    	Motor1 		= 	11,
    	Motor2 		= 	12,
    	Motor3 		= 	13,
    } MotorAddress;

    typedef struct
    {
        MotorAddress MA;
    	int counter;
    	int index;
        int calibrationLength;
        int lineLength;
    } MotorData;

    extern MotorData motorDat[4];

    void motorCommand(MotorAddress MA,uint8 cmd,uint32 arg);

    void motorSetSpeed(MotorAddress MA,int targetVelocity);
    void motorSetPosition(MotorAddress MA,int targetPosition);
    void motorSafeStartExit(MotorAddress MA);
    void motorEnergize(MotorAddress MA);
    void motorDeenergize(MotorAddress MA);

#endif

//From Tic C++ Arduino library:
/*
typedef enum
{
  IntentionallyDeenergized = 0,
  MotorDriverError         = 1,
  LowVin                   = 2,
  KillSwitch               = 3,
  RequiredInputInvalid     = 4,
  SerialError              = 5,
  CommandTimeout           = 6,
  SafeStartViolation       = 7,
  ErrLineHigh              = 8,
  SerialFraming            = 16,
  RxOverrun                = 17,
  Format                   = 18,
  Crc                      = 19,
  EncoderSkip              = 20,
} TicError;

typedef enum
{
  SetTargetPosition                 = 0xE0,
  SetTargetVelocity                 = 0xE3,
  HaltAndSetPosition                = 0xEC,
  HaltAndHold                       = 0x89,
  ResetCommandTimeout               = 0x8C,
  Deenergize                        = 0x86,
  Energize                          = 0x85,
  ExitSafeStart                     = 0x83,
  EnterSafeStart                    = 0x8F,
  Reset                             = 0xB0,
  ClearDriverError                  = 0x8A,
  SetSpeedMax                       = 0xE6,
  SetStartingSpeed                  = 0xE5,
  SetAccelMax                       = 0xEA,
  SetDecelMax                       = 0xE9,
  SetStepMode                       = 0x94,
  SetCurrentLimit                   = 0x91,
  SetDecayMode                      = 0x92,
  GetVariable                       = 0xA1,
  GetVariableAndClearErrorsOccurred = 0xA2,
  GetSetting                        = 0xA8,
} TicCommand;

typedef enum
{
  Reset             = 0,
  Deenergized       = 2,
  SoftError         = 4,
  WaitingForErrLine = 6,
  StartingUp        = 8,
  Normal            = 10,
} TicOperationState;

typedef enum
{
  Off            = 0,
  TargetPosition = 1,
  TargetVelocity = 2,
} TicPlanningMode;

typedef enum
{
  PowerUp        = 0,
  Brownout       = 1,
  ResetLine      = 2,
  Watchdog       = 4,
  Software       = 8,
  StackOverflow  = 16,
  StackUnderflow = 32,
} TicReset;

typedef enum
{
  Full    = 0,
  Half    = 1,

  Microstep1  = 0,
  Microstep2  = 1,
  Microstep4  = 2,
  Microstep8  = 3,
  Microstep16 = 4,
  Microstep32 = 5,
} TicStepMode;

typedef enum
{
  SCL = 0,
  SDA = 1,
  TX  = 2,
  RX  = 3,
  RC  = 4,
} TicPin;

typedef enum
{
  HighImpedance = 0,
  InputPullUp   = 1,
  OutputLow     = 2,
  OutputHigh    = 3,
} TicPinState;
*/
	