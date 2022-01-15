using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor frontLeft;
extern motor frontRight;
extern motor backLeft;
extern motor backRight;
extern motor plat2;
extern motor plat1;
extern digital_out solenoid;
extern controller Controller1;
extern inertial beefro;
extern motor SoleMogo;
extern motor intake;
extern pot leftPot;
extern pot rightPot;
extern sonar Range;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );