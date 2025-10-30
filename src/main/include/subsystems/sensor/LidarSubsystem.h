#pragma once

#include "studica/Lidar.h"
#include "Constants.h"

#include <memory>
#include <mutex>

class LidarSubsystem {
public:
    LidarSubsystem();
    ~LidarSubsystem();

    void UpdateLidar();
    double getMedianDistanceOfAngle(int angle);

private:
    std::unique_ptr<studica::Lidar> lidar;
    studica::Lidar::ScanData cachedScanData;
    std::mutex initMutex;
};
