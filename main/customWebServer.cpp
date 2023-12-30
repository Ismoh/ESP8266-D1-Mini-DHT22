#include "customWebServer.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <WiFiClient.h>
#include <ElegantOTA.h>

#define ELEGANTOTA_USE_ASYNC_WEBSERVER 1
#define OTA_MODE_FIRMWARE 1
#define OTA_MODE_FILESYSTEM 0
#define ELEGANTOTA_DEBUG 1
#define UPDATE_DEBUG 1

AsyncWebServer server(SECRET_WEB_SERVER_PORT);
unsigned long ota_progress_millis = 0;

void onOTAStart()
{
    Serial.println("OTA update started!");
}

void onOTAProgress(size_t current, size_t final)
{
    if (millis() - ota_progress_millis > 1000)
    {
        ota_progress_millis = millis();
        Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
    }
}

void onOTAEnd(bool success)
{
    if (success)
    {
        Serial.println("OTA update finished successfully!");
        ESP.restart();
    }
    else
    {
        Serial.println("There was an error during OTA update!");
    }
}

void CustomWebServer::setup()
{
    ElegantOTA.begin(&server, SECRET_OTA_USER, SECRET_OTA_PASSWORD);
    ElegantOTA.onStart(onOTAStart);
    ElegantOTA.onProgress(onOTAProgress);
    ElegantOTA.onEnd(onOTAEnd);
    //Serial.println("ElegantOTA set up");

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->redirect("https://www.google.com"); });
    server.begin();
    //Serial.println("HTTP server started");
}

void CustomWebServer::loop()
{
    ElegantOTA.loop();
}
