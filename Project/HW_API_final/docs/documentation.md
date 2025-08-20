# STM32 Hardware API - Projektdokumentation

## Projektübersicht

Dieses Projekt implementiert eine **Multi-Family STM32 Hardware Abstraction Layer (HAL) API**, die eine einheitliche Schnittstelle für verschiedene STM32-Mikrocontroller-Familien bereitstellt. Das System ermöglicht es, Hardware-spezifischen Code zu abstrahieren und verschiedene STM32-Familien mit derselben API anzusprechen.

### Unterstützte Hardware-Plattformen

✅ **Getestet und funktionsfähig:**
- STM32C031C6 (NUCLEO-C031C6) - Cortex-M0+, 32KB Flash, 12KB RAM
- STM32G071RB (NUCLEO-G071RB) - Cortex-M0+, 128KB Flash, 36KB RAM  
- STM32G0B1RE - Cortex-M0+, 512KB Flash, 144KB RAM

🔧 **Vorbereitet für Erweiterung:**
- STM32F4xx Familie (Framework vorhanden)

## Projektarchitektur

### 1. Verzeichnisstruktur

```
HW_API_final/
├── config/
│   └── stm32_config.mk           # Hardware-Konfiguration pro Familie
├── app/
│   ├── CMakeLists.txt            # App-spezifische Build-Konfiguration
│   ├── main.cpp                  # Hauptprogramm mit Hardware-Tests
│   └── main.hpp
├── HW_API/
│   ├── core/                     # Kernkomponenten
│   │   ├── hw_interface.hpp      # Hardware-Abstraktionsschnittstelle
│   │   ├── hw_factory.hpp        # Factory Pattern für Hardware-Instanzen
│   │   ├── hw_enum_classes.hpp   # Gemeinsame Enumerationen
│   │   ├── hw_enum_stm32.hpp     # STM32-spezifische Enumerationen
│   │   ├── hw_enum_esp32.hpp     # ESP32-spezifische Enumerationen
│   │   └── project_config.hpp        # Pin-Konfigurationsstrukturen
│   ├── drivers/
│   │   └── stm32_hal_wrapper/    # STM32 HAL Wrapper
│   │       ├── common/           # Familie-übergreifende Komponenten
│   │       │   ├── stm32_hal_inc.hpp  # Zentrale HAL-Header-Verwaltung
│   │       │   └── syscalls.c    # Newlib syscalls für printf/malloc
│   │       ├── stm32c0xx/        # C0xx-Familie spezifisch
│   │       │   └── stm32c0xx_hal_conf.h
│   │       └── stm32g0xx/        # G0xx-Familie spezifisch
│   │           └── stm32g0xx_hal_conf.h
│   ├── gpio/                     # GPIO-Implementierungen
│   │   ├── gpio_interface.hpp    # GPIO-Abstraktionsschnittstelle
│   │   ├── gpio_stm32.cpp/.hpp   # STM32-spezifische GPIO-Implementierung
│   │   └── gpio_test.cpp/.hpp    # GPIO-Testsuite
│   └── platform/                 # Platform-spezifische Implementierungen
│       └── stm32/
│           ├── stm32x0_gpio_mapping.hpp  # Einheitliches GPIO-Mapping
│           ├── stm32c0xx/        # C0xx Hardware-Implementierung
│           │   ├── STM32C031C6Tx_FLASH.ld  # Linker Script
│           │   ├── stm32c0xx_hw.cpp/.hpp   # Hardware-Klasse
│           │   ├── stm32c0xx_hal_msp.c     # HAL MSP Callbacks
│           │   └── stm32c0xx_it.c/.h       # Interrupt Handler
│           └── stm32g0xx/        # G0xx Hardware-Implementierung
│               ├── STM32G071RBTx_FLASH.ld  # Linker Script
│               ├── stm32g0xx_hw.cpp/.hpp   # Hardware-Klasse
│               ├── stm32g0xx_hal_msp.c     # HAL MSP Callbacks
│               └── stm32g0xx_it.c/.h       # Interrupt Handler
├── toolchains/
│   └── stm32-toolchain.cmake     # ARM GCC Toolchain-Definition
├── CMakeLists.txt                # Haupt-CMake-Konfiguration
└── Makefile                      # Build-Automatisierung
```

### 2. Architekturprinzipien

#### **Factory Pattern**
Das System verwendet das Factory Pattern zur Hardware-Instanziierung:
```cpp
// hw_factory.hpp
std::unique_ptr<HardwareInterface> create_hardware_instance() {
    #if defined(STM32C0xx)
        return std::make_unique<Stm32c0xx_hw>();
    #elif defined(STM32G0xx)
        return std::make_unique<Stm32g0xx_hw>();
    #endif
}
```

#### **Interface Segregation**
Klare Trennung der Verantwortlichkeiten:
- `HardwareInterface`: Abstrakte Basis für alle Hardware-Implementierungen
- `GpioInterface`: GPIO-spezifische Abstraktionsschicht
- Platform-spezifische Implementierungen erben von diesen Interfaces

#### **Dependency Injection**
Hardware-Instanzen werden zur Laufzeit erstellt und injiziert, nicht fest verdrahtet.

## Build-System

### 1. Makefile-basierte Konfiguration

Das Build-System verwendet eine **externalisierte Konfiguration** in `config/stm32_config.mk`:

```makefile
# Familie auswählen
MCU_FAMILY ?= stm32g0xx           # oder stm32c0xx
MCU_SPECIFIC ?= STM32G071RB       # spezifisches MCU-Modell

# Automatische Repository-Auswahl basierend auf Familie
ifeq ($(MCU_FAMILY),stm32g0xx)
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32g0xx_hal_driver.git
    STM32_HAL_TAG ?= v1.4.4
    DEFAULT_MCU ?= STM32G071RB
endif
```

### 2. CMake Familie-Detection

Das CMake-System erkennt automatisch die STM32-Familie und konfiguriert:
- Compile-Definitionen (`-DSTM32G0xx=1`)
- Include-Pfade 
- Linker-Scripts
- HAL-Bibliotheken

### 3. Build-Kommandos

```bash
# C0xx Familie bauen
make clean && make stm32 MCU_FAMILY=stm32c0xx

# G0xx Familie bauen  
make clean && make stm32 MCU_FAMILY=stm32g0xx

# Debug-Informationen anzeigen
make stm32 VERBOSE=1
```

## Kritische Implementierungsdetails

### 1. ⚠️ HAL Include-Reihenfolge

**Problem:** STM32 HAL Header haben strenge Include-Abhängigkeiten.

**Lösung:** Verwendung der Haupt-HAL-Header in `stm32_hal_inc.hpp`:
```cpp
#if defined(STM32G0xx)
    #include "stm32g0xx_hal.h"  // Haupt-Header verwaltet Include-Reihenfolge
#elif defined(STM32C0xx)
    #include "stm32c0xx_hal.h"
#endif
```

**❌ Vermeiden:** Manuelle Include-Reihenfolge (config → CMSIS → HAL-Module)
**✅ Verwenden:** Haupt-HAL-Header, der die korrekte Reihenfolge intern verwaltet

### 2. ⚠️ Family-spezifische Compile-Definitionen

**Problem:** Gemischte Familie-Definitionen führen zu Build-Fehlern.

**Lösung:** Familie-spezifische CMake-Logik in `app/CMakeLists.txt`:
```cmake
if(STM32_FAMILY STREQUAL "stm32c0xx")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        STM32C0xx=1
        STM32C031xx=1
        # ... C0xx-spezifische Definitionen
    )
elseif(STM32_FAMILY STREQUAL "stm32g0xx")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        STM32G0xx=1
        STM32G071xx=1
        # ... G0xx-spezifische Definitionen
    )
endif()
```

### 3. ⚠️ Memory Layout Unterschiede

**Kritischer Punkt:** Jede STM32-Familie hat unterschiedliche Speicher-Layouts.

**Lösung:** Familie-spezifische Linker-Scripts:
- `STM32C031C6Tx_FLASH.ld`: 32KB Flash, 12KB RAM
- `STM32G071RBTx_FLASH.ld`: 128KB Flash, 36KB RAM

**Automatische Auswahl** über CMake basierend auf `STM32_FAMILY`.

### 4. ⚠️ Clock-Konfiguration

**Problem:** Verschiedene STM32-Familien haben unterschiedliche Clock-Trees.

**Lösung:** Familie-spezifische `SystemClock_Config()` in Hardware-Klassen:
```cpp
// stm32g0xx_hw.cpp
void Stm32g0xx_hw::SystemClock_Config() {
    // G0xx-spezifische PLL-Konfiguration
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 8;        // 64MHz
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
}
```

### 5. ⚠️ GPIO Port Mapping

**Problem:** Verschiedene STM32-Familien haben unterschiedliche verfügbare GPIO-Ports.

**Lösung:** Einheitliches Mapping in `stm32x0_gpio_mapping.hpp`:
```cpp
#if defined(STM32C0xx)
    GPIO_TypeDef* gpio_port[4] = {GPIOA, GPIOB, GPIOC, GPIOF};
#elif defined(STM32G0xx)  
    GPIO_TypeDef* gpio_port[6] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};
#endif
```

## Hardware-spezifische Besonderheiten

### STM32C031C6 (NUCLEO-C031C6)
- **Cortex-M0+** @ bis zu 48MHz
- **32KB Flash, 12KB RAM**
- **Limitierte Peripherie:** Weniger Timer, ADC-Kanäle
- **Boot-Pin:** BOOT0 auf PA14
- **User Button:** PC13 (Active Low)
- **User LED:** PA5

### STM32G071RB (NUCLEO-G071RB)  
- **Cortex-M0+** @ bis zu 64MHz
- **128KB Flash, 36KB RAM**
- **Erweiterte Peripherie:** Mehr Timer, USB, CAN
- **Boot-Pin:** BOOT0 auf PB8
- **User Button:** PC13 (Active Low)
- **User LED:** PA5

### STM32G0B1RE
- **Cortex-M0+** @ bis zu 64MHz
- **512KB Flash, 144KB RAM**
- **Premium-Features:** Advanced timers, Crypto, mehr ADC

## Debugging und Troubleshooting

### 1. Build-Probleme

**HAL_StatusTypeDef nicht gefunden:**
```bash
# Lösung: Clean build mit korrekter Familie
make clean
make stm32 MCU_FAMILY=stm32g0xx
```

**Gemischte Familie-Definitionen:**
- Überprüfe `app/CMakeLists.txt` auf korrekte Familie-spezifische Blöcke
- Stelle sicher, dass `STM32_FAMILY` Variable korrekt gesetzt ist

### 2. Hardware-Debugging

**System startet nicht:**
- Überprüfe Clock-Konfiguration in `SystemClock_Config()`
- Überprüfe Linker-Script Memory-Layout
- Überprüfe Boot-Pin-Zustand

**GPIO funktioniert nicht:**
- Überprüfe GPIO-Port-Mapping für Familie
- Überprüfe Clock-Enable für GPIO-Ports
- Überprüfe Pin-Konfiguration (Mode, Pull, Speed)

### 3. Debug-Ausgaben aktivieren

```cpp
// In main.cpp
#define DEBUG_PRINTS 1
#if DEBUG_PRINTS
    printf("System initialized successfully\n");
#endif
```

## Erweiterung für neue STM32-Familien

### Schritt-für-Schritt Anleitung:

1. **Konfiguration erweitern** (`config/stm32_config.mk`):
```makefile
else ifeq ($(MCU_FAMILY),stm32f4xx)
    STM32_HAL_REPO ?= https://github.com/STMicroelectronics/stm32f4xx_hal_driver.git
    # ... weitere Konfiguration
endif
```

2. **HAL-Wrapper erstellen** (`HW_API/drivers/stm32_hal_wrapper/stm32f4xx/`):
- `stm32f4xx_hal_conf.h`

3. **Platform-Implementierung** (`HW_API/platform/stm32/stm32f4xx/`):
- `stm32f4xx_hw.cpp/.hpp`
- `STM32F407VGTx_FLASH.ld`
- `stm32f4xx_hal_msp.c`
- `stm32f4xx_it.c/.h`

4. **Factory Pattern erweitern** (`HW_API/core/hw_factory.hpp`):
```cpp
#elif defined(STM32F4xx)
    return std::make_unique<Stm32f4xx_hw>();
```

5. **GPIO-Mapping anpassen** (`HW_API/platform/stm32/stm32x0_gpio_mapping.hpp`):
```cpp
#elif defined(STM32F4xx)
    GPIO_TypeDef* gpio_port[9] = {GPIOA, GPIOB, ..., GPIOI};
```

## Performance und Optimierung

### Memory Footprint
- **Code Size:** ~15KB (ohne HAL-Bibliothek)
- **RAM Usage:** ~2KB Stack + dynamische Allokationen
- **HAL Library:** ~50-80KB je nach aktivierten Modulen

### Compile-Zeit Optimierungen
- Familie-spezifische Conditional Compilation
- Nur benötigte HAL-Module aktivieren
- Template-basierte GPIO-Implementierung reduziert Runtime-Overhead

## Testing und Validierung

### Hardware-in-the-Loop Tests
Alle unterstützten Boards wurden mit folgendem Test-Programm validiert:
```cpp
// Kontinuierlicher Button-Toggle-Test
while(true) {
    if(hardware->get_gpio()->read_pin(user_button) == false) {
        hardware->get_gpio()->toggle_pin(user_led);
        HAL_Delay(200);  // Debounce
    }
}
```

### Erfolgreiche Validierung
✅ **STM32C031C6:** Button-Toggle funktioniert, LED reagiert korrekt
✅ **STM32G071RB:** Button-Toggle funktioniert, LED reagiert korrekt  
✅ **STM32G0B1RE:** Button-Toggle funktioniert, LED reagiert korrekt

## Bekannte Limitationen

1. **ESP32-Support:** Framework vorhanden, aber nicht implementiert
2. **Advanced Features:** Keine Timer, SPI, I2C Implementierung (nur GPIO)
3. **RTOS-Support:** Aktuell nur Bare-Metal
4. **Power Management:** Keine Low-Power-Modi implementiert

## Lizenz und Credits

- **STM32 HAL:** © STMicroelectronics (BSD-3-Clause)
- **ARM CMSIS:** © ARM Limited (Apache-2.0)
- **Projekt-Code:** Siehe Projekt-Lizenz

---

**Erstellt:** August 2025
**Version:** 1.0
**Status:** Produktionsreif für STM32C0xx/G0xx Familien
