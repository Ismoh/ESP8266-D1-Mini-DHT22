// ESP8266MOD D1 mini data source:
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Datenblatt.pdf?5384137068277415753
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Pinout_Diagram.pdf?5603303439559815202

#include "customWifiManager.h"
#include "am2302.h"

#define ESP8266 true
#define DHT_PIN D5  // GPIO14 | D5 | IO,SCK

CustomWifiManager customWifiManager;
Am2302 am2302;

void setup()
{
    /*
     * Setup ESP8266
     */
    Serial.begin(115200);

    /*
     * Setup WifiManager
     */
    customWifiManager.setup();

    /*
     * Setup AM2302 (DHT22) sensor
     */
    am2302.setup(DHT_PIN);
}

void loop()
{
    customWifiManager.loop();
    am2302.loop();
}