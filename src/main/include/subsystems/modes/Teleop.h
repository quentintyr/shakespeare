#pragma once

#include "subsystems/amcu/AMCU.h"
#include "subsystems/Gamepad.h"

class Teleop
{
public:
    Teleop(AMCU *amcu, Gamepad *gamepad);

    void Init();
    void Periodic();

private:
    AMCU *m_amcu;
    Gamepad *m_gamepad;

    void HandleDrive();
    void HandleElevatorUpDown();
};
