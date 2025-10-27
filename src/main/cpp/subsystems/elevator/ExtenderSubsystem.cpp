#include "subsystems/elevator/ExtenderSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include "Constants.h"

#include "studica/Servo.h"
#include "studica/ServoContinuous.h"

#include <frc/DigitalInput.h>
#include <frc/Timer.h>


studica::Servo ExtenderServo{Constants::Extender::SERVO_PORT};
frc::DigitalInput LimitSwitchStopBack(Constants::Extender::LIMIT_SWITCH_STOP_BACK_PORT); // Lower
frc::DigitalInput LimitSwitchStopFront(Constants::Extender::LIMIT_SWITCH_STOP_FRONT_PORT); // Upper
frc::Timer ExtenderTimer;

bool ExtenderInitialized = false;
bool TimerDone = false;

ExtenderSubsystem::ExtenderSubsystem() {}


void ExtenderSubsystem::ExtenderSubsystemCurrentState() {

    switch (ExtenderSubsystem::currentState) {
        case ExtenderState::Idle:
            // drive forward once to initialize extender and get time
            if(!ExtenderInitialized) {
                LOG_INFO("Extender is Idle");
                ExtenderServo.Set(Constants::Extender::DRIVE_FORWARD);
                ExtenderInitialized = true;
                currentState = ExtenderState::MovingForward;
            }
            if(TimerDone) {
                LOG_INFO(MaxTimeFrontToBack);
                TimerDone = false;
                ExtenderTimer.Reset();
            }
            break;

        case ExtenderState::AtFront:
            ExtenderServo.Set(Constants::Extender::DRIVE_BACKWARD);
            currentState = ExtenderState::MovingBackward;
            break;

        case ExtenderState::AtBack:
            currentState = ExtenderState::Idle;
            break;

        case ExtenderState::MovingForward:
            if(LimitSwitchStopFront.Get()) {
                LOG_INFO("LimitSwitch Front pressed.");
                ExtenderServo.Set(Constants::Extender::DRIVE_STOP);
                ExtenderTimer.Start();
                LOG_INFO("Timer started");
                currentState = ExtenderState::AtFront;
            }
            break;

        case ExtenderState::MovingBackward:
            if(LimitSwitchStopBack.Get()) {
                LOG_INFO("LimitSwitch Back pressed.");
                ExtenderServo.Set(Constants::Extender::DRIVE_STOP);
                ExtenderTimer.Stop();
                ExtenderSubsystem::MaxTimeFrontToBack = ExtenderTimer.Get();
                LOG_INFO("Timer Stopped");
                TimerDone = true;
                currentState = ExtenderState::AtBack;
            }
            break;
        default:
            // currentState = ExtenderState::Error
            LOG_ERROR("Extender State Failed");
            break;
    }
}

void ExtenderSubsystem::Periodic(){

}

double ExtenderSubsystem::getMaxTimeFrontToBack() {
    return MaxTimeFrontToBack;
}