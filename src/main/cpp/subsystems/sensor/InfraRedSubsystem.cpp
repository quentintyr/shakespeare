#include "Constants.h"
#include "subsystems/sensor/InfraRedSubsystem.h"
#include "web-ds-logger/src/LoggingSystem.h"

InfraRedSubsystem::InfraRedSubsystem() {
    irSideRight = nullptr;
    irSideLeft = nullptr;
}

InfraRedSubsystem::~InfraRedSubsystem(){
    delete irSideLeft;
    delete irSideRight;
}

void InfraRedSubsystem::UpdateInfraRed()
{
    if (irSideLeft && irSideRight == nullptr) {
         irSideRight = new frc::AnalogInput(Constants::IRSensors::RIGHT);
        irSideLeft = new frc::AnalogInput(Constants::IRSensors::LEFT);
    }

    const size_t maxSamples = 9;
    double vLeft = irSideLeft->GetAverageVoltage();
    double vRight = irSideRight->GetAverageVoltage();

    // guard against zero or tiny voltages
    if (vLeft <= 0.0001) {vLeft = 0.0001;}
    if (vRight <= 0.0001) {vRight = 0.0001;}

    double rawLeft  = std::pow(vLeft,  -1.2045) * 27.726;
    double rawRight = std::pow(vRight, -1.2045) * 27.726 - 1.0;

    irSideLeftValueList.push_back(rawLeft);
    irSideRightValueList.push_back(rawRight);

    if (irSideLeftValueList.size() > maxSamples)
        irSideLeftValueList.erase(irSideLeftValueList.begin());
    if (irSideRightValueList.size() > maxSamples)
        irSideRightValueList.erase(irSideRightValueList.begin());

    if (!irSideLeftValueList.empty())
        irLeftValue = getMedian(irSideLeftValueList);
    if (!irSideRightValueList.empty())
        irRightValue = getMedian(irSideRightValueList);

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

double InfraRedSubsystem::GetIRLeftDistance()
{
    return irLeftValue;
}

double InfraRedSubsystem::GetIRRightDistance()
{
    return irRightValue;
}

bool InfraRedSubsystem::IRDistanceSimilar()
{
    double IRDistance = GetIRLeftDistance()-GetIRRightDistance();
    if(IRDistance > -1 && IRDistance < 1) {return true;}
    return false;
}