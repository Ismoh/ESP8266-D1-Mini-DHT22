// ESP8266MOD D1 mini data source:
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Datenblatt.pdf?5384137068277415753
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Pinout_Diagram.pdf?5603303439559815202

#include "customWifiManager.h"
#include "am2302.h"
#include "ESP8266WiFi.h"
#include <ESP8266mDNS.h>
//#include <ESP8266WebServer.h> // delete me

// #define ESP8266
#define DHT_PIN D5 // GPIO14 | D5 | IO,SCK
#define DEBUG_OUTPUT Serial

CustomWifiManager customWifiManager;
Am2302 am2302;
String deviceName = SECRET_DEVICE_NAME;

//ESP8266WebServer server(80); // delete me

void setup()
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
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");

    //server.on("/", handle_OnConnect);
    //server.onNotFound(handle_NotFound);

    //server.begin();
    //Serial.println("HTTP server started");
}

void loop()
{
    customWifiManager.loop();
    am2302.loop(deviceName, 0);
    MDNS.update();

    //server.handleClient(); // delete me
}

void handle_OnConnect()
{
    //server.send(200, "text/html", "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"></head><body><h1>Hey there!</h1></body></html>");
}

void handle_NotFound()
{
    //server.send(404, "text/plain", "Not found");
}