#define STEP_SCALE 100
#define PI 3.1415927
#define SPOOL_RADIUS 1

typedef enum
{ 
	Motor0 		= 	10,
	Motor1 		= 	11,
	Motor2 		= 	12,
	Motor3 		= 	13,
} MotorAddress;

typedef struct
{
	int counter;
	int index;
} MotorPositions;

extern MotorPositions motorPos[4];

void motorSetSpeed(MotorAddress MA,int targetVelocity);
void motorSetPosition(MotorAddress MA,int targetPosition);
void motorSafeStartExit(MotorAddress MA);
void motorEnergize(MotorAddress MA);


	