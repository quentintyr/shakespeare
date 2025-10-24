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
#include "subsystems/amcu/AMCU.h"
#include "subsystems/modes/Teleop.h"
#include "Constants.h"

#include <networktables/NetworkTableInstance.h>
#include <frc/RobotController.h>
#include <frc/DriverStation.h>

UltraSonicSubsystem sonic;
Gamepad gamepad;
AMCU amcu;

// Teleop mode handler
Teleop *teleop = nullptr;

void Robot::RobotInit()
{
  InitLogging();
  SetupLogging();
  LOG_INFO("Initializing Robot...");

  // Initialize ultrasonic sensors
  sonic.UltraSonicStartThread();

  // Initialize AMCU with mecanum drive (using motors 0-3)
  // Adjust these values based on your robot's dimensions
  amcu.initMecanumDriveBase(
      Constants::kWheelRadius, // wheel radius in mm
      300,                     // robot length (X) in mm
      300,                     // robot width (Y) in mm
      MOTOR_0,                 // front left
      MOTOR_1,                 // front right
      MOTOR_2,                 // back left
      MOTOR_3                  // back right
  );

  // Set PID values for motor control (tune these as needed)
  amcu.setPID(1.0, 0.0, 0.0);

  // Initialize teleop mode handler
  teleop = new Teleop(&amcu, &gamepad);

  LOG_INFO("AMCU initialized with Mecanum drive");
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  frc2::CommandScheduler::GetInstance().Run();
  UpdateLogging();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit()
{
  LOG_DISABLED(" Disabled.");
}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
  last_mode = {LOG_PURPLE, "[AUTONOMOUS]"};
  LOG_AUTONOMOUS("Enabled");
}

void Robot::AutonomousPeriodic()
{
}

void Robot::TeleopInit()
{
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  last_mode = {LOG_CYAN, "[TELEOP]"};
  LOG_TELEOP("Enabled.");

  if (teleop)
  {
    teleop->Init();
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if (teleop)
  {
    teleop->Periodic();
  }
}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

void Robot::TestInit() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
