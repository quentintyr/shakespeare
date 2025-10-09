#include "subsystems/LidarSubsystem.h"
#include "utilities/LoggingSystem.h"
#include "studica/Cobra.h"

#include <sstream>  
#include <string>   

studica::Lidar lidar{studica::Lidar::Port::kUSB1};

LidarSubsystem::LidarSubsystem() {
    lidar.Start();
    lidar.EnableFilter(studica::Lidar::Filter::kMEDIAN, true);

    studica::Lidar::ScanData scanData = lidar.GetData();

    std::stringstream ss;
    ss << "Angle: " << scanData.angle[180] << ", Distance: " << scanData.distance[180] / 10 << "cm";
    std::string logMsg = ss.str();
    LOG_INFO(logMsg);
}

double LidarSubsystem::getDistance() {
    studica::Lidar::ScanData data = lidar.GetData();
    return data.distance[180] / 10.0;  // Convert mm to cm
}

double LidarSubsystem::getAngle() {
    studica::Lidar::ScanData data = lidar.GetData();
    return data.angle[180];
}

// double LidarSubsystem::getMedianOffAngle() {
//     studica::Lidar::ScanData data = lidar.GetData();
//     return data.distance[170] / 10.0;  // Example: distance at 170 degrees
// }
