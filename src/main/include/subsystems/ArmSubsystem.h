#pragma once

enum class ArmState{
    Error,
    Idle,
    Calibrate,
    HighPick,
    GroundPick,
    DefaultPick
};

class ArmSubsystem {

public:
    ArmSubsystem();
    ~ArmSubsystem();

private:
    double GetGripperAngle();
};

