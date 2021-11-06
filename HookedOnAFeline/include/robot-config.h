using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MechnumWheelsMotorA;
extern motor MechnumWheelsMotorB;
extern motor OmniWheel;
extern controller con;
extern drivetrain Drivetrain;
extern inertial Inertial6;
extern motor tgt;
extern motor tgt2;
extern gps GPS8;
extern motor turnTable;
extern motor intake;
extern limit intakeSwitch;
extern limit tgt2Switch;
extern limit tgtSwitch;
extern sonar tgtRangeFinder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );