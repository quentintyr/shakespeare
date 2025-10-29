#include "subsystems/sensor/UltraSonicSubsystem.h"
#include "subsystems/sensor/InfraRedSubsystem.h"
#include "subsystems/sensor/LineFollowerSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include "subsystems/sensor/SensorManager.h"

#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

SensorManager::SensorManager()
{
    stopThread = false;

    ultraSonic = std::make_unique<UltraSonicSubsystem>();
    infraRed = std::make_unique<InfraRedSubsystem>();
}

SensorManager::~SensorManager()
{
    stopThread = true;
    if (workerThread.joinable())
        workerThread.join();
}

void SensorManager::SensorWorker()
{
    while (!stopThread.load())
    {
        ultraSonic->UpdateUltraSonic();
        infraRed->UpdateInfraRed();

        std::this_thread::sleep_for(std::chrono::milliseconds(Constants::Ultrasonic::SENSOR_UPDATE_RATE));
    }
}

void SensorManager::SensorManagerStartThread()
{
    workerThread = std::thread(&SensorManager::SensorWorker, this);
    LOG_THREAD("Sensor Thread initialized.");
}

UltraSonicSubsystem *SensorManager::GetUltraSonicSubsystem()
{
    return ultraSonic.get();
}

InfraRedSubsystem *SensorManager::GetInfraRedSubsystem()
{
    return infraRed.get();
}
