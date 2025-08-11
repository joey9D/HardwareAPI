# Platform Detection System

## Übersicht

Das HW_API-Projekt verfügt über ein integriertes Plattform-Erkennungssystem, das automatisch das verwendete Betriebssystem erkennt und entsprechende Konfigurationen vornimmt.

## Dateien

### `cmake/PlatformDetection.cmake`

Zentrale CMake-Datei mit allen Plattform-Erkennungsfunktionen.

## Funktionen

### `detect_and_configure_os()`

Hauptfunktion zur Betriebssystem-Erkennung:
- **Windows**: Erkennt Windows-Systeme und setzt `.exe` Suffix
- **macOS**: Erkennt macOS-Systeme, unterscheidet zwischen Intel und Apple Silicon
- **Linux**: Erkennt Linux-Distributionen über `/etc/os-release`
- **Unix**: Fallback für andere Unix-ähnliche Systeme

**Gesetzte Variablen:**

- `HW_API_OS_NAME`: Name des Betriebssystems
- `HW_API_OS_VERSION`: Version des Betriebssystems (falls verfügbar)
- `HW_API_EXECUTABLE_SUFFIX`: Datei-Endung für ausführbare Dateien
- `HW_API_LIBRARY_SUFFIX`: Datei-Endung für Bibliotheken
- `HW_API_APPLE_SILICON`: Boolean für Apple Silicon Macs

### `get_toolchain_paths(TOOLCHAIN_NAME OUTPUT_VAR)`

Gibt plattformspezifische Pfade für Toolchains zurück.

**Parameter:**

- `TOOLCHAIN_NAME`: Name der Toolchain (z.B. "arm-none-eabi")
- `OUTPUT_VAR`: Variable zum Speichern der gefundenen Pfade

### `find_toolchain_executable(TOOLCHAIN_NAME EXECUTABLE_NAME OUTPUT_VAR)`

Sucht nach Toolchain-Executables in bekannten Pfaden.

**Parameter:**

- `TOOLCHAIN_NAME`: Name der Toolchain
- `EXECUTABLE_NAME`: Name der ausführbaren Datei (z.B. "gcc")
- `OUTPUT_VAR`: Variable zum Speichern des gefundenen Pfads

### `print_os_info()`

Makro zum Ausgeben der erkannten OS-Informationen.

## Integration

### Automatische Integration

Das System wird automatisch in folgenden Dateien eingebunden:

- `CMakeLists.txt` (Hauptprojekt)
- `HW_API/CMakeLists.txt`
- `toolchains/stm32-toolchain.cmake`

### Manuelle Integration

```cmake
# Am Anfang einer CMakeLists.txt
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformDetection.cmake)
detect_and_configure_os()

# OS-Informationen anzeigen
print_os_info()
```

## Beispiel-Ausgabe

```
-- HW_API: Detected macOS 14.5 on Apple Silicon
-- === HW_API Operating System Detection ===
-- OS Name: macOS
-- OS Version: 14.5
-- Executable Suffix: ''
-- Library Suffix: '.dylib'
-- Apple Silicon: TRUE
-- ================================================================================
-- Found gcc: /opt/homebrew/bin/arm-none-eabi-gcc
-- Found g++: /opt/homebrew/bin/arm-none-eabi-g++
```

## Unterstützte Toolchain-Pfade

### Windows

- `C:/ST/STM32CubeCLT_1.18.0/GNU-tools-for-STM32/bin/`
- `C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/`
- `C:/Program Files/Arm GNU Toolchain arm-none-eabi/14.2 rel1/bin/`

### macOS

- `/opt/homebrew/bin/` (Apple Silicon Homebrew)
- `/usr/local/bin/` (Intel Homebrew)
- `/opt/local/bin/` (MacPorts)

### Linux

- `/usr/bin/`
- `/usr/local/bin/`
- `/opt/gcc-arm-none-eabi/bin/`

## Erweiterung

Um neue Plattformen oder Toolchain-Pfade hinzuzufügen:

1. **Neue OS-Erkennung** in `detect_and_configure_os()` hinzufügen
2. **Neue Toolchain-Pfade** in `get_toolchain_paths()` ergänzen
3. **Tests** mit `make info` durchführen

## Vorteile

- ✅ **Automatische Erkennung**: Keine manuelle Konfiguration nötig
- ✅ **Plattform-übergreifend**: Windows, macOS, Linux Unterstützung
- ✅ **Erweiterbar**: Einfach neue Plattformen hinzufügbar
- ✅ **Debug-freundlich**: Detaillierte Ausgaben
- ✅ **Zentral verwaltet**: Alle Plattform-Logik in einer Datei
