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
    void InfraRedSubsystemStartThread();
    double GetIRLeftDistance();
    double GetIRRightDistance();
    bool IRDistanceSimilar();

private:
    void IRWorker();
    double getMedian(std::vector<double> &values);
    double irLeftValue;
    double irRightValue;

    frc::AnalogInput *irSideRight;
    frc::AnalogInput *irSideLeft;
    std::vector<double> irSideLeftValueList;
    std::vector<double> irSideRightValueList;
    std::thread irWorkerThread;
    std::atomic<bool> irStopThread;
};



