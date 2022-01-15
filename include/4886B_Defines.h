#define TicksPerSecond (Msec_TO_sec / tickSpeed)
#define DRIVE_KP 15
#define STEERING_KP 3
#define ENC_TO_DRIVE_WHEEL ((float)3/7)
#define GyroMarginOfRollOver 300
#define wheelToWheelDistance 12.5
#define TORQUE_ROTATION_PER_TICK 10

float stopDist(float vel, float accel); 
void driveStraight(float dist, float maxVel, float accel); 

void driveForward(int dist, float maxVel, float accel);
void driveReverse(int dist, float maxVel, float accel);

void mogoPID();
bool ToggleBool(bool toggled);
void Drive(int left, int right);
int GyroAbsPos();
void driveTurn(float radians, float outerRadius, float vel, float accel, bool reversed = false);
void GraphDebuggerVars(int Red, int Blue = 0, int Green = 0, int Purple = 0, int Orange = 0, int Yellow = 0);

#define MOGO_UP 0
#define MOGO_HOLD -550
#define MOGO_DOWN -970  

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
