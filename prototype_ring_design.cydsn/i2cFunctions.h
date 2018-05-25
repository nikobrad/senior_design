#ifndef i2cFunctions_h
#define i2cFunctions_h

    #include "project.h"    
    #include "locationMath.h"

    #define STEP_SCALE 10000

    typedef enum
    { 
    	Motor0 		= 	10,
    	Motor1 		= 	11,
    	Motor2 		= 	12,
    	Motor3 		= 	13,
    } MotorAddress;
    
    typedef enum
    {
        Accel0      =   0x1D, // Alt Address pin tied high to VDD
        Accel1       =   0x53, // Alt Address pin tied low to ground
    } AccelerometerAddress; // CS pin MUST be tied high to VDD
    /*
    Hex Address     Name            Type        Reset Value     Description 
    0x00            DEVID           R           11100101        Device ID
    0x01 to 0x1C    Reserved        Reserved; do not access
    0x1D            THRESH_TAP      R/W         00000000        Tap threshold
    0x1E            OFSX            R/W         00000000        X-axis offset
    0x1F            OFSY            R/W         00000000        Y-axis offset
    0x20            OFSZ            R/W         00000000        Z-axis offset
    0x21            DUR             R/W         00000000        Tap duration
    0x22            Latent          R/W         00000000        Tap latency
    0x23            Window          R/W         00000000        Tap window
    0x24            THRESH_ACT      R/W         00000000        Activity threshold
    0x25            THRESH_INACT    R/W         00000000        Inactivity threshold
    0x26            TIME_INACT      R/W         00000000        Inactivity time
    0x27            ACT_INACT_CTL   R/W         00000000        Axis enable control for activity and inactivity detection
    0x28            THRESH_FF       R/W         00000000        Free-fall threshold
    0x29            TIME_FF         R/W         00000000        Free-fall time
    0x2A            TAP_AXES        R/W         00000000        Axis control for single tap/double tap
    0x2B            ACT_TAP_STATUS  R           00000000        Source of single tap/double tap
    0x2C            BW_RATE         R/W         00001010        Data rate and power mode control
    0x2D            POWER_CTL       R/W         00000000        Power-saving features control
    0x2E            INT_ENABLE      R/W         00000000        Interrupt enable control
    0x2F            INT_MAP         R/W         00000000        Interrupt mapping control
    0x30            INT_SOURCE      R           00000010        Source of interrupts
    0x31            DATA_FORMAT     R/W         00000000        Data format control
    0x32            DATAX0          R           00000000        X-Axis Data 0
    0x33            DATAX1          R           00000000        X-Axis Data 1
    0x34            DATAY0          R           00000000        Y-Axis Data 0
    0x35            DATAY1          R           00000000        Y-Axis Data 1
    0x36            DATAZ0          R           00000000        Z-Axis Data 0
    0x37            DATAZ1          R           00000000        Z-Axis Data 1
    0x38            FIFO_CTL        R/W         00000000        FIFO control
    0x39            FIFO_STATUS     R           00000000        FIFO status 
    */

    typedef struct
    {
        MotorAddress addr;
    	int16 counter;
    	int index;
        int calibrationSteps;
        float stepSpeed;
        float lineLength;
        float nextLineLength;
        float deltaL;
    } MotorData;

    extern MotorData motorDat[4];

    void motorCommand(MotorAddress addr,uint8 cmd,uint32 arg);

    void motorSetSpeed(MotorAddress addr,float targetVelocity);
    void motorSetPosition(MotorAddress addr,int targetPosition);
    void motorSafeStartExit(MotorAddress addr);
    void motorEnergize(MotorAddress addr);
    void motorDeenergize(MotorAddress addr);
    void accelerometerRead(uint8* result);


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
*/
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
/*
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
#endif