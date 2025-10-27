/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "studica/Servo.h"
#include "subsystems/amcu/AMCU.h"


namespace Constants
{
class Base{
public:
        // amcu constants
        static constexpr int kWheelRadius = 50;
        static constexpr int kRobotRadius = 150;

        static constexpr Motor kMotorLeft = MOTOR_0;
        static constexpr Motor kMotorRight = MOTOR_2;
        static constexpr Motor kMotorBack = MOTOR_3;
        static constexpr Motor kMotorElevator = MOTOR_1;
};

class Ultrasonic{
public:
        // ultra sonic right
        static constexpr int RIGHT_TRIG_PORT = 2;
        static constexpr int RIGHT_ECHO_PORT = 3;
        // ultra sonic left
        static constexpr int LEFT_TRIG_PORT = 0;
        static constexpr int LEFT_ECHO_PORT = 1;

        // sensor update rate
        static constexpr int SENSOR_UPDATE_RATE = 25;
};

class Gripper{
public:
        static constexpr int GRIPPER_TILT_PORT = 10;
        static constexpr int GRIPPER_OPEN_PORT = 11;
};

class Elevator{
public:
        static constexpr int ELEVATOR_MOVE_PORT = 12;
        static constexpr int ELEVEVATOR_UPDOWN_PORT = 13;
        static constexpr int ELEVATOR_ROTATE_PORT = 14;
};

class Extender{
public:
        static constexpr int SERVO_PORT = 18;

        static constexpr int LIMIT_SWITCH_STOP_BACK_PORT = 11;
        static constexpr int LIMIT_SWITCH_STOP_FRONT_PORT = 10;

        static constexpr double DRIVE_FORWARD = 0.0;
        static constexpr double DRIVE_BACKWARD = 1.0;
        static constexpr double DRIVE_STOP = 0.5;
};


class IRSensors{
public:
        static constexpr int LEFT   = 1;
        static constexpr int RIGHT  = 0;
        static constexpr int MAX_RANGE = 10;
};

}


