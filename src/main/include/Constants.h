/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "studica/Servo.h"
#include "subsystems/AMCU.h"

namespace Constants {
        // logfile path
        inline constexpr const char* FILE_PATH = "/home/pi/robot.log";
        // amcu constants
        inline constexpr int kWheelRadius = 50;
        inline constexpr int kRobotRadius = 150;

        inline constexpr Motor kMotorLeft = MOTOR_0;
        inline constexpr Motor kMotorRight = MOTOR_2;
        inline constexpr Motor kMotorBack = MOTOR_3;
        inline constexpr Motor kMotorElevator = MOTOR_1;

        // ultra sonic right
        inline constexpr int RIGHT_TRIG_PORT = 15;
        inline constexpr int RIGHT_ECHO_PORT = 16;
        // ultra sonic left
        inline constexpr int LEFT_TRIG_PORT = 8;
        inline constexpr int LEFT_ECHO_PORT = 9;

        // sensor update rate
        inline constexpr int SENSOR_UPDATE_RATE = 25;

        inline constexpr int GRIPPER_TILT_PORT = 10;
        inline constexpr int GRIPPER_OPEN_PORT = 11;

        inline constexpr int ELEVATOR_MOVE_PORT = 12;
        inline constexpr int ELEVEVATOR_UPDOWN_PORT = 13;
        inline constexpr int ELEVATOR_ROTATE_PORT = 14;

}
