#define TicksPerSecond (Msec_TO_sec / tickSpeed)
#define DRIVE_KP 3
#define STEERING_KP 4
#define ENC_TO_DRIVE_WHEEL ((float)3/7)
#define GyroMarginOfRollOver 300
#define wheelToWheelDistance 12.5
#define TORQUE_ROTATION_PER_TICK 10

#define AWPlineAuton 0
#define PlatformAuton 1
#define NeutralAuton 2
#define FullAWP 3
#define CenterRingsAuton 4
#define DebugAuton 5
#define SkillsAuton 6
#define LeastAuton AWPlineAuton
#define GreatestAuton SkillsAuton

#define BLUE_SIDE 1
#define NEUTRAL_SIDE 0
#define RED_SIDE -1



void BallsToTheWalls(float dist);

float stopDist(float vel, float accel); 
void driveStraight(float dist, float maxVel, float accel); 

#define DEADBAND 50
void fourPID();
bool ToggleBool(bool toggled);
void Drive(int left, int right);
int GyroAbsPos();
void driveTurn(float radians, float outerRadius, float vel, float accel, bool reversed = false);
void GraphDebuggerVars(int Red, int Blue = 0, int Green = 0, int Purple = 0, int Orange = 0, int Yellow = 0);
void AutonMogo(int pos, int duration);
void AutonLift(int pos, int duration);
#define MOGO_KP 4
#define MOGO_UP 313

#define FOUR290 290
#define FOURPLAT 260
#define MOGO_HOLD 193
#define MOGO_DOWN 100
#define MOGO_HOVER 150

#define pissopen clawnoid.set(false);
#define pissclose clawnoid.set(true);

#define FOUR_KP 3
#define FOUR_AWP 250
#define FOUR_DOWN 197
#define FOUR_MID 250
#define FOUR_UP 300
#define FOUR_HOVER 210


#define quadtile 96
#define tripletile 72
#define doubletile 48
#define fullplushalf 36
#define fulltile 24
#define halftile 12
#define quartertile 6 
#define eigthtile 3 

#define Nquadtile -96
#define Ntripletile -72
#define Ndoubletile -48
#define Nfullplushalf -36
#define Nfulltile -24
#define Nhalftile -12
#define Nquartertile -6 
#define Neigthtile -3 
