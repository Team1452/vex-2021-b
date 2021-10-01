/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vanho                                            */
/*    Created:      Tue Sep 14 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "v-drive.cpp"

using namespace vex;

class vDrive {
  public:
    void move(std::string dir);
    //void rotate(int degree);
    void pause(){
      MechnumWheelsMotorA.stop();
      MechnumWheelsMotorB.stop();
      OmniWheel.stop();
    }
};

void rotate(int degree){
  int turnVelocity = 50;
  MechnumWheelsMotorA.setVelocity(turnVelocity, percent);
  MechnumWheelsMotorB.setVelocity(turnVelocity, percent);
  OmniWheel.setVelocity(turnVelocity, percent);
  if(Inertial6.rotation(degrees)-degree>=5){//turn right
    MechnumWheelsMotorA.spin(reverse);
    MechnumWheelsMotorB.spin(reverse);
    OmniWheel.spin(reverse);
  }
  else if(Inertial6.rotation(degrees)-degree<=-5){//turn left
    MechnumWheelsMotorA.spin(forward);
    MechnumWheelsMotorB.spin(forward);
    OmniWheel.spin(forward);
  }
}

void vDrive::move(std::string dir) {
  int drivetrainLeftSideSpeed = 0, drivetrainRightSideSpeed = 0, drivetrainStraifeSpeed = 0;
  if(dir=="north"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = 0;
  }else if(dir=="west"){
    drivetrainLeftSideSpeed = 0;
    drivetrainRightSideSpeed = 0;
    drivetrainStraifeSpeed = -1;
  }else if(dir=="east"){
    drivetrainLeftSideSpeed = 0;
    drivetrainRightSideSpeed = 0;
    drivetrainStraifeSpeed = 1;
  }else if(dir=="south"){
    drivetrainLeftSideSpeed = -1;
    drivetrainRightSideSpeed = 1;
    drivetrainStraifeSpeed = 0;
  }else if(dir=="nw"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = -1;
  }else if(dir=="ne"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = 1;
  }else if(dir=="sw"){
    drivetrainLeftSideSpeed = -1;
    drivetrainRightSideSpeed = 1;
    drivetrainStraifeSpeed = -1;
  }else{
    drivetrainLeftSideSpeed = -1;
    drivetrainRightSideSpeed = 1;
    drivetrainStraifeSpeed = 1;
  }
  MechnumWheelsMotorA.setVelocity(drivetrainLeftSideSpeed, percent);//Might need to be multiplied by 100
  MechnumWheelsMotorB.setVelocity(drivetrainRightSideSpeed, percent);
  OmniWheel.setVelocity(drivetrainStraifeSpeed, percent);
  OmniWheel.spin(forward);
  MechnumWheelsMotorB.spin(forward);
  MechnumWheelsMotorA.spin(forward);
}

competition Competition;

bool RemoteControlCodeEnabled = true;
bool DrivetrainNeedsToBeStopped_Controller1 = true;
bool tgtMotorStopped = true;

vDrive vDrivetrain;//Drivetrain Class

void pre_auton(void){
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

//Use Compass for drivetrain movement
void autonomous(void){
  //vDrivetrain.move("north");
  wait(20, msec);
  //vDrivetrain.pause();
}

//DO NOT CHANGE (unless nessisary)
void usercontrol(void){
  tgt.setVelocity(100, percent);//Adjust for arm speed
  while(true){
  if(RemoteControlCodeEnabled) {
      int drivetrainLeftSideSpeed = Controller1.Axis3.position()/abs(Controller1.Axis3.position())*(abs(Controller1.Axis3.position()) + abs(Controller1.Axis4.position()));
      int drivetrainRightSideSpeed = Controller1.Axis3.position()/abs(Controller1.Axis3.position())*(abs(Controller1.Axis3.position()) + abs(Controller1.Axis4.position()));
      int drivetrainStraifeSpeed = Controller1.Axis4.position();
      int rotationAngle = atan2(Controller1.Axis2.position(), Controller1.Axis1.position());
      int drivetrainTurnSpeed = Controller1.Axis1.position();
      int turnVelocity = 50;
      
      // check if the values are inside of the deadband range
      if (abs(drivetrainLeftSideSpeed) < 5 && abs(drivetrainRightSideSpeed) < 5 && abs(drivetrainTurnSpeed) < 5 && abs(drivetrainStraifeSpeed) < 5) {
        // check if the motors have already been stopped
        if (DrivetrainNeedsToBeStopped_Controller1) {
          // stop the drive motors
          MechnumWheelsMotorA.stop();
          MechnumWheelsMotorB.stop();
          OmniWheel.stop();
          // tell the code that the motors have been stopped
          DrivetrainNeedsToBeStopped_Controller1 = false;
        }
      } else {
        DrivetrainNeedsToBeStopped_Controller1 = true;
        if(abs(drivetrainLeftSideSpeed) < 5) drivetrainLeftSideSpeed = 0;
        if(abs(drivetrainRightSideSpeed) < 5) drivetrainRightSideSpeed = 0;
        if(abs(drivetrainStraifeSpeed) < 5) drivetrainStraifeSpeed = 0;
        if(abs(drivetrainTurnSpeed) < 5) drivetrainTurnSpeed = 0;
      }
      if (Controller1.ButtonR1.pressing()) {
        tgt.spin(forward);
        tgtMotorStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        tgt.spin(reverse);
        tgtMotorStopped = false;
      }else if (!tgtMotorStopped){
        tgt.stop(hold);
        tgtMotorStopped = true;
      }
      if (DrivetrainNeedsToBeStopped_Controller1) {
        MechnumWheelsMotorA.setVelocity(drivetrainLeftSideSpeed, percent);
        MechnumWheelsMotorA.spin(forward);
        MechnumWheelsMotorB.setVelocity(drivetrainRightSideSpeed, percent);
        MechnumWheelsMotorB.spin(forward);
        OmniWheel.setVelocity(drivetrainStraifeSpeed, percent);
        OmniWheel.spin(forward);
        if(abs(drivetrainTurnSpeed)>0){
          MechnumWheelsMotorA.setVelocity(drivetrainTurnSpeed, percent);
          MechnumWheelsMotorA.spin(reverse);
          MechnumWheelsMotorB.setVelocity(drivetrainTurnSpeed, percent);
          MechnumWheelsMotorB.spin(forward);
          OmniWheel.setVelocity(drivetrainTurnSpeed, percent);
          OmniWheel.spin(reverse);
        }
      }
      /*if(DrivetrainNeedsToBeStopped_Controller1) {
        MechnumWheelsMotorA.setVelocity(turnVelocity, percent);
        MechnumWheelsMotorB.setVelocity(turnVelocity, percent);
        OmniWheel.setVelocity(turnVelocity, percent);
        if(Inertial6.rotation(degrees)-rotationAngle>=5){//turn right
          MechnumWheelsMotorA.spin(reverse);
          MechnumWheelsMotorB.spin(reverse);
          OmniWheel.spin(reverse);
        }
        else if(Inertial6.rotation(degrees)-rotationAngle<=-5){//turn left
          MechnumWheelsMotorA.spin(forward);
          MechnumWheelsMotorB.spin(forward);
          OmniWheel.spin(forward);
        }*/
      
    }
    // wait before repeating the process
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true){
    wait(100, msec);
  }
}

