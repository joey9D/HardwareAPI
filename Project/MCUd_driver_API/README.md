# MCU-driver API

Driver API für verschiedene Mikrocontroller, hauptsächlich STM32 MCUs.
(Zukünfitg auch ESP32). 
Fokus liegt auf der Modularität, Abstraktion und einfache Anwendung.
Crossplattform kompatibel.


## Projektstruktur

- Drivers:
- Peripherals:
- CMSIS:

## Wie sieht es im Code aus?

```cpp
#include "main.h"


int main()
{
    periph::systick::init();

    // Externe LED
    periph::gpio_stm32c0 led(periph::gpio_stm32c0::port::a, 9, periph::gpio::mode::digital_output);

    while(1)
    {
        led.toggle();
        periph::systick::delay(1000);
    }

    return 0;
}
```

## Wie wird es gebuilded?

```bash
git clone https://github.com/joey9D/HardwareAPI.git
cd HardwareAPI/Projects/MyMCU

# make build directory
make prepare

# default target is STM32C0
make
```

**Weitere `make` Befehle:**

- `make flash` $\rightarrow$ Lade das Applikationspogramm auf das Target.
- `make erase` $\rightarrow$ Lösche den Speicher des Targets.
- `make reset` $\rightarrow$ Starte das Target neu.

## Requirements

- [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [CMake](https://github.com/Kitware/CMake/releases)
- [Make]
- [Ninja](https://github.com/ninja-build/ninja/releases)
- STM32Cube Umgebung für debuggen und flashen der Applikation auf das Target:
  - STM32CubeProgrammer
  - ST-Link
  - STM32CubeIDE um Linker-Files erstellen/generieren lassen zu können.
