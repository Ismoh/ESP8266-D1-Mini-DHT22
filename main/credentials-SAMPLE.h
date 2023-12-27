// https://www.andreagrandi.it/2020/12/16/how-to-safely-store-arduino-secrets/

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

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
#define SECRET_HA_DNS "192.168.4.2"
#endif

#ifndef SECRET_HA_PORT
#define SECRET_HA_PORT 8123
#endif

#ifndef SECRET_HA_TOKEN
#define SECRET_HA_TOKEN "JWT-TOKEN"
#endif

#endif
