#include "Constants.h"
#include "subsystems/sensor/InfraRedSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"

InfraRedSubsystem::InfraRedSubsystem() {
    irSideRight = nullptr;
    irSideLeft = nullptr;
    irStopThread = false;
}

InfraRedSubsystem::~InfraRedSubsystem(){
    stopThread = True;
    if (irWorkerThread.joinable())
        irWorkerThread.join();
    delete irSideLeft;
    delete irSideRight;
}

double InfraRedSubsystem::getMedian(std::vector<double> &values)
{
    if (values.empty())
        return 0.0;
    std::vector<double> sorted = values;
    std::sort(sorted.begin(), sorted.end());
    size_t mid = sorted.size() / 2;
    return sorted[mid];
}

//Create an accessor function
double InfraRedSubsystem::GetIRLeftDistance()
{
    return 0;
}

double InfraRedSubsystem::GetIRRightDistance()
{
    return 0;
}

void InfraRedSubsystem::InfraRedSubsystemStartThread(){
    LOG_THREAD("IR Sensors iniialized.")
}

void InfraRedSubsystem::IRWorker()
{
    IRSideRight = new frc::AnalogInput(Constants::IRSensors::RIGHT);
    IRSideLeft = new frc::AnalogInput(Constants::IRSensors::LEFT);
    
    while (!stopThread)
    {
        if (sideLeftValueList.size() >=9) {
            irLeftValue = getMedian(irSideLeftValueList);
            irSideLeftValueList.erase(irSideLeftValueList.begin())
        }
        if (sideRightValueList.size() >=9) {
            irRightValue = getMedian(irSideRightValueList);
            irSideRightValueList.erase(irSideRightValueList.begin())
        }
        irSideLeftValueList.push_back(irSideLeft->)
        irSideRightValueList
    }

}

bool InfraRedSubsystem::IRDistanceSimilar()
{
    // double IRDistance = GetIRLeftDistance-GetIRRightDistance;

    // if(IRDistance > -1 && IRDistance < 1)
    // {
    //     return true;
    // }

    return false;
}