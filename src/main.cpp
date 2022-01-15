// /*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontLeft            motor         1
// frontRight           motor         2
// backLeft             motor         3
// backRight            motor         4
// plat2                motor         6
// plat1                motor         5
// solenoid             digital_out   H
// Controller1          controller
// beefro               inertial      10
// SoleMogo             motor         8
// intake               motor         9
// leftPot              pot           A
// rightPot             pot           B
// Range                sonar         C, D
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "4886B_Defines.h"
#include "v5standarddefines.h"
#include "vex.h"
using namespace vex;
motor_group leftDrive(frontLeft, backLeft);
motor_group rightDrive(frontRight, backRight);
motor_group platters(plat1, plat2);

motor_group fullDrive(frontLeft, backLeft, frontRight, backRight);
// A global instance of competition
competition Competition;

///////VARIABLES T/F   ///////////////////////
bool driveSlowToggled;
bool intakeToggled;
bool buttonPressed;
bool pistonToggle;
float currentHeading = 0;

int driveReversed = 1;
int dir;
int autonSelect = 0;
int autonMin = 0;
int autonMax = 4;

// Auton Select Functions and Routine
void AutonGUI() {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Determine the correct Auton");
  Brain.Screen.printAt(1, 200, "Chosen Auton: %d", autonSelect);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(20, 50, 100, 100);
  Brain.Screen.printAt(25, 75, "SELECT");
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawRectangle(170, 50, 100, 100);
  Brain.Screen.printAt(175, 75, "CONFIRM");
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(280, -10, 10, 400);

  Brain.Screen.setFillColor(black);
  Brain.Screen.printAt(300, 45, "0 = NO AUTON");
  Brain.Screen.printAt(300, 55, "1 = Left Neutral");
  Brain.Screen.printAt(300, 65, "2 = right Neutral");
  Brain.Screen.printAt(300, 75, "3 = AWP AUTON");
  Brain.Screen.printAt(300, 85, "4 = PLATFORM STACK");
}

void selectAuton() {
  bool selectingAuton = true;
  int x = Brain.Screen
              .xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen
              .yPosition(); // get the y position of last touch of the screen

  if (x >= 20 && x <= 120 && y >= 50 && y <= 150) // select button pressed
  {
    autonSelect++;
    if (autonSelect > autonMax)
      autonSelect = autonMin; // rollover

    Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", autonSelect);
  }
  if (x >= 170 && x <= 270 && y >= 50 && y <= 150) {
    selectingAuton = false; // GO button pressed
    Brain.Screen.printAt(1, 200, "Auton Selected = %d ", autonSelect);
  }
  if (!selectingAuton) {
    Brain.Screen.setFillColor(green);
    Brain.Screen.drawCircle(145, 160, 15);
  } else {
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawCircle(145, 160, 15);
  }
  wait(10, msec); // slow it down
  Brain.Screen.setFillColor(black);
}
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  platters.setPosition(0, degrees);
  beefro.calibrate();
  AutonGUI();
  Brain.Screen.pressed(selectAuton);

  /*---------------------------------------------------------------------------*/
  /*                                                                           */
  /*                              Autonomous Task */
  /*                                                                           */
  /*  This task is used to control your robot during the autonomous phase of */
  /*  a VEX Competition. */
  /*                                                                           */
  /*  You must modify the code to add your own robot specific commands here. */
  /*---------------------------------------------------------------------------*/
}

///////////AUTONOMOUS FUCNTIONS///////////////////
int mogoTarg = MOGO_UP;
void autonomous(void) {
  Brain.Screen.clearScreen();
  switch (autonSelect) {
  // NO AUTON
  case 0:
    break;

  // ONE LEFT NEUTRAL
  case 1:
    solenoid.set(true);           // open the claw
    mogoTarg = MOGO_DOWN;
    driveStraight(doubletile - 2 , 54, 54); // drive 44.5 inches to Neutral
    solenoid.set(false);
    driveStraight(Nfullplushalf - 4, 54, 50);
    solenoid.set(true);
    driveTurn(-pi/3, wheelToWheelDistance, 25, 30, true);
    driveStraight(Nhalftile, 50, 50);
    mogoTarg = MOGO_HOLD;
    driveStraight(halftile, 5, 10);
    intake.spin(forward, 600, rpm);
    break;

  // ONE RIGHT NEUTRAL
  case 2:
    driveTurn(-pi/2, wheelToWheelDistance, 20, 30, true);
    break;

  // AWP AUTON
  case 3:

    break;

  // PLATFORM STACK
  case 4:
    break;
  }
}

void xPressed() { dir *= -1; }

int lpow, rpow;
void usercontrol(void) {

  int ringspeed = 600;
  driveSlowToggled = false;
  buttonPressed = false;
  pistonToggle = false;
  solenoid.set(false);
  while (1) {

    /// DRIVE CODE STARTS HERE ///

    if (driveReversed == 1) {
      lpow = LStickUpDown;
      rpow = RStickUpDown;
    } else {
      lpow = -RStickUpDown;
      rpow = -LStickUpDown;
    }

    lpow *= 6; // MULTIPLIED SPEED FOR LEFT
    rpow *= 6; // MULTIPLIED SPEED FOR RIGHT


    /// THIS IS THE DEADZONE FOR THE JOYSTICKS ///
    if (lpow > 15 && lpow < 15) {
      lpow = 0;
    }
    if (rpow > 15 && rpow < 15) {
      rpow = 0;
    }
    /// THIS REVERSES THE DRIVE ///
    if (XButton) {
      if (!buttonPressed) {
        driveReversed *= -1;
        buttonPressed = true;
      } else {
        buttonPressed = false;
      }
    }
    /// RING SIDE MOGO LIFTER ///
    if (L1Button && !R1Button) {
      SoleMogo.spin(forward, 100, rpm);
    } else if (L2Button && !R2Button) {
      SoleMogo.spin(reverse, 100, rpm);
    } else {
      SoleMogo.stop(brake);
    }
    /// PLATFORM LIFT ///
    if (R1Button && !L1Button) {
      platters.spin(reverse, 200, rpm);
    } else if (R2Button && !L2Button) {
      platters.spin(forward, 200, rpm);
    } else {

      platters.stop(hold);
    }
    /// INTAKE AND CONTINUOUS INTAKE ///
    if (L1Button && R1Button) {
      intake.spin(forward, ringspeed, rpm);
    } else if (L2Button && R2Button) {
      intake.spin(reverse, ringspeed, rpm);
    } else {
      intake.stop(coast);
    }
    /// PNEUMATIC CONTROL ///
    if (BButton) {
      if (!pistonToggle) {
        solenoid.set(ToggleBool(solenoid.value()));
        pistonToggle = true;
      }
    } else {
      pistonToggle = false;
    }
    Controller1.Screen.print(Range);
    Drive(lpow, rpow);
    wait(20, msec);
  }
}

int main() {
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  Controller1.ButtonX.pressed(xPressed);

  while (true) {
    wait(100, msec);
  }
}
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

void Drive(int left, int right) {

  leftDrive.setVelocity(left, rpm);
  rightDrive.setVelocity(right, rpm);
  leftDrive.spin(forward, left, rpm);
  rightDrive.spin(forward, right, rpm);
}
bool ToggleBool(bool toggled) {
  if (toggled == true)
    return false;
  else
    return true;
}
float stopDist(float vel, float accel) { return (vel * vel / (2 * accel)); }

void driveStraight(float dist, float maxVel, float accel) {
  float vel = 0;
  float pos = 0;
  float currLeft;
  float currRight;
  float LeftPosStart = leftDrive.position(turns);
  float RightPosStart = rightDrive.position(turns);
  int tickSpeed = FiftiethSecondTick;
  int currentTimer = VexTimer;
  int ticksPerSec = (Msec_TO_sec / tickSpeed);

  if (dist > 0) {
    while (vel >= 0) {

      GyroAbsPos();
      currLeft = (leftDrive.position(turns) - LeftPosStart) *
                 LargeOmni_Circumfrence * ENC_TO_DRIVE_WHEEL;
      currRight = (rightDrive.position(turns) - RightPosStart) *
                  LargeOmni_Circumfrence *
                  ENC_TO_DRIVE_WHEEL; /// this converts the code into inches
      if (pos + stopDist(vel, accel) >= dist) {
        vel -= accel / ticksPerSec; // decell
      } else if (vel < maxVel) {
        vel += accel / ticksPerSec;
      } else {
        vel = maxVel;
      }
      pos += vel / ticksPerSec;
      Drive(DRIVE_KP * (pos - currLeft) 
                + vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL 
                - STEERING_KP * (GyroAbsPos() - currentHeading), 
            DRIVE_KP * (pos - currRight) 
                + vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL 
                + STEERING_KP * (GyroAbsPos() - currentHeading));

      mogoPID();
      GraphDebuggerVars(vel, pos, currLeft);
      currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                 // passed since last iteration of while loop
      while (VexTimer < currentTimer) {
      }
    }
  } else if (dist < 0) {
    while(vel >= 0){

      GyroAbsPos();
      currLeft = (leftDrive.position(turns) - LeftPosStart) *
                 LargeOmni_Circumfrence * ENC_TO_DRIVE_WHEEL;
      currRight = (rightDrive.position(turns) - RightPosStart) *
                  LargeOmni_Circumfrence *
                  ENC_TO_DRIVE_WHEEL; 
      if(pos - stopDist(vel, accel) <= dist) {
        vel -= accel / ticksPerSec;
      } else if(vel < maxVel) {
        vel += accel / ticksPerSec;
      } else {
        vel = maxVel;
      }
      pos -= vel/ ticksPerSec;
     Drive(DRIVE_KP * (pos - currLeft) 
                - vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL 
                - STEERING_KP * (GyroAbsPos() - currentHeading), 
            DRIVE_KP * (pos - currRight) 
                - vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL 
                + STEERING_KP * (GyroAbsPos() - currentHeading));

      mogoPID();
      GraphDebuggerVars(vel, pos, currLeft);
      currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                 // passed since last iteration of while loop
      while (VexTimer < currentTimer) {
      }

    }
  }

  Drive(0, 0);
}

int GyroRollOvers = 0, PreviousGyro = 0, CurrentGyro;
int GyroAbsPos() {
  CurrentGyro = beefro.orientation(yaw, degrees);
  if (CurrentGyro - PreviousGyro > GyroMarginOfRollOver)
    GyroRollOvers--;
  else if (CurrentGyro - PreviousGyro < -GyroMarginOfRollOver)
    GyroRollOvers++;
  PreviousGyro = CurrentGyro;

  return (CurrentGyro + GyroRollOvers * DegreesPerTurn);
}

void driveTurn(float radians, float outerRadius, float maxVel, float accel,
               bool reversed) {
  int innerRadius = outerRadius - wheelToWheelDistance;
  float radiusRatio = innerRadius / outerRadius;
  float vel = 0;
  float angleLeft;
  float pos = 0;
  float currLeft;
  float currRight;
  float LeftPosStart = leftDrive.position(turns);
  float RightPosStart = rightDrive.position(turns);
  int tickSpeed = FiftiethSecondTick;
  int currentTimer = VexTimer;
  int ticksPerSec = (Msec_TO_sec / tickSpeed);

  if (radians > GyroAbsPos() / RAD_TO_DEG) { // turning right
    while (vel >= 0) {

      angleLeft = radians - GyroAbsPos() / RAD_TO_DEG;
      currLeft = (leftDrive.position(turns) - LeftPosStart) *
                 LargeOmni_Circumfrence * ENC_TO_DRIVE_WHEEL;
      currRight = (rightDrive.position(turns) - RightPosStart) *
                  LargeOmni_Circumfrence *
                  ENC_TO_DRIVE_WHEEL; /// this converts the code into inches
      if (stopDist(vel, accel) >= angleLeft * outerRadius) {
        vel -= accel / ticksPerSec; // decell
      } else if (vel < maxVel) {
        vel += accel / ticksPerSec;
      } else {
        vel = maxVel;
      }
      pos += vel / ticksPerSec;

      if (GyroAbsPos() / RAD_TO_DEG >= radians) {
        break;
      }

      if (!reversed)
        Drive(DRIVE_KP * (pos - currLeft)
                  + vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL,
              DRIVE_KP * (pos * radiusRatio - currRight)
                  + vel * radiusRatio * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL);
      else
        Drive(- DRIVE_KP * (pos * radiusRatio + currLeft)
                  - vel * radiusRatio * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL,
              - DRIVE_KP * (pos + currRight)
                  -vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL);

      mogoPID();
      currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                 // passed since last iteration of while loop
      while (VexTimer < currentTimer) {
      }
    }
  } else if (radians < GyroAbsPos() / RAD_TO_DEG) {
    while (vel >= 0) {

      angleLeft = GyroAbsPos() / RAD_TO_DEG - radians;
      currLeft = (leftDrive.position(turns) - LeftPosStart) *
                 LargeOmni_Circumfrence * ENC_TO_DRIVE_WHEEL;
      currRight = (rightDrive.position(turns) - RightPosStart) *
                  LargeOmni_Circumfrence *
                  ENC_TO_DRIVE_WHEEL; /// this converts the code into inches
      if (stopDist(vel, accel) >= angleLeft * outerRadius) {
        vel -= accel / ticksPerSec; // decell
      } else if (vel < maxVel) {
        vel += accel / ticksPerSec;
      } else {
        vel = maxVel;
      }
      pos += vel / ticksPerSec;

      if (GyroAbsPos() / RAD_TO_DEG <= radians) {
        break;
      }
      if (!reversed)
        Drive(DRIVE_KP * (pos * radiusRatio - currLeft)
                  + vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL,
              DRIVE_KP * (pos - currRight)
                  + vel * radiusRatio * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL);
      else
        Drive(- DRIVE_KP * (pos + currLeft)
                  - vel * LargeOmni_InPerSec_TO_RPM / ENC_TO_DRIVE_WHEEL,
              - DRIVE_KP * (pos * radiusRatio + currRight)
                  - vel * radiusRatio * LargeOmni_Circumfrence / ENC_TO_DRIVE_WHEEL);
      GraphDebuggerVars(vel, stopDist(vel, accel), angleLeft * outerRadius, -GyroAbsPos(), -radians * RAD_TO_DEG);
      mogoPID();
      currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                 // passed since last iteration of while loop
      while (VexTimer < currentTimer) {
      }
    }
  }
  Drive(0, 0);
  currentHeading = radians * RAD_TO_DEG;
}

void mogoPID() {

  SoleMogo.spin(forward, mogoTarg - SoleMogo.position(degrees), rpm);
}

//graph variables on the brain screen. Call in a while loop.
//each iteration draws 1 pixel per color, up to 6 colors. No numeric values graphed
//good for comparing several different values as they change over time
int xcursor = 0;
void GraphDebuggerVars(int Red, int Blue, int Green, int Purple, int Orange, int Yellow)
{
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawPixel(xcursor, Red);
  Brain.Screen.setPenColor(blue);
  Brain.Screen.drawPixel(xcursor, Blue);
  Brain.Screen.setPenColor(green);
  Brain.Screen.drawPixel(xcursor, Green);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.drawPixel(xcursor, Purple);
  Brain.Screen.setPenColor(orange);
  Brain.Screen.drawPixel(xcursor, Orange);
  Brain.Screen.setPenColor(yellow);
  Brain.Screen.drawPixel(xcursor, Yellow);
  xcursor ++; //auto increment x cursor.
}
