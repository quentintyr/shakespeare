#pragma once

#include "studica/Lidar.h"
#include "Constants.h"

/**
 * kUSB1 = Top USB 2.0 port of VMX
 * kUSB2 = Bottom USB 2.0 port of VMX
 */


class LidarSubsystem
{
public:
    LidarSubsystem();
    ~LidarSubsystem();
    void LidarStartThread();
    double getMedianDistanceOfAngle(int angle);

private:
    void LidarWorker();

};