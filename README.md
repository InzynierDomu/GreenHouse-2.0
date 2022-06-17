# GreenHouse-2.0

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/InzynierDomu/GreenHouse-2.0/CI?logo=github&style=flat-square)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/InzynierDomu/GreenHouse-2.0?style=flat-square)
<a href="https://inzynierdomu.github.io/sun_clock/">![GitHub docs deployments](https://img.shields.io/github/deployments/InzynierDomu/GreenHouse-2.0/github-pages?label=docs&logo=BookStack&logoColor=white&style=flat-square)</a>
<a href="https://discord.gg/KmW6mHdg">![Discord](https://img.shields.io/discord/815929748882587688?logo=discord&logoColor=green&style=flat-square)</a>
![GitHub](https://img.shields.io/github/license/InzynierDomu/GreenHouse-2.0?style=flat-square)
<a href="https://tipo.live/p/inzynierdomu">![support](https://img.shields.io/badge/support-tipo.live-yellow?style=flat-square)</a>

- [Description](#Description)
- [Scheme](#Scheme)
- [IDE](#IDE)

## Description

More descriptions are available on the blog: [Projekt GREENHOUSE 2.0 cz.1](http://www.inzynierdomu.pl/projekt-greenhouse-2-0-cz-1/) PL<br>
The development process is presented on live streams [Playlist - live](https://www.youtube.com/playlist?list=PLZ7-be74MkEyWofOm7bbRsfblTcDVo8DT)

## Scheme

The basic part of the driver.
![schem](https://www.inzynierdomu.pl/wp-content/uploads/2019/12/kicad_8LYc8QVG40.png)

Part list:
- BT1 Battery CR2025 3,3V
- J1 SD card socket
- Brd1 OLED screen 128x64 SSD1306
- U2 DHT22 humidity and temperature sensor
- U3 EEPROM 24C16
- U4 ESP8266 NodeMCU
- U5 RTC DS1307
- Y1 Oscillator 32,788 KHz

Parts optional (on I2C)
- MCP23017 (max 8 pcs)
- PCF8591 (max 8 pcs)

## IDE

The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc)
<br><br>
Formatting is done using clang-format. The description of the tool configuration is in the [video](https://youtu.be/xxuaOG0WjIE).

### Solving a bug with adafruit/RTC library

Possible problems with build after IDE installed adafruit/RTC:

```
#include <avr/interrupt.h>
Compiling .pio\build\nodemcuv2\lib145\RTClib\RTClib.cpp.o
```

This requires removing an automatically installed library TinyWireM.

PlatformIO > Libraries > Installed > TinyWireM (remove).
