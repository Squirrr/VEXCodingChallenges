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
bumper BumperC = bumper(Brain.ThreeWirePort.C);
motor rightMotor = motor(PORT1, ratio18_1, false);

distance Distance9 = distance(PORT9);
optical Optical2 = optical(PORT2);
servo ServoB = servo(Brain.ThreeWirePort.B);
motor leftMotor = motor(PORT10, ratio18_1, false);

limit LimitSwitchD = limit(Brain.ThreeWirePort.D);
pot PotentiometerA = pot(Brain.ThreeWirePort.A);
led LEDE = led(Brain.ThreeWirePort.E);


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
/*    Created:      {2/11/25}                                                 */
/*    Description:  VEX Coding Challenge Part 2                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

int lifeCounter = 3;
int level = 0;

/* When the bumper is pressed, turn on the LEDs
   for 2 seconds then turn them off until the 
   bumper is pressed again */
int partThreeProblemOne() {
  LEDE.off();
  while (true) {
    while (!BumperC.pressing()) {}
    LEDE.on();
    wait(2, seconds);
    LEDE.off();
  }
  return 0;
}

/* If the bumper is pressed, decrease the life counter by 1;
 * else, maintain the life counter
 * then, advance to the next level
 * If the lifeCounter reaches zero, the game is over */
int partThreeProblemTwo() {
  if (lifeCounter > 0) {
      level++;
      Brain.Screen.clearScreen();
      Brain.Screen.newLine();
      Brain.Screen.print("LifeCounter: "); Brain.Screen.print(lifeCounter);
      Brain.Screen.newLine();
      wait(1, seconds);
      Brain.Screen.print("Level: "); Brain.Screen.print(level);
      Brain.Screen.newLine();
      wait(1, seconds);
      if(BumperC.pressing()) {
        Brain.Screen.print("LEVEL FAILED");
        Brain.Screen.newLine();
        lifeCounter--;
      } else {
        Brain.Screen.print("LEVEL SUCCESS");
        Brain.Screen.newLine();
      }
      wait(5, seconds);
    } else {
      Brain.Screen.clearScreen();
      Brain.Screen.newLine();
      Brain.Screen.print("GAME OVER");
      Brain.programStop();
    }
    return 0;
}

/* If the bumper is pressing, continuously spin forward 180 deg;
 * otherwise, stop spinning */
int partThreeProblemFour() {
  if (BumperC.pressing()) {
    rightMotor.spinFor(forward, 180, degrees);
  } else {
    rightMotor.stop();
  }
  return 0;
}

/* If the bumper is  pressing,
 * then if the distance to the object is less than 20mm, spin 
 * the right motor backwards. otherwise, spin forwards.
 * If the bumper is not pressed,
 * stop the motor.
 */
int partThreeProblemFive() {

  if (!BumperC.pressing()) {
    rightMotor.stop();
  }
  if (Distance9.objectDistance(mm) < 20) {
    rightMotor.setVelocity(-50, percent);
    rightMotor.spin(forward);
  } else {
    Brain.Screen.clearScreen();
    Brain.Screen.print(Distance9.objectDistance(mm));
    rightMotor.setVelocity(50, percent);
    rightMotor.spin(forward);
  }
  return 0;
}

/* If the bumper is not being pressed, turn the servo to default position.
 * Otherwise, turn to -50 degrees
 * If the optical sensor senses an object near it, turn to 50 degrees */
int partThreeProblemSix() {
  Optical2.setLight(ledState::on);
  Optical2.setLightPower(100, percent);

  if (!BumperC.pressing()) {
    ServoB.setPosition(0, degrees);
    return 0;
  }
  if (!Optical2.isNearObject()) {
    ServoB.setPosition(-50, degrees);
    return 0;
  }
  
  ServoB.setPosition(50, degrees);
  return 0;
}

/*If the bumper switch is being pressed, turn the left motor on
  If the limit switch is being pressed, turn the right motor on*/
int partThreeProblemSeven() {
  leftMotor.spin(forward);
  rightMotor.spin(forward);

  if (BumperC.pressing()) {
    leftMotor.setVelocity(50, percent);
  } else {
    leftMotor.setVelocity(0, percent);
  }

  if (LimitSwitchD.pressing()) {
    rightMotor.setVelocity(50, percent);
  } else {
    rightMotor.setVelocity(0, percent);
  }

  return 0;
}

/* Spin the right motor four times and 
   print the current count on the screen */
int partThreeProblemEight() {
  //Part 1 Provided Code

  int motorCount = 1;
  while (motorCount < 4) {
    rightMotor.setVelocity(50, percent);
    rightMotor.spinFor(forward, 95, degrees);
    wait(2, seconds);
    rightMotor.stop();
    wait(2, seconds);
    motorCount++;
  }
  Brain.Screen.print(motorCount); 
  return 0;
}

/* Helper function to turn the LED on 
   if the bumper is being pressed*/
void turnLEDon() {
  if (BumperC.pressing()) {
    LEDE.on();
  } else {
    LEDE.off();
  }
}

/* If the bumper is being pressed, turn on the LED
   and print the closest object distance the distance sensor has read */
int partThreeProblemTen() {
  int closest = 10000; //Arbitrary value
  Brain.Screen.print(closest);
  Brain.Screen.setCursor(1, 7);
  Brain.Screen.print(Distance9.objectDistance(mm));
  Brain.Screen.newLine();
  while (true) {
    turnLEDon();
    while (!BumperC.pressing()) {
      Brain.Screen.clearLine(2);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(closest);
      Brain.Screen.setCursor(2, 7);
      Brain.Screen.print(Distance9.objectDistance(mm));
      if (Distance9.objectDistance(mm) < closest) {
        closest = Distance9.objectDistance(mm);
      }
    }
  }
}

/* If the bumper is being pressed, turn on the LED
   and print the farthest object distance the distance sensor has read */
int partThreeProblemEleven() {
  int farthest = Distance9.objectDistance(mm); //Current farthest value
  Brain.Screen.print(farthest);
  Brain.Screen.setCursor(1, 7);
  Brain.Screen.print(Distance9.objectDistance(mm));
  Brain.Screen.newLine();
  while (true) {
    turnLEDon();
    while (!BumperC.pressing()) {
      Brain.Screen.clearLine(2);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(farthest);
      Brain.Screen.setCursor(2, 7);
      Brain.Screen.print(Distance9.objectDistance(mm));
      if (Distance9.objectDistance(mm) < farthest) {
        farthest = Distance9.objectDistance(mm);
      }
    }
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code
  int currentProblem = 0; //Config based on selected problem

  //Set screen typeface
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.setFont(mono30);
  Brain.Screen.setPenColor(white);
  wait(15, msec);
  leftMotor.setVelocity(0, percent);
  rightMotor.setVelocity(0, percent);

  while (true) {
    
    switch (currentProblem) {
    case 1:
      partThreeProblemOne();
      break;
    case 2:
      partThreeProblemTwo();
      break;
    case 4:
      partThreeProblemFour();
      break;
    case 5:
      partThreeProblemFive();
      break;
    case 6:
      partThreeProblemSix();
      break;
    case 7:
      partThreeProblemSeven();
      break;
    case 8:
      partThreeProblemEight();
      break;
    case 10:
      partThreeProblemTen();
      break;
    case 11:
      partThreeProblemEleven();
      break;
    default:
      break;
    }
  }
}
