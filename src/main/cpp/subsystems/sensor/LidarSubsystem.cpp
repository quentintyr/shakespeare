#include "subsystems/LidarSubsystem.h"
#include "utilities/LoggingSystem.h"
#include "studica/Cobra.h"

studica::Lidar lidar{studica::Lidar::Port::kUSB1};

// Scan data
 struct
studica::Lidar::ScanData getLidarData;

LidarSubsystem::LidarSubsystem() {

    lidar.Start();
    lidar.EnableFilter(studica::Lidar::Filter::kMEDIAN, true);

    std::string logMsg << "Angle: " << getLidarData.angle[180] << "˚, Distance: " << getLidarData.distance[180] / 10 << "cm" << std::endl; 
    LOG_INFO(logMsg);
}


double LidarSubsystem::getMedian()
{
    double getLidarData = lidar.GetData();
    return getLidarData;
}

double LidarSubsystem::getAngle()
{

}

double LidarSubsystem::getDistance()
{

}

