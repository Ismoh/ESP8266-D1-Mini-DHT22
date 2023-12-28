#include "customWifiManager.h"

WiFiManager wm;

void CustomWifiManager::setup(String deviceName)
{
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
    wm.setClass("invert");    // dark theme
    wm.setScanDispPerc(true); // display percentages instead of graphs for RSSI
    // Do not log passwords..
    wm.setShowPassword(false);
    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();

    // const char *hostname = WiFi.getHostname();
    // const char *extra_text = deviceName.c_str();
    // char *buf = (char *)malloc(strlen(extra_text) + strlen(hostname) + 1);
    // buf[0] = 0;
    // strcat(buf, extra_text);
    // strcat(buf, hostname);
    // WiFi.setHostname(buf);
    // free(buf);
    WiFi.setHostname(deviceName.c_str());

    // Set custom ip for portal
    wm.setAPStaticIPConfig(IPAddress(SECRET_AP_IP), IPAddress(SECRET_AP_GATEWAY), IPAddress(SECRET_AP_SUBNET));
    // Disable debug output
    wm.setDebugOutput(false);
    // Make AP not available for ever (10min)
    wm.setConfigPortalTimeout(600);

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result
    if (!wm.autoConnect(SECRET_SSID, SECRET_PASSWORD))
    {
        Serial.println("Failed to connect to AP!");
        Serial.println("Restarting ESP...");
        ESP.restart();
    }
    else
    {
        Serial.println("Connected to AP '" + WiFi.SSID() + "'!");
    }
}

void CustomWifiManager::loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
}
