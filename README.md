# Hardware

### ESP8266 Espressif Wemos D1 Mini

ESP branding looks like to be a chaotic mess.
You can clearly see Espressif brand logo on the board, but it's called ESP8266 Wemos D1 Mini?
I bought it on [Amazon.de](https://www.amazon.de/dp/B0CB85Q78G?psc=1&ref=ppx_yo2ov_dt_b_product_details).
Datasheet can be found [here](https://www.espressif.com/sites/default/files/documentation/0a-esp8266ex_datasheet_en.pdf).

### DHT22 (AM2302) Temperature and Humidity Sensor

Datasheet can be found [here](https://cdn.shopify.com/s/files/1/1509/1638/files/DHT_22_-_AM2302_Temperatur_und_Luftfeuchtigkeitssensor_Datenblatt.pdf?11983326290748777409).

## Setup

Copy and paste `credentials.h-SAMPLE` to `credentials.h` and fill in your credentials appropriately, but double check to **do not store credentials in git**.

### Circuit diagram

![Circuit diagram](res/circuit-diagram.png)

### VSCode-Arduino extension setup

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

#### VSCode-Arduino Serial Monitor

- Press `F1` and type `Open Serial Monitor` select `Arduino: Open Serial Monitor`.
