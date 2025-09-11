/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "subsystems/AMCU.h"
#include "utilities/LoggingSystem.h"
#include "utilities/ShuffleboardData.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include <frc/DigitalInput.h>
#include <frc/AnalogInput.h>
#include <frc/Ultrasonic.h> 

#include "studica/Servo.h"
#include <iostream>
#include <thread>
#include <chrono>

float servoPos = 0.f;
constexpr int kWheelRadius = 50;
constexpr int kRobotRadius = 150;
constexpr Motor kMotorLeft = MOTOR_0;
constexpr Motor kMotorRight = MOTOR_2;
constexpr Motor kMotorBack = MOTOR_3;
int whiteCableTrig = 0;
int grayCableEcho = 1;

AMCU amcu;
ShuffleboardData loadData;

studica::Servo* servo;
frc::DigitalInput* stopBottom;
// ultra sonic sensors
// frc::AnalogInput* leftSensor;
// frc::AnalogInput* rightSensor;

frc::Ultrasonic* leftSide;
frc::Ultrasonic* rightSide;

void Robot::RobotInit() {
  SetupLogging();
  LOG_INFO("Initialize Robot");
  amcu.initOmniDriveBase(kWheelRadius, kRobotRadius, kMotorLeft, kMotorRight, kMotorBack);
  // try
  // {
  //   if(stopBottom == nullptr)
  //     stopBottom = new frc::DigitalInput(8);
  //   }

  // catch(const std::exception& e)
  // {
  //   std::cerr << e.what() << '\n';
  // }

    if (leftSide == nullptr) {
    leftSide = new frc::Ultrasonic(9, 8); // or your correct DIOs
    leftSide->SetEnabled(true);
        }
    frc::Ultrasonic::SetAutomaticMode(true);  
    

  }
  

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { 
  frc2::CommandScheduler::GetInstance().Run(); 
    
  // bool isPressed;
  // if (stopBottom == nullptr) {
  //   isPressed = false;  // default if not connected
  // } else {
  //   isPressed = !stopBottom->Get();
  // }

  // if (isPressed == true) {
  //   LOG_INFO("pressed switch");
  // }
  try {
    // double mm = leftSide->GetRangeMM();
    double distance = getDistance();
    bool valid = leftSide->IsRangeValid();
    if(valid == false) { 
      std::cout << "Ultrasonic left: " << distance << " mm\n";
      } 
      else {
        LOG_INFO("oops");
      }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}


/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  // amcu.driveDistance(2, 0, 0);
  m_autonomousCommand = m_container.GetAutonomousCommand();

    if (m_autonomousCommand != nullptr) {
      m_autonomousCommand->Schedule();
    }
// try
//   {
//     if(servo == nullptr)
//       servo = new studica::Servo(18);
//     }

//   catch(const std::exception& e)
//   {
//     std::cerr << e.what() << '\n';
//   }

}


void Robot::AutonomousPeriodic() {
  servo->Set(servoPos);
  servoPos += 0.001;
  if(servoPos > 1) {
    servoPos = 0;   
  }

  std::cout << servoPos << std::endl;
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

double Robot::getDistance() {
    return leftSide->GetRangeMM();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
