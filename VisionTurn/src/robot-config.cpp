#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT10, ratio18_1, false);
motor RightDriveSmart = motor(PORT1, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
/*vex-vision-config:begin*/
signature Vision5__SIG_1 = signature (1, 6099, 8065, 7082, -1069, -745, -907, 3.6, 0);
signature Vision5__SIG_2 = signature (2, -2341, -1273, -1807, 4733, 6757, 5745, 2.5, 0);
signature Vision5__SIG_3 = signature (3, 1319, 2743, 2031, -3435, -2933, -3184, 1.1, 0);
signature Vision5__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3.6, 0);
vision Vision5 = vision (PORT5, 50, Vision5__SIG_1, Vision5__SIG_2, Vision5__SIG_3, Vision5__SIG_5);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}