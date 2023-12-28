#ifndef CUSTOMWIFIMANAGER_H
#define CUSTOMWIFIMANAGER_H

#ifndef CREDENTIALS_H
#include "credentials.h"
#endif

#include <WiFiManager.h>

class CustomWifiManager
{
public:
    /// @brief Set up WifiManager.
    /// @param deviceName mDNS and HomeAssistant device name.
    void setup(String deviceName);

    /// @brief Loop until ESP died.
    void loop();
};

#endif