/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Charlie Van Hook                                          */
/*    Created:      Tue Sep 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "v-drive.h"
#include "position.h"

using namespace vex;


competition Competition;

//enable code
bool RemoteControlCodeEnabled = true;
bool DrivetrainNeedsToBeStopped = true;
bool tgtMotorStopped = true;
bool tgt2MotorStopped = true;
bool turnTableStopped = true;
bool intakeStopped = true;

vDrive vDrivetrain;//Drivetrain Class

//Is the vision thread running
bool visionActive = true;

//input type(might be removed)
bool inputype = true;

//Position 3D Variables
bool positionActive = true;
robotPosition position;//Watch out

//Calibrate intake
void intakeCalibrate(){
  while(!intakeSwitch.pressing()){
    intake.spin(vex::forward, 80, percent);
  }
  intake.stop();
}

void tgtCalibrate(){
  bool trigger1 = true, trigger2 = true;
  while(!tgt2Switch.pressing() && !tgtSwitch.pressing()){
    if(tgt2Switch.pressing()&&trigger1){
      tgt2.spinFor(vex::forward, 50, degrees);
      tgt2.stop(hold);
      trigger1 = !trigger1;
    }else if(!trigger1){

    }else{
      tgt2.spin(vex::reverse, 50, percent);
    }
    if(tgtSwitch.pressing()&&trigger2){
      tgt.spinFor(vex::reverse, 50, degrees);
      tgt.stop(hold);
      trigger2 = !trigger2;
    }else if(!trigger2){

    }else{
      tgt.spin(vex::forward, 50, percent);
    }
  }
}

int positionCallback() {
  while (positionActive) {
    if(DrivetrainNeedsToBeStopped){
      position.resetV();
    }
    position.updatePos();
    con.Screen.print ("X: %f, Y: %f, Z %f", position.getXPos(), position.getYPos(), position.getZPos());
    this_thread::sleep_for(20);
  }
  return 0;
}

int visionThreadCallback() {
  while (visionActive) {
    this_thread::sleep_for(20);
  }
  return 0;
}

int visionTaskCallback() {
  while (visionActive) {
    wait(20, msec);
  }
  return 0;
}

void pre_auton(void){
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

//Use Compass for drivetrain movement
void autonomous(void){
  vDrivetrain.move("north");
  wait(2000, msec);
  vDrivetrain.pause();
}

/* Field Oriented Control
// Get gyro angle in radians

        // rotate coordinate system
        temp  = forward * cos(theta) - right * sin(theta);
        right = forward * sin(theta) + right * cos(theta);
        forward = temp;
*/

//DO NOT CHANGE (unless nessisary)
void usercontrol(void){
  tgt.setVelocity(50, percent);//Adjust for arm speed
  tgt2.setVelocity(50, percent);
  tgtCalibrate();
  turnTable.setVelocity(50, percent);
  intake.setVelocity(100, percent);
  int toggleVariable = 0;
  int leftAngle = 10, rightAngle = 10;
  con.Screen.clearScreen();
  while(true){
  if(RemoteControlCodeEnabled) {
      int drivetrainLeftSideSpeed = con.Axis3.position()/abs(con.Axis3.position())*(abs(con.Axis3.position()) + abs(con.Axis4.position()));
      int drivetrainRightSideSpeed = con.Axis3.position()/abs(con.Axis3.position())*(abs(con.Axis3.position()) + abs(con.Axis4.position()));
      int drivetrainStraifeSpeed = con.Axis4.position();
      int drivetrainTurnSpeed = con.Axis1.position();
      
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5 && abs(drivetrainTurnSpeed) < 5 && abs(drivetrainStraifeSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped) {
          // stop the drive motors
          MechnumWheelsMotorA.stop();
          MechnumWheelsMotorB.stop();
          OmniWheel.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped = false;
        }
      } else {
        DrivetrainNeedsToBeStopped = true;
        if(abs(drivetrainLeftSideSpeed) < 5) drivetrainLeftSideSpeed = 0;
        if(abs(drivetrainRightSideSpeed) < 5) drivetrainRightSideSpeed = 0;
        if(abs(drivetrainStraifeSpeed) < 5) drivetrainStraifeSpeed = 0;
        if(abs(drivetrainTurnSpeed) < 5) drivetrainTurnSpeed = 0;
      }
      if(inputype){//Change this already IDIOT (done)
      if (con.ButtonR1.pressing()) {
        if(leftAngle<440){
          tgt.spinFor(vex::reverse, 20, degrees);
          tgtMotorStopped = false;
          leftAngle += 20;
        }
      } else if (!tgtMotorStopped){
        tgt.stop(hold);
        tgtMotorStopped = true;
      }else if(con.ButtonR2.pressing()){
        if(leftAngle>50){
          tgt.spinFor(vex::forward, 20, degrees);
          tgtMotorStopped = false;
          leftAngle -= 20;
        }
      }
      if (con.ButtonL1.pressing()) {
        if(rightAngle<480){
          tgt2.spinFor(vex::forward, 20, degrees);
          tgt2MotorStopped = false;
          rightAngle += 20;
        }
      } else if (!tgt2MotorStopped){
        tgt2.stop(hold);
        tgt2MotorStopped = true;
      }else if(con.ButtonL2.pressing()){
        if(rightAngle>50){
          tgt2.spinFor(vex::reverse, 20, degrees);
          tgt2MotorStopped = false;
          rightAngle -= 20;
        }
      }
      }else{
        if (con.ButtonL1.pressing()) {
          turnTable.spin(vex::forward);
          turnTableStopped = false;
        }else if(con.ButtonL2.pressing()){
          turnTable.spin(reverse);
          turnTableStopped = false;
        }else if (!turnTableStopped){
          turnTable.stop(hold);
          turnTableStopped = true;
        }
        if (con.ButtonR1.pressing()) {
          intake.spin(vex::forward);
          intakeStopped = false;
        }else if (con.ButtonR2.pressing()){
          intake.spin(reverse);
          intakeStopped = false;
        }else if (!intakeStopped){
          intake.stop();
          intakeStopped = true;
        }
      }
      if ((con.ButtonA.pressing()) && (toggleVariable == 0)){
        wait(150, msec);
        toggleVariable = 1;
        inputype = !inputype;
      }if ((con.ButtonA.pressing()) && (toggleVariable == 1)){
        wait(150, msec);
        toggleVariable = 0;
      }
      /*if ((con.ButtonB.pressing()) && (toggleVariable == 0)){
        wait(150, msec);
        toggleVariable = 1;
        visionActive = !visionActive;
      }if ((con.ButtonB.pressing()) && (toggleVariable == 1)){
        wait(150, msec);
        toggleVariable = 0;
      }*/
      if (DrivetrainNeedsToBeStopped) {
        MechnumWheelsMotorA.setVelocity(drivetrainLeftSideSpeed, percent);
        MechnumWheelsMotorA.spin(vex::forward);
        MechnumWheelsMotorB.setVelocity(drivetrainRightSideSpeed, percent);
        MechnumWheelsMotorB.spin(vex::forward);
        OmniWheel.setVelocity(drivetrainStraifeSpeed, percent);
        OmniWheel.spin(vex::forward);
        if(abs(drivetrainTurnSpeed)>0){
          MechnumWheelsMotorA.setVelocity(drivetrainTurnSpeed, percent);
          MechnumWheelsMotorA.spin(reverse);
          MechnumWheelsMotorB.setVelocity(drivetrainTurnSpeed, percent);
          MechnumWheelsMotorB.spin(vex::forward);
          OmniWheel.setVelocity(drivetrainTurnSpeed, percent);
          OmniWheel.spin(reverse);
        }
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  vexcodeInit();
  //position.calibrate();
  //intakeCalibrate();

  pre_auton();

  while (true){
    wait(100, msec);
  }
}

