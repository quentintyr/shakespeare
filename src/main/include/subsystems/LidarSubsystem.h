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
    // ~UltraSonicSubsystem();
    // void UltraSonicStartThread();
    // double getSonicLeftDistance();
    // double getSonicRightDistance();

private:
    // void UltraSonicWorker();
    double getMedian();

    // frc::Ultrasonic *sideRight;
    // frc::Ultrasonic *sideLeft;
    // std::vector<double> sideLeftValueList;
    // std::vector<double> sideRightValueList;
    // std::thread workerThread;
    // std::atomic<bool> stopThread;
};