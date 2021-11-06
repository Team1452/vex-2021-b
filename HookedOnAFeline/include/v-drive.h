#include "vex.h"

using namespace vex;

#define calculateSpeed(theta, xsign, ysign)
  

class vDrive {
  public:
    void move(std::string dir);
    //void rotate(int degree);
    void pause(){
      MechnumWheelsMotorA.stop();
      MechnumWheelsMotorB.stop();
      OmniWheel.stop();
    }
    void moveTo(double x, double y);
};

void moveTo(double x, double y){
  int ysign, xsign;
  double theta = atan2(abs(GPS8.yPosition(mm) - y), abs(GPS8.xPosition(mm) - x));
  while(abs(GPS8.yPosition(mm) - y) > 10 && abs(GPS8.xPosition(mm) - x) > 10){
    if(GPS8.yPosition(mm) < y){
      ysign = -1;
    }else{
      ysign = 1;
    }
    if(GPS8.xPosition(mm) < x){
      xsign = -1;
    }else{
      xsign = 1;
    }
    int vx = cos(theta)*100;
    int vy = sin(theta)*100;
    MechnumWheelsMotorA.setVelocity((vx+vy)*ysign, percent);
    MechnumWheelsMotorB.setVelocity((vx+vy)*ysign, percent);
    OmniWheel.setVelocity(vx * xsign, percent);
    OmniWheel.spin(vex::forward);
    MechnumWheelsMotorB.spin(vex::forward);
    MechnumWheelsMotorA.spin(vex::forward);
  }
    MechnumWheelsMotorA.stop();
    MechnumWheelsMotorB.stop();
    OmniWheel.stop();
}
/*void rotate(int degree){
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
}*/

void vDrive::move(std::string dir) {
  int drivetrainLeftSideSpeed = 0, drivetrainRightSideSpeed = 0, drivetrainStraifeSpeed = 0;
  if(dir=="north"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = 1;
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
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = 0;
  }else if(dir=="nw"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = 1;
    drivetrainStraifeSpeed = -1;
  }else if(dir=="ne"){
    drivetrainLeftSideSpeed = 1;
    drivetrainRightSideSpeed = 1;
    drivetrainStraifeSpeed = 1;
  }else if(dir=="sw"){
    drivetrainLeftSideSpeed = -1;
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = -1;
  }else{
    drivetrainLeftSideSpeed = -1;
    drivetrainRightSideSpeed = -1;
    drivetrainStraifeSpeed = 1;
  }
  MechnumWheelsMotorA.setVelocity(drivetrainLeftSideSpeed*100, percent);//Might need to be multiplied by 100
  MechnumWheelsMotorB.setVelocity(drivetrainRightSideSpeed*100, percent);
  OmniWheel.setVelocity(drivetrainStraifeSpeed*100, percent);
  OmniWheel.spin(forward);
  MechnumWheelsMotorB.spin(forward);
  MechnumWheelsMotorA.spin(forward);
}