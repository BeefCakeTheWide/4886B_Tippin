using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern controller Controller1;
extern inertial beefro;
extern motor intake;
extern potV2 LiftPot;
extern motor leftMid;
extern motor midRight;
extern motor platters;
extern digital_out clawnoid;
extern digital_out backclamp;
extern digital_out backtilt;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );