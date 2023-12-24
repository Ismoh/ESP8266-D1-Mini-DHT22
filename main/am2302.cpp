#include "am2302.h"

#define ESP8266 true // Espressif Wemos D1 R2 & mini
#define DHT_PIN 14   // GPIO14 | D5 | IO,SCK

DHTesp dhtEsp;

void Am2302::setup(uint8_t pin)
{
    dhtEsp.setup(pin, DHTesp::AM2302);
}

void Am2302::loop()
{
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
        print(h, t);
    }

    // delay(2000);
}

void Am2302::print(float h, float t) const
{
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

int Am2302::sendToHA(float h, float t)
{
    // Not yet implemented.
    return 0;
}
