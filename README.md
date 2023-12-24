# How to set up

Add a `credentials.h` like so

```C++
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

// WiFi credentials:
const char *ssid = "ssid-name";
const char *password = "password-better-choose-a-good-one";
const IPAddress ap_ip(192, 168, 0, 2);
const IPAddress ap_gateway(192, 168, 0, 1);
const IPAddress ap_subnet(255, 255, 255, 0);

#endif
```

to do not store credentials in git.

I'll add a circuit diagram soon!

## VSCode-Arduino extension setup

- Install [VSCode](https://code.visualstudio.com/)
- Install [Arduino CLI](https://arduino.github.io/arduino-cli/0.21/installation/#download)
  - Put the `arduino-cli.exe` for example in\
  `C:\Program Files\Arduino-CLI` and run

  ```cmd
  set PATH=%PATH%;C:\Program Files\Arduino-CLI
  ```

- and/or install [Arduino IDE](https://www.arduino.cc/en/Main/Software), but I prefer **CLI**
- Install the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
- Press `F1` and type `Select Board` select `Arduino: Board Manager`. Expand `Type` and select ESP8266. Select the latest version and install it.
- Press `F1` and type `Select Port` select `Arduino: Select Serial Port`. Select the port your ESP8266 is connected to.
- Press `Ctrl+Shift+I` for rebuilding IntelliSense Configuration.
- Press `Ctrl+Shift+R` for compiling the sketch. This will generate a new Arduino configuration in the `c_cpp_properties.json` file. Then reload VSCode.
- Use `Ctrl+Alt+U` to upload the sketch to the board.

### VSCode-Arduino Serial Monitor

- Press `F1` and type `Open Serial Monitor` select `Arduino: Open Serial Monitor`.
