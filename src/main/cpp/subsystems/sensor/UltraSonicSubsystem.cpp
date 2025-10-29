#include "subsystems/sensor/UltraSonicSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"
#include <algorithm>
#include <iostream>

UltraSonicSubsystem::UltraSonicSubsystem()
{
    sideRight = nullptr;
    sideLeft = nullptr;
    leftValue = 0.0;
    rightValue = 0.0;
}

UltraSonicSubsystem::~UltraSonicSubsystem()
{
    if (sideRight != nullptr)
    {
        delete sideRight;
        sideRight = nullptr;
    }
    if (sideLeft != nullptr)
    {
        delete sideLeft;
        sideLeft = nullptr;
    }
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

void UltraSonicSubsystem::UpdateUltraSonic()
{
    if (sideLeft == nullptr && sideRight == nullptr)
    {
        try
        {
            sideRight = new frc::Ultrasonic(Constants::Ultrasonic::RIGHT_TRIG_PORT, Constants::Ultrasonic::RIGHT_ECHO_PORT);
            sideLeft = new frc::Ultrasonic(Constants::Ultrasonic::LEFT_TRIG_PORT, Constants::Ultrasonic::LEFT_ECHO_PORT);
            sideRight->SetAutomaticMode(true);
            sideLeft->SetAutomaticMode(true);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    if (sideLeft != nullptr && sideRight != nullptr)
    {
        try
        {
            if (sideLeftValueList.size() >= 9)
            {
                leftValue = getMedian(sideLeftValueList);
                sideLeftValueList.erase(sideLeftValueList.begin());
            }
            if (sideRightValueList.size() >= 9)
            {
                rightValue = getMedian(sideRightValueList);
                sideRightValueList.erase(sideRightValueList.begin());
            }
            sideLeftValueList.push_back(sideLeft->GetRangeMM());
            sideRightValueList.push_back(sideRight->GetRangeMM());
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

double UltraSonicSubsystem::getSonicRightDistance()
{
    return rightValue;
}

double UltraSonicSubsystem::getSonicLeftDistance()
{
    return leftValue;
}
