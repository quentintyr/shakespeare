#pragma once

#include <string>

enum class ExtenderState
{
    Error,
    Idle,
    AtFront,
    AtBack,
    MovingForward,
    MovingBackward
};

class ExtenderSubsystem
{
public:
    ExtenderSubsystem();
    void ExtenderSubsystemCurrentState();
    std::string GetCurrentStateString();
    void Periodic();
    double getMaxTimeFrontToBack();
    void calibrate();

private:
    ExtenderState currentState = ExtenderState::Idle;
    double MaxTimeFrontToBack = 0.0;
};