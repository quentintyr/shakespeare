// #pragma once

// #include <AMCU.h>
// #include <atomic>

// #define ELEVATOR_HEIGHT 29.0f

// namespace ElevatorUpDown {
//     namespace elevator {
//         extern std::atomic<float> currentPos;

//         void init(AMCU* acmu);
//         void destroy();

//         void moveTo(const float targetPos);

//         void calibrate();
//         void limitswitchcallback(uint8_t motorNr, uint8_t high);
//     }
// }