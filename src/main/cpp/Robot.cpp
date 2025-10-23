/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include "subsystems/sensor/UltraSonicSubsystem.h"
#include "subsystems/elevator/ElevatorSubsystem.h"
#include "subsystems/Gamepad.h"

#include <networktables/NetworkTableInstance.h>
#include <frc/RobotController.h>
#include <frc/DriverStation.h>

UltraSonicSubsystem sonic;
Gamepad gamepad;

void Robot::RobotInit() {
  InitLogging();
  SetupLogging();
  LOG_INFO("Initializing Robot...");
  sonic.UltraSonicStartThread();
  // ElevatorUpDown::ElevatorSubsystem::init(&amcu);   
  // ElevatorUpDown::ElevatorSubsystem::calibrate();
  
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
  UpdateLogging();
}


/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  LOG_DISABLED(" Disabled.");
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  last_mode = {LOG_PURPLE, "[AUTONOMOUS]"};
  LOG_AUTONOMOUS("Enabled");

}


void Robot::AutonomousPeriodic() {


}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  last_mode = {LOG_CYAN, "[TELEOP]"};
  LOG_TELEOP("Enabled.");

}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {

  gamepad.Periodic();

}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

void Robot::TestInit() {}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
