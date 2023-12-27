#ifndef AM2302_H
#define AM2302_H

#ifndef CREDENTIALS_H
#include "credentials.h"
#endif

#include "DHTesp.h"
#include "HARestAPI.h"
#include <sstream>

class Am2302
{
public:
    /// @brief Configure sensor.
    void setup(uint8_t pin);

    /// @brief Loop until esp died.
    /// @param deviceName Name of your device listed in HomeAssistant.
    /// @param measurementDelay Delay between measurements, i.e. 5000ms for measuring each 5s.
    void loop(String deviceName, unsigned measurementDelay);

    /// @brief Prints humidity and temperature on `Serial`.
    /// @param h humidity
    /// @param t temperature
    void print(float h, float t) const;
    
    /// @brief Sending values to Home Assistant.
    /// @param deviceName DeviceName (chose whatever you like)
    /// @param h Humidity in %
    /// @param t Temperature in ˚C
    /// @return error code
    int sendToHA(String deviceName, float h, float t);
};

#endif