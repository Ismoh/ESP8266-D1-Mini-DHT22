// ESP8266MOD D1 mini data source:
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Datenblatt.pdf?5384137068277415753
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Pinout_Diagram.pdf?5603303439559815202

#include "am2302.h"
#include "customWebServer.h"
#include "customWifiManager.h"
#include "ESP8266WiFi.h"
#include <ESP8266mDNS.h>

// #define ESP8266
#define DHT_PIN D5 // GPIO14 | D5 | IO,SCK
#define DEBUG_OUTPUT Serial

Am2302 am2302;
CustomWebServer customWebServer;
CustomWifiManager customWifiManager;
String deviceName = SECRET_DEVICE_NAME;


void setup(void)
{
    /*
     * Setup ESP8266
     */
    Serial.begin(115200);

    /*
     * Setup WifiManager
     */
    customWifiManager.setup(deviceName);

    /*
     * Setup AM2302 (DHT22) sensor
     */
    am2302.setup(DHT_PIN);

    /*
     * Setup mDNS
     */
    if (!MDNS.begin(deviceName))
    { // Set the hostname to deviceName + ".local"
        Serial.println("Error setting up MDNS responder!");
        Serial.println("Answer:");
        Serial.println(MDNS.answerIP(MDNS.ServiceQueryAnswerType_IP4Address));
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");

    /*
     * Setup WebServer
     */
    customWebServer.setup();

}

void loop(void)
{
    customWifiManager.loop();
    am2302.loop(deviceName, 0);
    MDNS.update();
    customWebServer.loop();
}
