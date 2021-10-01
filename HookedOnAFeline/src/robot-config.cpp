#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MechnumWheelsMotorA = motor(PORT2, ratio18_1, true); //Left
motor MechnumWheelsMotorB = motor(PORT1, ratio18_1, false); //Right
motor OmniWheel = motor(PORT3, ratio18_1, false);
controller Controller1 = controller(primary);
inertial Inertial6 = inertial(PORT6);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Inertial6.calibrate();
  while (Inertial6.isCalibrating()){
    wait(100, msec);
  }
}