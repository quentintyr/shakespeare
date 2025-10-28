#pragma once

#include <vector>
#include <atomic>
#include <thread>
#include <frc/AnalogInput.h>
#include <frc2/command/SubsystemBase.h>

class InfraRedSubsystem
{
public:
    InfraRedSubsystem();
    ~InfraRedSubsystem();
    double GetIRLeftDistance();
    double GetIRRightDistance();
    bool IRDistanceSimilar();
    void UpdateInfraRed();

private:
    double getMedian(std::vector<double> &values);
    double irLeftValue;
    double irRightValue;

    frc::AnalogInput *irSideRight;
    frc::AnalogInput *irSideLeft;
    std::vector<double> irSideLeftValueList;
    std::vector<double> irSideRightValueList;
};



