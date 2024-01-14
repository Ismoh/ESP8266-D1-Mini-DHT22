#include "am2302.h"
#include "ESP8266WiFi.h"

#ifndef DEBUG_AM2302
#define DEBUG_AM2302 1
#endif

DHTesp dhtEsp;
WiFiClient client;
HARestAPI ha(client);
long timer = 0;

void Am2302::setup(uint8_t pin)
{
    dhtEsp.setup(pin, DHTesp::AM2302);

#if DEBUG_AM2302
    ha.setDebugMode(false);
#endif
    ha.setHAServer(SECRET_HA_DNS, SECRET_HA_PORT);
    ha.setHAPassword(SECRET_HA_TOKEN);

    // Optional, but can use SHA1 fingerprint to confirm one is connecting to
    String fingerprint = "35 85 74 EF 67 35 A7 CE 40 69 50 F3 C0 F6 80 CF 80 3B 2E 19";
    ha.setFingerPrint(fingerprint);
}

void Am2302::loop(String deviceName, unsigned measurementDelay)
{
    // Wait async until measurement duration is reached
    if (millis() < measurementDelay + timer)
    {
        timer = millis();
        return;
    }

    delay(dhtEsp.getMinimumSamplingPeriod());

    float h = dhtEsp.getHumidity();
    float t = dhtEsp.getTemperature();

    if (isnan(h))
    {
        Serial.println("Error reading humidity!");
    }
    else if (isnan(t))
    {
        Serial.println("Error reading temperature!");
    }
    else
    {
        if (Serial)
        {
            print(h, t);
        }
        sendToHA(deviceName, h, t);
    }
}

void Am2302::print(float h, float t) const
{
#if DEBUG_AM2302
    return;
#endif
    Serial.print(dhtEsp.getStatusString());
    Serial.print("\t");
    Serial.print(h, 1);
    Serial.print("%");
    Serial.print("\t\t");
    Serial.print(t, 1);
    Serial.print("˚C");
    Serial.print("\t");
    Serial.print(dhtEsp.toFahrenheit(t), 1);
    Serial.print("F");
    Serial.print("\t");
    Serial.print(dhtEsp.computeHeatIndex(t, h, false), 1);
    Serial.print(" H I C");
    Serial.print("\t");
    Serial.print(dhtEsp.computeHeatIndex(dhtEsp.toFahrenheit(t), h, true), 1);
    Serial.println(" H I F");
}

int Am2302::sendToHA(String deviceName, float h, float t)
{
    deviceName.replace("-", "_");
    // https://funprojects.blog/2020/12/12/home-assistant-rest-api/
    String json = "{\"state\": \"" + String(h, 2) + "\", \"attributes\": { \"unit_of_measurement\": \"%\", \"friendly_name\": \"" + deviceName.c_str() + "\" }}";
    ha.sendCustomHAData("/api/states/sensor." + deviceName + "_humidity", json);
    json = "{\"state\": \"" + String(t, 2) + "\", \"attributes\": { \"unit_of_measurement\": \"C\", \"friendly_name\": \"" + deviceName.c_str() + "\" }}";
    ha.sendCustomHAData("/api/states/sensor." + deviceName + "_temperature", json);
    json = "{\"state\": \"" + String(WiFi.RSSI()) + "\", \"attributes\": { \"unit_of_measurement\": \"dBm\", \"friendly_name\": \"" + deviceName.c_str() + "\" }}";
    ha.sendCustomHAData("/api/states/sensor." + deviceName + "_wifi_rssi", json);
    return 0;
}
