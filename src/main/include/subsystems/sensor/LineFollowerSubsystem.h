#pragma once
#include "studica/Cobra.h"


class LineFollower {
public:
    LineFollower(float voltage = 5.0F);
    void InitLineFollower();
    void update(); // should update periodically
    bool isLineDetected() const;

    float getVoltage() const;

private:
    studica::Cobra cobra;
    int sensorChannel = 0; // Der einzige Kanal, z. B. ADC0
    float sensorVoltage = 0.0F;
    const float LINE_THRESHOLD = 1.5F;
};