#include "subsystems/sensor/UltraSonicSubsystem.h"
#include "subsystems/sensor/InfraRedSubsystem.h"
#include "subsystems/sensor/LidarSubsystem.h"
#include "subsystems/sensor/LineFollowerSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include "subsystems/sensor/SensorManager.h"

#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

SensorManager::SensorManager() {
    stopThread = false;

    ultraSonic = std::make_unique<UltraSonicSubsystem>();
    infraRed   = std::make_unique<InfraRedSubsystem>();
    lidar      = std::make_unique<LidarSubsystem>();
}

SensorManager::~SensorManager()
{
    stopThread = true;
    if (workerThread.joinable())
        workerThread.join();
}

void SensorManager::SensorWorker()
{
    LOG_THREAD("Starting UltraSonic Sensors");
    ultraSonic->UpdateUltraSonic();
    LOG_THREAD("Starting InfraRed Sensors");
    infraRed->UpdateInfraRed();
    // LOG_THREAD("Starting Lidar");
    // LOG_THREAD("Starting LineFollower");
    std::this_thread::sleep_for(std::chrono::milliseconds(Constants::Ultrasonic::SENSOR_UPDATE_RATE));
}

void SensorManager::SensorManagerStartThread()
{
    workerThread = std::thread(&SensorManager::SensorWorker, this);
    LOG_THREAD("Sensor Thread initialized.");

}

