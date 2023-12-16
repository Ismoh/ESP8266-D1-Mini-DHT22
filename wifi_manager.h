// ESP8266MOD D1 mini data source:
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Datenblatt.pdf?5384137068277415753
// https://cdn.shopify.com/s/files/1/1509/1638/files/D1_Mini_Pinout_Diagram.pdf?5603303439559815202

#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include "DHTesp.h"
#include <ESP8266WebServer.h>
#include "credentials.h"

#define ESP8266 true
#define DHT_PIN 14  // GPIO14 | D5 | IO,SCK

WiFiManager wm;
ESP8266WebServer webServer(80);
DHTesp dht;

float temperature;
float humidity;

void setup() {
  /*
  * Setup ESP8266
  */
  Serial.begin(115200);

  /*
  * Setup WifiManager
  */
  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.
  wm.setClass("invert");     // dark theme
  wm.setScanDispPerc(true);  // display percentages instead of graphs for RSSI
  // Do not log passwords..
  wm.setShowPassword(false);
  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();

  const char *hostname = WiFi.getHostname();
  const char *extra_text = "THCSensor-";
  char *buf = (char *)malloc(strlen(hostname) + strlen(extra_text) + 1);
  buf[0] = 0;
  strcat(buf, extra_text);
  strcat(buf, hostname);
  WiFi.setHostname(buf);
  free(buf);

  // Set custom ip for portal
  wm.setAPStaticIPConfig(IPAddress(9, 9, 9, 9), IPAddress(9, 9, 9, 9), IPAddress(255, 255, 255, 0));
  // Disable debug output
  wm.setDebugOutput(false);
  // Make AP not available for ever (10min)
  wm.setConfigPortalTimeout(600);

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result
  if (!wm.autoConnect(ssid, password)) {
    Serial.println("Failed to connect to AP!");
    Serial.println("Restarting ESP...");
    ESP.restart();
  } else {
    Serial.println("Connected to AP '" + WiFi.SSID() + "'!");
  }

  /*
  * Setup DHT22 (AM2302)
  */
  dht.setup(D5, DHTesp::DHT22);

  /*
  * Setup WebServer
  */
  webServer.on("/", handle_OnConnect);
  webServer.onNotFound(handle_NotFound);
  webServer.begin();
  Serial.println("HTTP server started");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  //webServer.handleClient();

  readAndPrintTemperatureAndHumidity();
}

void handle_OnConnect() {
  temperature = dht.getTemperature();  //dht.readTemperature();
  humidity = dht.getHumidity();        //dht.readHumidity();
  webServer.send(200, "text/html", buildHtml(temperature, humidity));
}

void handle_NotFound() {
  webServer.send(404, "text/plain", "Not found");
}

String buildHtml(float _temperature, float _humidity) {
  String page = "<!DOCTYPE html> <html>\n";
  page += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"/>\n";
  page += "<meta charset=\"UTF-8\"/>";
  page += "<meta http-equiv=\"refresh\" content=\"5\"/>";
  page += "<title>WeMos D1 mini Temperature & Humidity Report</title>\n";
  page += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  page += "body{margin-top: 50px;} h1 {color: #444444;margin: 20px auto 30px;}\n";
  page += "h2 {color: #0d4c75;margin: 50px auto 20px;}\n";
  page += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  page += "</style>\n";
  page += "</head>\n";
  page += "<body>\n";
  page += "<div id=\"webpage\">\n";
  page += "<h2>WeMos Lolin D1 mini</h2><h1>Temperature & Humidity Report</h1>\n";

  page += "<p>Temperature: ";
  page += (int)_temperature;
  page += " °C</p>";
  page += "<p>Humidity: ";
  page += (int)_humidity;
  page += " %</p>";

  page += "</div>\n";
  page += "</body>\n";
  page += "</html>\n";
  return page;
}

// https://blog.rolandbaer.ch/tag/wemos-d1-mini/
// https://blog.rolandbaer.ch/2020/03/07/temperatur-und-luftfeuchtigkeit-messen-mit-dem-arduino-nano/


// https://chewett.co.uk/blog/1405/using-the-dht11-temperature-sensor-with-a-wemos-d1-mini-esp8266/
void readAndPrintTemperatureAndHumidity() {
  // Wait two seconds between measurements as the sensor will not measure faster
  delay(dht.getMinimumSamplingPeriod());

  float h = dht.getHumidity();
  float t = dht.getTemperature();

  if (isnan(h)) {
    Serial.println("Error reading humidity!");
  }
  if (isnan(t)) {
    Serial.println("Error reading temperature!");
  }

  humidity = h;
  temperature = t;

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.print("\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  delay(2000);
}
