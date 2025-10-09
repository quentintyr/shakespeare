#include "subsystems/Gamepad.h"
#include <frc/Joystick.h>

// The joystick object for the driver controller
static frc::Joystick driveJoystick(DRIVE_USB_PORT);

// Axis methods
double Gamepad::GetRightDriveY(void) {
    return driveJoystick.GetRawAxis(RIGHT_ANALOG_Y);
}

double Gamepad::GetRightDriveX(void) {
    return driveJoystick.GetRawAxis(RIGHT_ANALOG_X);
}

double Gamepad::GetLeftDriveY(void) {
    return driveJoystick.GetRawAxis(LEFT_ANALOG_Y);
}

double Gamepad::GetLeftDriveX(void) {
    return driveJoystick.GetRawAxis(LEFT_ANALOG_X);
}

// Button methods
bool Gamepad::GetDriveRightTrigger(void) {
    return driveJoystick.GetRawButton(RIGHT_TRIGGER);
}

bool Gamepad::GetDriveRightBumper(void) {
    return driveJoystick.GetRawButton(RIGHT_BUMPER);
}

bool Gamepad::getDriveLeftTrigger(void) {
    return driveJoystick.GetRawButton(LEFT_TRIGGER);
}

bool Gamepad::GetDriveLeftBumper(void) {
    return driveJoystick.GetRawButton(LEFT_BUMPER);
}

bool Gamepad::GetDriveXButton(void) {
    return driveJoystick.GetRawButton(X_BUTTON);
}

bool Gamepad::GetDriveSquareButton(void) {
    return driveJoystick.GetRawButton(SQUARE_BUTTON);
}

bool Gamepad::GetDriveCircleButton(void) {
    return driveJoystick.GetRawButton(CIRCLE_BUTTON);
}

bool Gamepad::GetDriveTriangleButton(void) {
    return driveJoystick.GetRawButton(TRIANGLE_BUTTON);
}

bool Gamepad::GetDriveOptionsButton(void) {
    return driveJoystick.GetRawButton(OPTIONS_BUTTON);
}

bool Gamepad::GetDriveShareButton(void) {
    return driveJoystick.GetRawButton(SHARE_BUTTON);
}

bool Gamepad::GetDriveRightAnalogButton(void) {
    return driveJoystick.GetRawButton(RIGHT_ANALOG_BUTTON);
}

bool Gamepad::GetDriveLeftAnalogButton(void) {
    return driveJoystick.GetRawButton(LEFT_ANALOG_BUTTON);
}

bool Gamepad::GetDrivePS4Button(void) {
    return driveJoystick.GetRawButton(PS4_BUTTON);
}

bool Gamepad::GetDriveTouchpadButton(void) {
    return driveJoystick.GetRawButton(TOUCHPAD_BUTTON);
}
