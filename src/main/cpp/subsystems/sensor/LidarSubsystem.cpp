#include "subsystems/sensor/LidarSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include <sstream>
#include <iostream>

LidarSubsystem::LidarSubsystem() {
    lidar = nullptr;
}

LidarSubsystem::~LidarSubsystem() {

}

void LidarSubsystem::UpdateLidar() {
    try {
        if (lidar == nullptr) {
            lidar = std::make_unique<studica::Lidar>(studica::Lidar::Port::kUSB1);
            lidar->Start();
            lidar->EnableFilter(studica::Lidar::Filter::kMEDIAN, true);
        }
        cachedScanData = lidar->GetData();

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

double LidarSubsystem::getMedianDistanceOfAngle(int angle) {
    return cachedScanData.distance[angle];
}
