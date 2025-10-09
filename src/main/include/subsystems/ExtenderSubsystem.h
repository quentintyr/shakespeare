#pragma once

enum class ExtenderState {
    Error, 
    Idle,
    AtFront,
    AtBack,
    MovingForward,
    MovingBackward
};

class ExtenderSubsystem {
public:
    ExtenderSubsystem();
    void ExtenderSubsystemCurrentState();
    void Periodic();
    double getMaxTimeFrontToBack();
private:
    ExtenderState currentState = ExtenderState::Idle;
    double MaxTimeFrontToBack = 0.0;
};