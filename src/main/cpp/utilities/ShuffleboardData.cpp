#include "utilities/ShuffleboardData.h"
#include "utilities/LoggingSystem.h" 

ShuffleboardData::ShuffleboardData() {
    frc::ShuffleboardTab& tab = frc::Shuffleboard::GetTab("Function Tests");

    m_buttons.push_back({"Robot Base",
        [] { LOG_INFO("Calibrating Base"); },
        tab.Add("Start", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Elevator Arm",
        [] { LOG_INFO("Calibrating Elevator Arm"); },
        tab.Add("Elevator Arm", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Elevator Lift",
        [] { LOG_INFO("Calibrating Elevator Lift"); },
        tab.Add("Elevator Lift", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Gripper",
        [] { LOG_INFO("Calibrating Gripper"); },
        tab.Add("Gripper", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Gripper Tilt",
        [] { LOG_INFO("Calibrating Gripper Tilt"); },
        tab.Add("Gripper Tilt", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Elevator Rotate",
        [] { LOG_INFO("Calibrating Elevator Rotate"); },
        tab.Add("Elevator Rotate", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

    m_buttons.push_back({"Camera Test",
        [] { LOG_INFO("Testing Camera detection"); },
        tab.Add("Camera Test", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry(),
        false
    });

}

void ShuffleboardData::Periodic() {
    for (auto& btn : m_buttons) {
        bool state = btn.entry.GetBoolean(false);
        if (state && !btn.lastState) { // Button pressed
            btn.action(); // Call the action
            btn.entry.SetBoolean(false); // Reset the button
        }
        btn.lastState = state;
    }
}