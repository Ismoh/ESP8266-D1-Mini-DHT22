#ifndef AM2302_H
#define AM2302_H

#include "DHTesp.h"

class Am2302
{
public:
    /// @brief Configure sensor.
    void setup(uint8_t pin);

    /// @brief Loop until esp died.
    void loop();

    /// @brief Prints humidity and temperature on `Serial`.
    /// @param h humidity
    /// @param t temperature
    void print(float h, float t) const;
    
    /// @brief Sending values to Home Assistant.
    /// @param h Humidity in %
    /// @param t Temperature in ˚C
    /// @return error code
    int sendToHA(float h, float t);
};

#endif