# How to set up

Add a `credentials.h` like so

```C++
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

// WiFi credentials:
const char *ssid = "ssid-name";
const char *password = "password-better-choose-a-good-one";
const IPAddress *ap_ip(192, 168, 0, 2);
const IPAddress *ap_gateway(192, 168, 0, 1);
const IPAddress *ap_subnet(255, 255, 255, 0);

#endif
```

to do not store credentials in git.

I'll add a circuit diagram soon!
