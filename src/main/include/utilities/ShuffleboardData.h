#pragma once

#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>
#include <networktables/NetworkTableEntry.h>
#include <vector>
#include <string>
#include "utilities/LoggingSystem.h"

// fuck this shit

class ShuffleboardData {
public:
    ShuffleboardData();
    void Periodic(); // Call regularly, e.g. from RobotPeriodic

private:
    struct ButtonAction {
        std::string label;
        std::function<void()> action;
        nt::NetworkTableEntry entry;
        bool lastState;
    };

    std::vector<ButtonAction> m_buttons;
};