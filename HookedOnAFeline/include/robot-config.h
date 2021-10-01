using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MechnumWheelsMotorA;
extern motor MechnumWheelsMotorB;
extern motor OmniWheel;
extern controller Controller1;
extern drivetrain Drivetrain;
extern inertial Inertial6;
extern motor tgt;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );