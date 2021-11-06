#include "vex.h"
#include "matrix.h"
#include <chrono>

using namespace std;

//matixCalculator mc;
class robotPosition {
  double xPos=0, yPos=0, zPos =0;
  double xVel=0, yVel=0, zVel=0;
  double** getAccel(){
    double accel3d[3][1];
    vex::inertial::quaternion qRotation;
    qRotation = Inertial6.vex::inertial::orientation();
    double q0 = qRotation.a;
    double q1 = qRotation.b;
    double q2 = qRotation.c;
    double q3 = qRotation.d;
    double rotMatrix[3][3] = {{2 * (q0 * q0 + q1 * q1) - 1, 2 * (q1 * q2 - q0 * q3), 2 * (q1 * q3 + q0 * q2)},
                              {2 * (q1 * q2 + q0 * q3), 2 * (q0 * q0 + q2 * q2) - 1, 2 * (q2 * q3 - q0 * q1)},
                              {2 * (q1 * q3 - q0 * q2), 2 * (q2 * q3 + q0 * q1), 2 * (q0 * q0 + q3 * q3) - 1}};
    
    double acelMatrix[3][1] = {{Inertial6.vex::inertial::acceleration(xaxis)},
                            {Inertial6.vex::inertial::acceleration(yaxis)},
                            {Inertial6.vex::inertial::acceleration(zaxis)}};
    double adj[3][3];
    float inv[3][3];
    //mc.inverse(rotMatrix, inv);
    //return (mc.multiply(3, 3, rotMatrix, 3, 1, acelMatrix));
    //Inertial6.vex::inertial::pitch();
  }

  public:
  void calibrate(){
    double xAccel = getAccel()[0][0];
    double yAccel = getAccel()[1][0];
    double zAccel = getAccel()[2][0];
    if(xAccel == 0 && yAccel == 0 && zAccel == 1){

    }else{
      Brain.Screen.print("IMU Calibration Failed");
    }
  }

  public:
  void updatePos(){
    double xAccel = getAccel()[0][0];
    double yAccel = getAccel()[1][0];
    double zAccel = getAccel()[2][0];
    xPos = xVel * .02 + .5 * xAccel * (.02)*(.02);
    yPos = yVel * .02 + .5 * yAccel * (.02)*(.02);
    //zPos = zVel * .02 + .5 * xAccel * (.02)*(.02);
    xVel = xAccel * (.02);
    yVel = yAccel * (.02);
  }

  public:
  double getXPos(){
    return xPos;
  }
  public:
  double getYPos(){
    return xPos;
  }
  public:
  double getZPos(){
    return zPos;
  }

  public:
  void resetV(){
    xVel = 0;
    yVel = 0;
  }
};