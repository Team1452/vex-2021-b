/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Windward_Student                                 */
/*    Created:      Sat Oct 16 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    10, 1           
// Vision5              vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
int redMax = 0, blueMax = 0, yellowMax = 0;

void autonomous(){
  bool detected = false;
  int max;
  int i = 0;
  while(i<11){
    Drivetrain.turnFor(right, 10, degrees);
    wait(50, msec);
    Vision5.takeSnapshot(Vision5__SIG_1);
    int redboxSize = Vision5.objects[0].height * Vision5.objects[0].width;
    redMax = fmax(redMax, redboxSize);
    Vision5.takeSnapshot(Vision5__SIG_2);
    int blueboxSize = Vision5.objects[0].height * Vision5.objects[0].width;
    blueMax = fmax(blueMax, blueboxSize);
    Vision5.takeSnapshot(Vision5__SIG_3);
    int yellowboxSize = Vision5.objects[0].height * Vision5.objects[0].width;
    yellowMax = fmax(yellowMax, yellowboxSize);
    i++;
  }
  max = fmax(yellowMax, fmax(redMax, blueMax));
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(3, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print(max);
  while(!detected){
    Drivetrain.turnFor(left, 5, degrees);
    if(max==redMax){
      Vision5.takeSnapshot(Vision5__SIG_1);
      if(Vision5.objectCount >0 && abs((Vision5.objects[0].height * Vision5.objects[0].width)- redMax)<500){
        detected = true;
      }
    }else if(max==blueMax){
      Vision5.takeSnapshot(Vision5__SIG_2);
      if(Vision5.objectCount >0 && abs((Vision5.objects[0].height * Vision5.objects[0].width)- blueMax)<500){
        detected = true;
      }
    }else{
      Vision5.takeSnapshot(Vision5__SIG_3);
      if(Vision5.objectCount >0 && abs((Vision5.objects[0].height * Vision5.objects[0].width)- yellowMax)<500){
        detected = true;
      }
    }
  }
  Drivetrain.drive(forward);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  autonomous();
}