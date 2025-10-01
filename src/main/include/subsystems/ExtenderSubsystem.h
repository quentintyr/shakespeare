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
    InitExtenderSubsystem();
    double getMaxTimeFrontToBack();
private:
    ExtenderState currentState = ExtenderState::Idle;
    double MaxTimeFronToBack = 0.0;
};