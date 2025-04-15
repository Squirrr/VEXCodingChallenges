#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
servo ServoB = servo(Brain.ThreeWirePort.B);
motor LeftMotor = motor(PORT1, ratio18_1, false);

motor RightMotor = motor(PORT10, ratio18_1, false);

bumper BumperC = bumper(Brain.ThreeWirePort.C);
limit LimitSwitchD = limit(Brain.ThreeWirePort.D);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);
led LEDF = led(Brain.ThreeWirePort.F);


// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {Abdullah Khaled}                                         */
/*    Created:      {2/6/2025}                                                */
/*    Description:  VEX Coding Challenge Part 2                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

/* Set the servo position to val in degrees, print out that position,
   and wait for the waitTime amount of seconds */
void setServoAndPrint(double val, double waitTime) {
  ServoB.setPosition(val, degrees);
  Brain.Screen.print(val);
  wait(waitTime, seconds);
}

/* Set the servo position to various angles and wait for set intervals of time 
   before returning to home position */
void partTwoProblemOne() {
  setServoAndPrint(0, 1);
  setServoAndPrint(30, 3);
  setServoAndPrint(0, 3);
  setServoAndPrint(25, 2);
  setServoAndPrint(0, 1);
  setServoAndPrint(16, 3);
  setServoAndPrint(0, 1);
  setServoAndPrint(55, 2);
  setServoAndPrint(0, 0.1);
}

/* Spin the left motor at certain speeds and times, 
   then stop and spin the right motor to a certain position,
   and finally print "Brain Coding is Cool!" on the screen */
void partTwoProblemTwo() {

  //Spin left motor at 50% velocity for 3 seconds
  LeftMotor.setVelocity(50, percent);
  LeftMotor.spin(forward);
  wait(3, seconds);
  LeftMotor.stop();

  //Spin left motor at -100% velocity for 3 seconds
  LeftMotor.setVelocity(100, percent);
  LeftMotor.spin(reverse);
  wait(3, seconds);
  LeftMotor.stop();

  //Spin right motor -180 degrees, then
  //spin to 100 degrees
  RightMotor.spinFor(reverse, 180, degrees);
  RightMotor.spinToPosition(100, degrees);

  //Print "Brain Coding is Cool!" for 3 seconds then clear the screen
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFont(mono30);
  Brain.Screen.print("Brain Coding is Cool!");
  Brain.Screen.clearScreen();
  wait(3, seconds);
}

////////////////////////////////////////////////////////////
//Part Two Problem Three
/* Use events and broadcasts to move the motors when the 
   "motorMotion" event is broadcast */
event motorMotion = event();

void onEventMotorMotion() {
  LeftMotor.setVelocity(50, percent);
  RightMotor.setVelocity(50, percent);
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  wait(5, seconds);
  RightMotor.spin(reverse);
  wait(5, seconds);

}
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//Part Two Problem Four
/* Use events and broadcasts to move the left and right motors
   simultaneously when the "motorMove" event is broadcast */
event motorMove = event();

void onEventMotorMoveA() {
  RightMotor.setVelocity(50, percent);
  RightMotor.spin(forward);
  wait(5, seconds);
  RightMotor.stop();
  
}

void onEventMotorMoveB() {
  LeftMotor.setVelocity(75, percent);
  LeftMotor.spin(reverse);
  wait(2.5, seconds);
  LeftMotor.stop();
}
////////////////////////////////////////////////////////////


/* Turn on the LED and spin the motors when the potentiometer
   value is >=50%; otherwise, turn everything off */
void partTwoProblemSix() {
  if (PotentiometerA.angle(percent) >= 50) {
    LEDF.on();
    LeftMotor.setVelocity(75, percent);
    RightMotor.setVelocity(75, percent);
    LeftMotor.spin(reverse);
    RightMotor.spin(forward);
  } else {
    LeftMotor.stop();
    RightMotor.stop();
    LEDF.off();
  }
}


int main() {
  int currentProblem = 0; //Config based on selected problem

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code

  //Switch statement to manage problems based on user input
  switch (currentProblem) {
    case 1:
      partTwoProblemOne();
      break;
    case 2:
      partTwoProblemTwo();
      break;
    case 3:
      // Part Two Problem Three Code
      motorMotion(onEventMotorMotion);
      wait(15, msec);
      motorMotion.broadcast();
      break;
    case 4:
      // Part Two Problem Four Code
      motorMove(onEventMotorMoveA);
      motorMove(onEventMotorMoveB);
      wait(15, msec);
      motorMove.broadcast();
      break;
    case 5:
      //Part Two Problem Five A/B Code
      while (true) {
        if (BumperC.pressing()) {
          motorMove.broadcast();
        }
        if (LimitSwitchD.pressing()) {
          motorMove.broadcast();
        }
      }
      break;
    case 6:
      //Part Two Problem Six Code
      while (true) {
        partTwoProblemSix();
      }
      break;
    default:
      break;
  }
}
