/*#include "vex.h"

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
}*/