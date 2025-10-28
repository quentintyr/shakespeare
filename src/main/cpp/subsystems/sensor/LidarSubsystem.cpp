// #include "subsystems/sensor/LidarSubsystem.h"
// #include "web-ds-logger/src/LoggingSystem.h"
// #include "studica/Cobra.h"

// #include <sstream>  
// #include <string>   

// studica::Lidar lidar{studica::Lidar::Port::kUSB1};

// LidarSubsystem::LidarSubsystem() {
//     lidar.Start();
//     lidar.EnableFilter(studica::Lidar::Filter::kMEDIAN, true);

//     studica::Lidar::ScanData scanData = lidar.GetData();

//     std::stringstream ss;
//     ss << "Angle: " << scanData.angle[180] << ", Distance: " << scanData.distance[180] / 10 << "cm";
//     std::string logMsg = ss.str();
//     LOG_INFO(logMsg);
// }

// LidarSubsystem::~LidarSubsystem() {

// }

// void LidarSubsystem::LidarStartThread() {

// }

// void LidarSubsystem::LidarWorker() {

// }
// /**
//  * Available Angles: 0 - 360 deg
// */
// double LidarSubsystem::getMedianDistanceOfAngle(int angle) {
//     studica::Lidar::ScanData data = lidar.GetData();
//     return data.angle[angle];
// }



