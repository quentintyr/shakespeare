#include "subsystems/ElevatorSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"

#include <chrono>
#include <thread>

#define ELEVATOR_SPEED_RPM 70.f
#define ELEVATOR_PINION_RADIUS 12.746f
#define ENCODER_TICKS_PER_REVOLUTION 1464.f

using namespace ElevatorUpDown;

AMCU* acmu;

std::thread* motorHandlerThread;

std::atomic<float> ElevatorSubsystem::currentPos = std::atomic<float>(0.f);
std::atomic<float> targetPos = std::atomic<float>(-1.f);
std::atomic<bool> shouldStop = std::atomic<bool>(false);
std::atomic<bool> driveFromLimitSwitchToZero = std::atomic<bool>(false);
std::atomic<bool> calibrating{false};

int8_t prevRPM;
int8_t targetRPM;
int prevEncoderSteps = 0;

void motorHandler() {
    // if should stop is not true run loop
    while(!shouldStop.load()) {
        float dist = abs(targetPos - ElevatorSubsystem::currentPos);

        // target position is not -1 and dist is bigger than 0.1
        if(targetPos != -1 && dist > 0.1) {
            // drive up when bigger
            if(targetPos > ElevatorSubsystem::currentPos) {
                targetRPM = ELEVATOR_SPEED_RPM * (1 - exp(-dist / 5.f));

                if(targetRPM > ELEVATOR_SPEED_RPM)
                    targetRPM = ELEVATOR_SPEED_RPM;

                if(targetRPM < 5)
                    targetRPM = 5;
            }
            // drive down when smaller
            else {
                targetRPM = -ELEVATOR_SPEED_RPM * (1 - exp(-dist / 5.f));
                
                if(targetRPM < -ELEVATOR_SPEED_RPM)
                    targetRPM = -ELEVATOR_SPEED_RPM;
            }
        // set target rpm to stop
        }else if(targetRPM != 0) {
            targetRPM = 0;
        }
        frc::SmartDashboard::PutString("targetRPM", std::to_string(targetRPM));

        // help
        if(!calibrating && !driveFromLimitSwitchToZero && targetRPM != prevRPM) {
            acmu->setRPM(MOTOR_0, targetRPM);
            prevRPM = targetRPM;
        }
        
        float currentPos = ElevatorSubsystem::currentPos.load();
        int newEncoderSteps = acmu->getEncoder(MOTOR_0) - prevEncoderSteps;
        ElevatorSubsystem::currentPos.store(currentPos + ((newEncoderSteps * ELEVATOR_PINION_RADIUS) / ENCODER_TICKS_PER_REVOLUTION));
        prevEncoderSteps += newEncoderSteps;

        // when true top moving to zero#
        if(driveFromLimitSwitchToZero) {
            if(ElevatorSubsystem::currentPos >= 0) {
                acmu->setRPM(MOTOR_0, 0);
                driveFromLimitSwitchToZero.store(false);
            }else if(newEncoderSteps < 5) {
                acmu->setRPM(MOTOR_0, 30);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        frc::SmartDashboard::PutString("Current ElevatorSubsystem pos", std::to_string(currentPos));
        std::this_thread::sleep_for(std::chrono::nanoseconds(30));
    }
}


// destroy the thread if not needed anymore
void ElevatorSubsystem::destroy() {
    shouldStop.store(true);
    if(motorHandlerThread->joinable())
        motorHandlerThread->join();

    delete motorHandlerThread;
}

void ElevatorSubsystem::init(AMCU* p_acmu) {
    // init when the robot is starting
    acmu = p_acmu;
    acmu->setLimitSwitches(MOTOR_0, 0, 1, 0, 0);
    acmu->registerLimitSwitchCallback(&limitswitchcallback);

    // starting the thread with the motorHandler function
    motorHandlerThread = new std::thread(motorHandler);
}

// move the ElevatorSubsystem to the target position
void ElevatorSubsystem::moveTo(const float p_targetPos) {
    targetPos.store(p_targetPos);
}

// calibrating the ElevatorSubsystem motor
void ElevatorSubsystem::calibrate() {
    frc::SmartDashboard::PutString("calibrating", "ElevatorSubsystem");
    acmu->setRPM(MOTOR_0, -15); // always drive down when calibrating to press limit switch
    // setting bool for calibration to true
    calibrating.store(true);
}

// waits until limit switch is pressed
void ElevatorSubsystem::limitswitchcallback(uint8_t motorNr, uint8_t high) {
    // check if the calibrating is true
    if(calibrating.load()) {
        acmu->setRPM(MOTOR_0, 30);
        currentPos.store(-0.8f);
        calibrating.store(false);
        driveFromLimitSwitchToZero.store(true); // set true 
    }
}