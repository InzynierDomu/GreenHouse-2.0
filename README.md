# GreenHouse-2.0

- [Description](#Description)
- [Scheme](#Scheme)
- [IDE](#IDE)

## Description

More descriptions are available on the blog: [Projekt GREENHOUSE 2.0 cz.1](http://www.inzynierdomu.pl/projekt-greenhouse-2-0-cz-1/) PL<br>
The development process is presented on live streams [Playlist - live](https://www.youtube.com/playlist?list=PLZ7-be74MkEyWofOm7bbRsfblTcDVo8DT)

## Scheme

Bhe basic part of the driver
[schem](https://www.inzynierdomu.pl/wp-content/uploads/2019/12/kicad_8LYc8QVG40.png)

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
