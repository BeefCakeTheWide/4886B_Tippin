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
// frontLeft            motor         7               
// frontRight           motor         3               
// backLeft             motor         5               
// backRight            motor         1               
// Controller1          controller                    
// beefro               inertial      11              
// intake               motor         10              
// LiftPot              potV2         A               
// leftMid              motor         6               
// midRight             motor         2               
// platters             motor         9               
// clawnoid             digital_out   E               
// backclamp            digital_out   F               
// backtilt             digital_out   G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "4886B_Defines.h" 
#include "v5standarddefines.h"
#include "vex.h"
#include <cmath>
using namespace vex;
motor_group leftDrive(frontLeft, backLeft, leftMid);
motor_group rightDrive(frontRight, backRight, midRight);

motor_group fullDrive(frontLeft, backLeft, frontRight, backRight);
competition Competition;

///////VARIABLES T/F   ///////////////////////
bool driveSlowToggled;
bool intakeToggled;
bool buttonPressed;
bool liftUpTOG;
bool pistonToggle;
bool clampToggle;
bool tiltToggle;

float currentHeading = 0;

int driveReversed = 1;
int dir;
int autonSelect = 0;
int autonMin = 0;
int autonMax = 10;

   

/* Beginning of Auto select code(orginal) */
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
  Brain.Screen.printAt(300, 50, "0 = NO AUTON");
  Brain.Screen.printAt(300, 60, "1 = L'NEUTER");
  Brain.Screen.printAt(300, 70, "2 = FAWP");
  Brain.Screen.printAt(300, 80, "3 = LAWP");
  Brain.Screen.printAt(300, 90, "4 = RAWP");
  Brain.Screen.printAt(300, 100, "5 = R'NEUTER");
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
/* end of our orginal auto select */


/* beginning of leif and tates' gui code */
void drawHomeFieldLines();
void drawRingles();
void drawMogo(int, int, int);
void drawPlatform(int);

int AutonSide = 1, AutonSelect = 0;
void TateLeifAutonGui()
{
  while(true)
  {
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.clearScreen();
    Brain.Screen.setPenWidth(2);
    Brain.Screen.setPenColor(green);
    Brain.Screen.drawRectangle(120,0,360,240);  // a line for the field outline
    Brain.Screen.drawLine(0, 100, 120, 100);
    drawHomeFieldLines();
    drawRingles();
    drawMogo(300, 60, 0);
    drawMogo(210, 60, 0);
    drawMogo(390, 60, 0);
    drawPlatform(AutonSide);
    drawMogo(450, 150, AutonSide);
    drawMogo(235, 210, AutonSide);
    Brain.Screen.setPenColor(white);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Change Auton");
    //Display which autonomous program will be run
    Brain.Screen.setPenColor(green);
    switch(AutonSelect)
    {
      case AWPlineAuton:
        Brain.Screen.drawLine(390, 200, 390, 60);
        Brain.Screen.drawLine(390, 60, 400, 150);
        Brain.Screen.drawLine(400, 150, 450, 150);
        Brain.Screen.drawLine(450, 150, 420, 60);
        Brain.Screen.drawLine(420, 60, 420, 180);
        break;
      case PlatformAuton:
        Brain.Screen.drawLine(200, 200, 210, 60);
        Brain.Screen.drawLine(210, 60, 230, 200);
        Brain.Screen.drawLine(230, 200, 150, 200);
        break;
      case NeutralAuton:
        Brain.Screen.drawLine(390, 200, 390, 60);
        Brain.Screen.drawLine(390, 60, 340, 80);
        Brain.Screen.drawLine(340, 80, 300, 60);
        Brain.Screen.drawLine(300, 60, 420, 180);
        break;
      case FullAWP:
        Brain.Screen.drawLine(200, 200, 200, 150);
        Brain.Screen.drawLine(200, 150, 450, 150);
        Brain.Screen.drawLine(450, 150, 420, 60);
        Brain.Screen.drawLine(420, 60, 420, 180);
        break;
      case CenterRingsAuton:
        Brain.Screen.drawLine(390, 200, 300, 60);
        Brain.Screen.drawLine(300, 60, 450, 150);
        Brain.Screen.drawLine(450, 150, 420, 60);
        Brain.Screen.drawLine(420, 60, 420, 180);
        break;
      case DebugAuton:
        Brain.Screen.setCursor(5, 29);
        Brain.Screen.print("Debug");
        break;
      case SkillsAuton:
      Brain.Screen.setCursor(5, 29);
        Brain.Screen.print("Skills");
        break;
      default:
      Brain.Screen.setCursor(5, 29);
        Brain.Screen.print("Error");
    }
    Brain.Screen.setPenColor(white);
    Brain.Screen.setCursor(6, 1);
    Brain.Screen.print("Change Side");

    if(Brain.Screen.pressing()) //upon touching the screen
    {
      if(Brain.Screen.xPosition() < 120) //if the touch is on the left side
      {
        if (Brain.Screen.yPosition() < 100)
        {
          //cycle through autonomus programs
          if(AutonSelect  >= GreatestAuton) AutonSelect = LeastAuton;
          else AutonSelect ++;
        }
        else
        {
          AutonSide *= -1;
        }
        while(Brain.Screen.pressing()){}
      }
      //if on the right side, exit. AutonSelect is now locked in.
      else return;
    }
    wait(20, msec);
  }
}
void drawMogo(int xcent, int ycent, int side)
{
  if (side == RED_SIDE)
  {
    Brain.Screen.setFillColor(red);
    Brain.Screen.setPenColor(red);
  }
  else if (side == BLUE_SIDE)
  {
    Brain.Screen.setFillColor(blue);
    Brain.Screen.setPenColor(blue);
  }
  else
  {
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.setPenColor(yellow);
  }
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawCircle(xcent, ycent, 15);
}
void drawPlatform(int side)
{
  if (side == RED_SIDE) Brain.Screen.setPenColor(red);
  else Brain.Screen.setPenColor(blue);
  Brain.Screen.setPenWidth(6);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.drawRectangle(250,180,100,50);
  Brain.Screen.setPenWidth(2);
}
void drawHomeFieldLines()
{
  Brain.Screen.setPenColor(white);
  Brain.Screen.setPenWidth(2);
  Brain.Screen.drawLine(120,120,480,120);
  Brain.Screen.drawLine(420,120,480,180);
}
void drawRingle(int xcent, int ycent)   
{ 
  Brain.Screen.setFillColor(transparent);      
  Brain.Screen.setPenColor(purple);  
  Brain.Screen.setPenWidth(2);      
  Brain.Screen.drawCircle(xcent, ycent, 3);
}
void drawRingleStar (int xcent, int ycent)
{
  drawRingle(xcent-7, ycent);
  drawRingle(xcent+7, ycent);
  drawRingle(xcent, ycent+7);
  drawRingle(xcent, ycent-7);
}
void drawRingles(void)
{  /* the Left L of ringles */
  drawRingle(130,60);
  drawRingle(147,60);
  drawRingle(163,60);
  drawRingle(180,60);
  drawRingle(180,45);
  drawRingle(180,30);
  drawRingle(180,15);
  drawRingle(180,0);
  /* six ringles in the middle */
  drawRingle(240,60);
  drawRingle(255,60);
  drawRingle(270,60);
  drawRingle(330,60);
  drawRingle(345,60);
  drawRingle(360,60);
  /* the right :L of ringles */
  drawRingle(470,60);
  drawRingle(453,60);
  drawRingle(437,60);
  drawRingle(420,60);
  drawRingle(420,75);
  drawRingle(420,90);
  drawRingle(420,105);
  drawRingle(420,120); 
  drawRingleStar(240,120);
  drawRingleStar(300,120);
}

/* end of leif and tate's gui code*/

void pre_auton(void) {
  clawnoid.set(false);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  platters.setPosition(0, degrees);
  beefro.calibrate();
  //TateLeifAutonGui();
  AutonGUI();
  Brain.Screen.pressed(selectAuton);
}

///////////AUTONOMOUS FUCNTIONS///////////////////
int mogoTarg = MOGO_UP;
int fourTarg = FOURPLAT;

//ALL OF THE AUTONOMOUS PROGRAMS ARE CONTAINED HERE
void autonomous(void) {
  clawnoid.set(true);
  Brain.Screen.clearScreen();

  switch (autonSelect) {
  
  //No autonomous
  case 0: 
  break;

  //Left side ringle(0-30 points)
  case 1:
   backtilt.set(true); //Bring tilter down
   wait(500, msec); //Wait 1/2 a second
   driveStraight(-10, 40, 50); //Drive 10 inches back
   backclamp.set(true); //Close the clamp
   wait(250,msec); //Wait 1/4 of a second
   backtilt.set(false); //Bring the tilter up
   intake.spin(reverse,600,rpm); //Activate the intake 
   driveStraight(30, 25, 30); //Drive 30 inches forward
   driveStraight(-25, 25, 30); //Drive 25 inches back
   driveStraight(25, 25, 30); //Drive 25 inches forward
   driveStraight(-25, 25, 30); // "   "
   driveStraight(25, 25, 30);  // "   "
   driveStraight(-25, 25, 30); // "   "
   driveStraight(25, 25, 30);  // "   "
   driveStraight(-25, 25, 30); // "   "
  break;

  // AWP AUTON
  case 2:
    
    driveTurn(-pi/4, wheelToWheelDistance, 25, 25);


  break;

  case 3:
  driveStraight(70,50,50);

  break;

  // RIGHT AUTON QIN POIGT
  case 4:
  AutonMogo(MOGO_DOWN, 1300);
  driveStraight(-15, 20, 40);
  AutonMogo(MOGO_HOLD, 600);
  fourTarg = FOUR_MID;
  driveTurn(pi, 13.2, 40, 50);
  intake.spin(forward, 600, rpm);
  driveStraight(50, 20, 30);
  //driveStraight(-20, 40, 50);
  driveTurn(2*pi, wheelToWheelDistance/2, 20, 35);
  driveStraight(70, 20, 30);
  AutonMogo(MOGO_HOVER, 3000);
  
  break;

  case 5:
  driveTurn(-pi/2, wheelToWheelDistance/2, 10, 10, true);
  break;

  case 6:
  
  AutonMogo(MOGO_DOWN, 1300);
  driveStraight(-15, 20, 40);
  AutonMogo(MOGO_HOLD, 600);
  fourTarg = FOUR290;
  intake.spin(forward, 600, rpm);
  driveStraight(37,15,30);
  driveStraight(-20, 15, 30);
  driveStraight(20, 15, 30);
  driveStraight(-20, 15, 30);
  intake.stop(coast);
  fourTarg = FOUR_DOWN;
  driveTurn(1.85, wheelToWheelDistance, 30, 50);
  pissopen
  driveStraight(55, 54, 54);
  pissclose
  wait(200, msec);
  fourTarg = FOUR_UP;
  driveTurn(2.1, wheelToWheelDistance, 30, 35);
  driveStraight(50, 54, 54);
  AutonLift(FOURPLAT,700);  
  pissopen
  driveStraight(-12, 30, 35);
  fourTarg = FOUR_DOWN;
  driveTurn(2.1 - pi/2, wheelToWheelDistance/2, 20, 20);
  
  
  AutonMogo(MOGO_DOWN, 1300);
  driveStraight(30,25,30);
  driveTurn(pi, wheelToWheelDistance/2, 25, 25);
  driveStraight(34, 30, 35);
  pissclose
  AutonLift(FOUR290, 1300);
  driveTurn(pi-pi/4,wheelToWheelDistance/2,20,20);
  driveStraight(4, 25, 25);
  fourTarg = FOURPLAT;
  pissopen
  driveStraight(-4, 25, 25);


  break;

  case 7:
  pissopen
  driveStraight(44.5,54,54);
  pissclose
  mogoTarg = MOGO_DOWN;
  driveStraight(-24,54,54);
  driveTurn(-3*pi/4,wheelToWheelDistance, 20, 20, true);
  //AutonMogo(MOGO_DOWN, 1000);
  driveStraight(-40,50,50);
  mogoTarg = MOGO_HOVER;
  driveStraight(40,54,54);

  break;
  }
}



int lpow, rpow;

//Usercontrol contains all */
void usercontrol(void) {

  
  
  mogoTarg = MOGO_DOWN;
 

  int ringspeed = 550;
  driveSlowToggled = false;

  buttonPressed = false;
  pistonToggle = false;
  clampToggle = false;
  tiltToggle = false;

  bool slowtogg = false;
  bool slowbuttonOn = false;
  clawnoid.set(true);
  while (1) {

    /// DRIVE CODE STARTS HERE ///

  if (AButton) {
    if (!slowbuttonOn) {
      if(slowtogg) {
        slowtogg = false;
      } else {
        slowtogg = true;
      }
      slowbuttonOn = true;
    }
  } else {
    slowbuttonOn= false;
  }

  lpow = (LStickUpDown + (LStickLeftRight)/2)*6;
  rpow = (LStickUpDown - (LStickLeftRight)/2)*6;

  if (slowtogg) {
    lpow /= 3;
    rpow /= 3;
  }

  if (lpow < DEADBAND && lpow > -DEADBAND) lpow = 0;
  if (rpow < DEADBAND && rpow > -DEADBAND) rpow = 0;

  if (RStickUpDown > 60 ) {
    leftDrive.setStopping(hold);
    rightDrive.setStopping(hold);
  } else {
    leftDrive.setStopping(coast);
    rightDrive.setStopping(coast);
  }

    /// RING SIDE MOGO LIFTER ///
    if (L1Button && !R1Button) {
      mogoTarg = MOGO_HOLD;
      
    } else if (L2Button && !R2Button) {
      mogoTarg = MOGO_DOWN;
    } else {
      //SoleMogo.stop(brake);
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
    if (YButton) {
      intake.spin(forward, ringspeed, rpm);
    } else if (XButton) {
      intake.spin(reverse, ringspeed, rpm);
    } else {
      intake.stop(coast);
    }
    /// PNEUMATIC CONTROL ///
    if (BButton) {
      if (!pistonToggle) {
        clawnoid.set(ToggleBool(clawnoid.value()));
        pistonToggle = true;
      }
    } else {
      pistonToggle = false;
    }
   
   if ( RightButton) {
     if (!clampToggle) {
       backclamp.set(ToggleBool(backclamp.value()));
      clampToggle=true;
     }
     
   } else {
     clampToggle = false;
   }

    
   if (DownButton) {
     if (!tiltToggle) {
       backtilt.set(ToggleBool(backtilt.value()));
       tiltToggle = true;
     }
     
   } else {
     tiltToggle = false;
   }
   

    Drive(lpow, rpow);
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print(LiftPot.angle(degrees));
    //Drive(lpow, rpow);
    wait(20, msec);
  }

}

//Main does not need anything added to it
int main() {

  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
 

  while (true) {
    wait(100, msec);
  }
}

/*
Below this point are the Prototypes 
They need to remain below int main()
*/

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

      
      fourPID();
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

      
      fourPID();
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

      
      fourPID();
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
      
      fourPID();
      currentTimer += tickSpeed; // wait until tickSpeed milliseconds have
                                 // passed since last iteration of while loop
      while (VexTimer < currentTimer) {
      }
    }
  }
  Drive(0, 0);
  currentHeading = radians * RAD_TO_DEG;
}

void fourPID() {
  

  platters.spin(forward, (fourTarg + LiftPot.angle(degrees))*FOUR_KP, rpm);

  
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

void AutonMogo(int pos, int duration)
{
  mogoTarg = pos; //set mogoTarg
  for(int i = 0; i < duration / FiftiethSecondTick; i ++)
      {
       //while the duration hasn't been reached, call mogoPID and wait
        wait(FiftiethSecondTick, msec);
      }
}

void AutonLift(int pos, int duration)
{
  fourTarg = pos; //set mogoTarg
  for(int i = 0; i < duration / FiftiethSecondTick; i ++)
      {
        fourPID(); //while the duration hasn't been reached, call mogoPID and wait
        wait(FiftiethSecondTick, msec);
      }
}


//////.  BALLS TO THE WALLS (SERIOUS SHIT).  //////////

void BallsToTheWalls(float dist) {
  leftDrive.setVelocity(600, rpm);
  rightDrive.setVelocity(600, rpm);
  float lpos = 0,rpos = 0, targpos = 0;
  float lStart = leftDrive.position(turns);
  float rStart = rightDrive.position(turns);

  while (targpos < dist) { 
    lpos = (leftDrive.position(turns) - lStart) * ENC_TO_DRIVE_WHEEL * LargeWheel_Circumfrence;
    rpos = (rightDrive.position(turns) - rStart) * ENC_TO_DRIVE_WHEEL * LargeWheel_Circumfrence;
  }

  

}