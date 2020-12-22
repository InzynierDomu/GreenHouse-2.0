# GreenHouse-2.0
* [Scheme](#Scheme)
* [IDE](#IDE)

## Scheme

## IDE
The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc)

###Solving a bug with adafruit/RTC library
Possible problems with build after IDE installed adafruit/RTC:
```
#include <avr/interrupt.h> 
Compiling .pio\build\nodemcuv2\lib145\RTClib\RTClib.cpp.o
```
This requires removing an automatically installed library TinyWireM.

PlatformIO > Libraries > Installed > TinyWireM (remove).

