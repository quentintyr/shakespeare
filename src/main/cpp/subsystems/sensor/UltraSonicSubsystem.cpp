#include "subsystems/UltraSonicSubsystem.h"
#include "utilities/LoggingSystem.h"
#include <algorithm>
#include <iostream>

UltraSonicSubsystem::UltraSonicSubsystem() {
    sideRight = nullptr;
    sideLeft = nullptr;
    stopThread = false;
}

UltraSonicSubsystem::~UltraSonicSubsystem()
{
    stopThread = true;
    if (workerThread.joinable())
        workerThread.join();
    delete sideRight;
    delete sideLeft;
}

double UltraSonicSubsystem::getMedian(std::vector<double> &values)
{
    if (values.empty())
        return 0.0;
    std::vector<double> sorted = values;
    std::sort(sorted.begin(), sorted.end());
    size_t mid = sorted.size() / 2;
    return sorted[mid];
}

void UltraSonicSubsystem::UltraSonicWorker()
{
    sideRight = new frc::Ultrasonic(Constants::RIGHT_TRIG_PORT, Constants::RIGHT_ECHO_PORT);
    sideLeft = new frc::Ultrasonic(Constants::LEFT_TRIG_PORT, Constants::LEFT_ECHO_PORT);
    sideRight->SetAutomaticMode(true);
    sideLeft->SetAutomaticMode(true);

    while (!stopThread)
    {
        if (sideLeftValueList.size() >= 9)
        {
            double leftValue = getMedian(sideLeftValueList);
            sideLeftValueList.erase(sideLeftValueList.begin());
            LOG_INFO(leftValue);
        }
        if (sideRightValueList.size() >= 9)
        {
            double rightValue = getMedian(sideRightValueList);
            sideRightValueList.erase(sideRightValueList.begin());
        }
        sideLeftValueList.push_back(sideLeft->GetRangeMM());
        sideRightValueList.push_back(sideRight->GetRangeMM());
        std::this_thread::sleep_for(std::chrono::milliseconds(Constants::SENSOR_UPDATE_RATE));
    }
}

void UltraSonicSubsystem::UltraSonicStartThread()
{
    LOG_INFO("Starting Ultra Sonic Thread...");
    workerThread = std::thread(&UltraSonicSubsystem::UltraSonicWorker, this);
}

double UltraSonicSubsystem::getSonicRightDistance()
{
    return getMedian(sideRightValueList);
}

double UltraSonicSubsystem::getSonicLeftDistance()
{
    return getMedian(sideLeftValueList);
}
