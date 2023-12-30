// https://www.andreagrandi.it/2020/12/16/how-to-safely-store-arduino-secrets/

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#ifndef SECRET_DEVICE_NAME
#define SECRET_DEVICE_NAME "esp8266-thcs-1"
#endif

#ifndef SECRET_SSID
#define SECRET_SSID "WifiSSID"
#endif

#ifndef SECRET_PASSWORD
#define SECRET_PASSWORD "WifiPassword"
#endif

#ifndef SECRET_AP_IP
#define SECRET_AP_IP 192, 168, 4, 1
#endif

#ifndef SECRET_AP_GATEWAY
#define SECRET_AP_GATEWAY 192, 168, 4, 1
#endif

#ifndef SECRET_AP_SUBNET
#define SECRET_AP_SUBNET 255, 255, 255, 0
#endif

#ifndef SECRET_HA_DNS
#define SECRET_HA_DNS "http://homeassistant.local"
#endif

#ifndef SECRET_HA_PORT
#define SECRET_HA_PORT 8123
#endif

#ifndef SECRET_HA_TOKEN
#define SECRET_HA_TOKEN "JWT-TOKEN"
#endif

#ifndef SECRET_WEB_SERVER_PORT
#define SECRET_WEB_SERVER_PORT 80
#endif

#ifndef SECRET_OTA_USER
#define SECRET_OTA_USER "OtaUser"
#endif

#ifndef SECRET_OTA_PASSWORD
#define SECRET_OTA_PASSWORD "OtaPassword"
#endif

#endif
