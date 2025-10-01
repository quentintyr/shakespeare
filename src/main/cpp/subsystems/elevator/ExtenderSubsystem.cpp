#include "subsystems/ExtenderSubsystem.h"
#include "utilities/LoggingSystem.h"
#include "studica/Servo.h"
#include "studica/ServoContinuous.h"
#include <frc/DigitalInput.h>
#include <frc/Timer.h>
#include "Constants.h"


studica::Servo ExtenderServo{Constants::EXTENDER_SERVO_PORT};
frc::DigitalInput LimitSwitchStopBack(Constants::LIMIT_SWITCH_STOP_BACK_PORT); // Lower
frc::DigitalInput LimitSwitchStopFront(Constants::LIMIT_SWITCH_STOP_FRONT_PORT); // Upper
frc::Timer ExtenderTimer;

bool ExtenderInitialized = false;
bool TimerDone = false;


ExtenderSubsystem::ExtenderSubsystem() {}


void ExtenderSubsystem::InitExtenderSubsystem() {

    // drive forward once to initialize extender and get time
    if(!ExtenderInitialized) {
        ExtenderServo.Set(Constants::EXTENDER_DRIVE_FORWARD);
        ExtenderInitialized = true;
    }

    // print max extender time once
    if(TimerDone) {
        LOG_INFO(MaxTimeFrontToBack);
        TimerDone = false;
        ExtenderTimer.Reset();
    }

    bool BackPressed = LimitSwitchStopBack.Get();
    bool FrontPressed = LimitSwitchStopFront.Get();

    if(BackPressed) {
        LOG_INFO("Back pressed.");
        ExtenderServo.Set(Constants::EXTENDER_DRIVE_STOP);
        ExtenderTimer.Stop();
        MaxTimeFrontToBack = ExtenderTimer.Get();
        LOG_INFO("Timer Stopped");
        TimerDone = true;
    }
    if(FrontPressed) {
        LOG_INFO("Front pressed.");
        ExtenderServo.Set(Constants::EXTENDER_DRIVE_STOP);
        ExtenderTimer.Start();
        LOG_INFO("Timer started");
        ExtenderServo.Set(Constants::EXTENDER_DRIVE_BACKWARD);
    }


}

double ExtenderSubsystem::getMaxTimeFrontToBack() {

    return MaxTimeFrontToBack;
}