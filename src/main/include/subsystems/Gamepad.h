#pragma once

#include <frc2/command/SubsystemBase.h>

class Gamepad : public frc2::SubsystemBase {
public:
    // Joystick Axes
    double GetLeftDriveX(void);   // Left X (axis 0)
    double GetLeftDriveY(void);   // Left Y (axis 1)
    double GetRightDriveX(void);  // Right X (axis 3)
    double GetRightDriveY(void);  // Right Y (axis 4)

    double GetLeftTrigger(void);  // Left Trigger (axis 2)
    double GetRightTrigger(void); // Right Trigger (axis 5)

    // Button Functions
    bool GetDriveLeftBumper(void);        // Left bumper (button 5)
    bool GetDriveRightBumper(void);       // Right bumper (button 6)
    bool GetDriveBack(void);              // Back (button 7)
    bool GetDriveStart(void);             // Start (button 8)

    bool GetDriveAButton(void);           // A (button 1)
    bool GetDriveXButton(void);           // X (button 3)
    bool GetDriveYButton(void);           // Y (button 4)
    bool GetDriveBButton(void);           // B (button 2)

    bool GetDriveHomeButton(void);        // Home (button 11)
    bool GetDriveLeftStickPress(void);    // Left stick press (button 9)
    bool GetDriveRightStickPress(void);   // Right stick press (button 10)

    bool GetDriveRightAnalogButton(void); // Not used on this controller
    bool GetDrivePS4Button(void);         // Not used on this controller
    bool GetDriveTouchpadButton(void);    // Not used on this controller

    // D-pad / POV
    int GetPOV(void);                     // returns -1 or angle in degrees
    bool IsDPadUp(void);
    bool IsDPadRight(void);
    bool IsDPadDown(void);
    bool IsDPadLeft(void);

    void Periodic() override;

public:
    static constexpr int DRIVE_USB_PORT = 0;

private:

    // Joystick Axis
    static constexpr int LEFT_ANALOG_X   = 0;
    static constexpr int LEFT_ANALOG_Y   = 1;
    static constexpr int LEFT_TRIGGER_A  = 2;

    static constexpr int RIGHT_ANALOG_X  = 3;
    static constexpr int RIGHT_ANALOG_Y  = 4;
    static constexpr int RIGHT_TRIGGER_A = 5;

    // Button Map
    static constexpr int A_BUTTON            = 1;
    static constexpr int B_BUTTON            = 2;
    static constexpr int X_BUTTON            = 3;
    static constexpr int Y_BUTTON            = 4;
    static constexpr int LEFT_BUMPER         = 5;
    static constexpr int RIGHT_BUMPER        = 6;
    static constexpr int BACK                = 7;
    static constexpr int START               = 8;
    static constexpr int LEFT_STICK_PRESS    = 9;
    static constexpr int RIGHT_STICK_PRESS   = 10;
    static constexpr int HOME_BUTTON         = 11;

    // unused
    static constexpr int RIGHT_ANALOG_BUTTON = 12;
    static constexpr int PS4_BUTTON          = 13;
    static constexpr int TOUCHPAD_BUTTON     = 14;
};