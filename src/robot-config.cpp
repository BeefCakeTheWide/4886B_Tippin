#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor frontLeft = motor(PORT1, ratio6_1, true);
motor frontRight = motor(PORT2, ratio6_1, false);
motor backLeft = motor(PORT3, ratio6_1, true);
motor backRight = motor(PORT4, ratio6_1, false);
motor plat2 = motor(PORT6, ratio18_1, true);
motor plat1 = motor(PORT5, ratio36_1, false);
digital_out solenoid = digital_out(Brain.ThreeWirePort.H);
controller Controller1 = controller(primary);
inertial beefro = inertial(PORT10);
motor SoleMogo = motor(PORT8, ratio36_1, true);
motor intake = motor(PORT9, ratio6_1, true);
pot leftPot = pot(Brain.ThreeWirePort.A);
pot rightPot = pot(Brain.ThreeWirePort.B);
sonar Range = sonar(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}