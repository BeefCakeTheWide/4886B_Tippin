#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor frontLeft = motor(PORT7, ratio6_1, true);
motor frontRight = motor(PORT3, ratio6_1, false);
motor backLeft = motor(PORT5, ratio6_1, true);
motor backRight = motor(PORT1, ratio6_1, false);
controller Controller1 = controller(primary);
inertial beefro = inertial(PORT11);
motor intake = motor(PORT10, ratio6_1, true);
potV2 LiftPot = potV2(Brain.ThreeWirePort.A);
motor leftMid = motor(PORT6, ratio6_1, true);
motor midRight = motor(PORT2, ratio6_1, false);
motor platters = motor(PORT9, ratio36_1, false);
digital_out clawnoid = digital_out(Brain.ThreeWirePort.E);
digital_out backclamp = digital_out(Brain.ThreeWirePort.F);
digital_out backtilt = digital_out(Brain.ThreeWirePort.G);

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