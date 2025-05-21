# MCU-driver API

Driver API für verschiedene Mikrocontroller, hauptsächlich STM32 MCUs.
(Zukünfitg auch ESP32).
Fokus liegt auf der Modularität, Abstraktion und einfache Anwendung.
Crossplattform kompatibel.

## Projektstruktur

- Drivers: Hardwareabstraktion für verschiedene Sensoren und Geräte.
- Peripherals: Jede Funktion (GPIO, SPI, etc.) befindet sich in einem eigenen Verzeichnis.
- App: Enthält `main.h`-Header und `main.cpp` der Applikation.

## Wie sieht es im Code aus?

### main.h

```cpp
#pragma once

#include <iostream>
#include <cstdint>
#include "periph/gpio_stm32c0.hpp"
#include "systick.hpp"
#include "rcc.hpp"
#include "FreeRTOSConfig.h"

```

### main.cpp

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

## Wie wird gebuilded?

Repo sollte hier schon geklont sein.

```bash
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

**Windows:**

- [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- [CMake](https://github.com/Kitware/CMake/releases)
- [Make](https://github.com/maweil/CompileMakeForWindows/releases)
- [Ninja](https://github.com/ninja-build/ninja/releases)
- [STM32CubeCLT](https://www.st.com/en/development-tools/stm32cubeclt.html?dl=redirect) für debuggen und flashen der Applikation auf das Target:
  - STM32CubeProgrammer
  - ST-Link
  - STM32CubeIDE um Linker-Files erstellen/generieren lassen zu können.
