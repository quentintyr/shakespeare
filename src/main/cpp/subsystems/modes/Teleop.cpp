#include "subsystems/modes/Teleop.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include "Constants.h"
#include <cmath>

Teleop::Teleop(AMCU *amcu, Gamepad *gamepad)
    : m_amcu(amcu),
      m_gamepad(gamepad)
{
}

void Teleop::Init()
{
    LOG_TELEOP("Initializing Teleop for Controller use");

    // Stop elevator motor
    m_amcu->setSpeed(Constants::kMotorElevator, 0);
}

void Teleop::Periodic()
{
    m_gamepad->Periodic();
    HandleDrive();
    HandleElevatorUpDown();
}

/**
 * Omnidirectional , left stick for translation and right stick X for rotation
 */
void Teleop::HandleDrive()
{
    // Get joystick inputs
    double leftY = m_gamepad->GetLeftDriveY();   // Forward/backward
    double leftX = m_gamepad->GetLeftDriveX();   // Strafe left/right
    double rightX = m_gamepad->GetRightDriveX(); // Rotation

    // Apply deadzone to avoid drift (adjust threshold as needed)
    const double deadzone = 0.1;
    if (std::abs(leftY) < deadzone)
        leftY = 0.0;
    if (std::abs(leftX) < deadzone)
        leftX = 0.0;
    if (std::abs(rightX) < deadzone)
        rightX = 0.0;

    // Convert joystick values to speed commands
    int8_t xSpeed = static_cast<int8_t>(leftX * 50);  // cm/s strafe
    int8_t ySpeed = static_cast<int8_t>(-leftY * 50); // cm/s forward (inverted)
    int8_t wSpeed = static_cast<int8_t>(rightX * 90); // deg/s rotation

    // Amcu speed drive with custom speeds
    m_amcu->speedDrive(xSpeed, ySpeed, wSpeed);
}

/**
 * Elevator up/down using AMCU
 */
void Teleop::HandleElevatorUpDown()
{
    // Elevator motor control - D-pad up/down
    if (m_gamepad->IsDPadUp())
    {
        // Move elevator up at 50% speed
        m_amcu->setSpeed(Constants::kMotorElevator, 50);
    }
    else if (m_gamepad->IsDPadDown())
    {
        // Move elevator down at -50% speed
        m_amcu->setSpeed(Constants::kMotorElevator, -50);
    }
    else
    {
        // Stop elevator when no D-pad input
        m_amcu->setSpeed(Constants::kMotorElevator, 0);
    }
}
