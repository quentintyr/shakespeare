/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"
#include "utilities/LoggingSystem.h"
#include "subsystems/UltraSonicSubsystem.h"
#include "subsystems/LidarSubsystem.h"
#include "subsystems/ExtenderSubsystem.h"

#include "subsystems/ElevatorSubsystem.h"
#include "utilities/WidgetSystem.h"
#include "utilities/ShuffleboardData.h"
#include <networktables/NetworkTableInstance.h>
#include <frc/RobotController.h>
#include <frc/DriverStation.h>

UltraSonicSubsystem sonic;

void Robot::RobotInit() {
  SetupLogging();
  LOG_INFO("Initializing Robot...");
  sonic.UltraSonicStartThread();
  // ElevatorUpDown::ElevatorSubsystem::init(&amcu);   
  // ElevatorUpDown::ElevatorSubsystem::calibrate();

  auto table1 = nt::NetworkTableInstance::GetDefault().GetTable("Dashboard");
  table1->PutString("RobotMode", "init");
  table1->PutBoolean("Connected", true);

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

  auto table = nt::NetworkTableInstance::GetDefault().GetTable("Dashboard");
  // Battery data
  double batteryVoltage = frc::RobotController::GetInputVoltage();
  table->PutNumber("Battery", batteryVoltage);
  
  // Ultrasonic sensors
  table->PutNumber("USSensorLeft", sonic.getSonicLeftDistance());
  table->PutNumber("USSensorRight", sonic.getSonicRightDistance());
  auto mode = GetRobotMode();
  table->PutString("RobotMode", mode);
  
  // Placeholder sensor data (replace with real sensors when available)
  table->PutNumber("IRSensorLeft", 0);
  table->PutNumber("IRSensorRight", 0);
  table->PutNumber("LidarDistance", 0);
  table->PutString("LidarStatus", "disconnected");
  table->PutString("ElevatorPosition", "0mm");
  table->PutString("CarriagePosition", "home");
  table->PutString("GripperStatus", "open");
  table->PutString("ExtenderStatus", "idle");
  table->PutNumber("ExtenderLength", 0);
  table->PutString("LineFollowerSensor", "not on line");
}

std::string Robot::GetRobotMode() {
    // Use correct FRC 2020 API method names
    auto& ds = frc::DriverStation::GetInstance();
    
    if (ds.IsDisabled()) {
        return "disabled";
    } else if (ds.IsAutonomous()) {
        return "autonomous";
    } else if (ds.IsOperatorControl()) {
        return "teleop";
    } else if (ds.IsTest()) {
        return "test";
    } else {
        return "unknown";
    }
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
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}


#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
