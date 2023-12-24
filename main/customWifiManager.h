#ifndef CustomWifiManager_H
#define CustomWifiManager_H

class CustomWifiManager
{
public:
    /// @brief Set up WifiManager.
    void setup();

    /// @brief Loop until ESP died.
    void loop();
};

#endif