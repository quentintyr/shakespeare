#include "subsystems/Gamepad.h"
#include <networktables/NetworkTableInstance.h>
#include <frc/Joystick.h>
#include <cmath>

using namespace frc;

static Joystick drivePad{Gamepad::DRIVE_USB_PORT};

/**
 * Helper function to apply deadband.
 */
static double ApplyDeadband(double value, double deadband = 0.05) {
    return (std::fabs(value) < deadband) ? 0.0 : value;
}

// === Joystick Axis Accessors ===
double Gamepad::GetLeftDriveX()  { return ApplyDeadband(drivePad.GetRawAxis(LEFT_ANALOG_X)); }
double Gamepad::GetLeftDriveY()  { return ApplyDeadband(drivePad.GetRawAxis(LEFT_ANALOG_Y)); }

double Gamepad::GetRightDriveX() { return ApplyDeadband(drivePad.GetRawAxis(RIGHT_ANALOG_X)); }
double Gamepad::GetRightDriveY() { return ApplyDeadband(drivePad.GetRawAxis(RIGHT_ANALOG_Y)); }

// === Trigger Accessors ===
double Gamepad::GetLeftTrigger()  { return drivePad.GetRawAxis(LEFT_TRIGGER_A); }
double Gamepad::GetRightTrigger() { return drivePad.GetRawAxis(RIGHT_TRIGGER_A); }

// === Button Accessors ===
bool Gamepad::GetDriveLeftBumper()        { return drivePad.GetRawButton(LEFT_BUMPER); }
bool Gamepad::GetDriveRightBumper()       { return drivePad.GetRawButton(RIGHT_BUMPER); }
bool Gamepad::GetDriveBack()              { return drivePad.GetRawButton(BACK); }
bool Gamepad::GetDriveStart()             { return drivePad.GetRawButton(START); }

bool Gamepad::GetDriveAButton()           { return drivePad.GetRawButton(A_BUTTON); }
bool Gamepad::GetDriveXButton()           { return drivePad.GetRawButton(X_BUTTON); }
bool Gamepad::GetDriveYButton()           { return drivePad.GetRawButton(Y_BUTTON); }
bool Gamepad::GetDriveBButton()           { return drivePad.GetRawButton(B_BUTTON); }

bool Gamepad::GetDriveHomeButton()        { return drivePad.GetRawButton(HOME_BUTTON); }
bool Gamepad::GetDriveLeftStickPress()    { return drivePad.GetRawButton(LEFT_STICK_PRESS); }
bool Gamepad::GetDriveRightStickPress()   { return drivePad.GetRawButton(RIGHT_STICK_PRESS); }

bool Gamepad::GetDriveRightAnalogButton() { return drivePad.GetRawButton(RIGHT_ANALOG_BUTTON); }
bool Gamepad::GetDrivePS4Button()         { return drivePad.GetRawButton(PS4_BUTTON); }
bool Gamepad::GetDriveTouchpadButton()    { return drivePad.GetRawButton(TOUCHPAD_BUTTON); }


// POV for the DPAD
int Gamepad::GetPOV() { return drivePad.GetPOV(); }

bool Gamepad::IsDPadUp()    { return GetPOV() == 0; }
bool Gamepad::IsDPadRight() { return GetPOV() == 90; }
bool Gamepad::IsDPadDown()  { return GetPOV() == 180; }
bool Gamepad::IsDPadLeft()  { return GetPOV() == 270; }

// Update the Dashboard 
void Gamepad::Periodic() {

    auto controllerTable = nt::NetworkTableInstance::GetDefault().GetTable("Controller");

    // Publish primary sticks, triggers, and POV
    controllerTable->PutNumber("LeftX", GetLeftDriveX());
    controllerTable->PutNumber("LeftY", GetLeftDriveY());
    controllerTable->PutNumber("RightX", GetRightDriveX());
    controllerTable->PutNumber("RightY", GetRightDriveY());

    controllerTable->PutNumber("LeftTrigger", GetLeftTrigger());
    controllerTable->PutNumber("RightTrigger", GetRightTrigger());

    controllerTable->PutNumber("POV", GetPOV());

    // Buttons (1..16)
    controllerTable->PutNumber("A", GetDriveAButton());
    controllerTable->PutNumber("B", GetDriveBButton());
    controllerTable->PutNumber("X", GetDriveXButton());
    controllerTable->PutNumber("Y", GetDriveYButton());

    controllerTable->PutNumber("Left Bumper", GetDriveLeftBumper());
    controllerTable->PutNumber("Right Bumper", GetDriveRightBumper());

    controllerTable->PutNumber("Back", GetDriveBack());
    controllerTable->PutNumber("Start", GetDriveStart());

    controllerTable->PutNumber("Left Stick Press", GetDriveLeftStickPress());
    controllerTable->PutNumber("Right Stick Press", GetDriveRightStickPress());

    controllerTable->PutNumber("Home", GetDriveHomeButton());
    controllerTable->PutNumber("RightAnalog", GetDriveRightAnalogButton());

    controllerTable->PutNumber("PS4", GetDrivePS4Button());
    controllerTable->PutNumber("Touchpad", GetDriveTouchpadButton());

}