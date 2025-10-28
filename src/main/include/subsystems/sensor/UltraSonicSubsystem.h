#pragma once
#include <vector>
#include <atomic>
#include <thread>
#include <frc/Ultrasonic.h>
#include "Constants.h"

class UltraSonicSubsystem
{
public:
    UltraSonicSubsystem();
    ~UltraSonicSubsystem();
    double getSonicLeftDistance();
    double getSonicRightDistance();
    void UpdateUltraSonic();

private:
    double getMedian(std::vector<double> &values);
    double leftValue;
    double rightValue;

    frc::Ultrasonic *sideRight;
    frc::Ultrasonic *sideLeft;
    std::vector<double> sideLeftValueList;
    std::vector<double> sideRightValueList;
};
