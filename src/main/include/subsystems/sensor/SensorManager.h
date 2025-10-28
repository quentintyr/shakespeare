#pragma once

#include <vector>
#include <atomic>
#include <thread>
#include <frc/Ultrasonic.h>

#include "Constants.h"
#include "subsystems/sensor/UltraSonicSubsystem.h"
#include "subsystems/sensor/InfraRedSubsystem.h"


class SensorManager
{
public:
    SensorManager();
    ~SensorManager();
    void SensorManagerStartThread();
    void SensorWorker();

private:
    std::thread workerThread;
    std::atomic<bool> stopThread;

    std::unique_ptr<UltraSonicSubsystem> ultraSonic;
    std::unique_ptr<InfraRedSubsystem> infraRed;

};
