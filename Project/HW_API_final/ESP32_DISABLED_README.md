# ESP32 Support Deaktiviert

## Übersicht

Alle ESP32-bezogenen Teile wurden für STM32-only Build deaktiviert oder entfernt.

## Deaktivierte/Entfernte Dateien

### Verschobene Dateien nach `_disabled_esp32_files/`:

- `HW_API/platform/esp32/` (kompletter Ordner)
- `HW_API/drivers/esp32_hal_wrapper/` (kompletter Ordner)
- `HW_API/gpio/gpio_esp32.cpp`
- `HW_API/gpio/gpio_esp32.hpp`
- `HW_API/core/hw_enum_esp32.hpp`

### Auskommentierte Teile in CMakeLists.txt Dateien:

- `HW_API/CMakeLists.txt`: ESP-IDF Erkennung und Pfad-Handling
- `HW_API/platform/CMakeLists.txt`: ESP32 Subdirectory und Verlinkung
- `HW_API/gpio/CMakeLists.txt`: ESP32 Source-Dateien und Konfiguration
- `HW_API/spi/CMakeLists.txt`: ESP32 Konfiguration
- `HW_API/core/CMakeLists.txt`: ESP32 Compile-Definitionen
- `HW_API/drivers/CMakeLists.txt`: ESP32 HAL Wrapper

### Auskommentierte Teile in Header-Dateien:

- `app/main.hpp`: ESP32 Platform-spezifische Includes
- `HW_API/pin_config.hpp`: ESP32 GPIO Include
- `HW_API/gpio/gpio_interface.hpp`: ESP32 Type-Aliases
- `HW_API/core/hw_enum_classes.hpp`: ESP32 Enumerationen
- `HW_API/core/hw_factory.hpp`: ESP32C6 Hardware-Klassen

### Auskommentierte Teile im Makefile:

- ESP32 Platform-Konfiguration
- `esp32` Target
- `esp32-idf` Target
- ESP32 Dokumentation in Help-Text

## Wiederherstellen von ESP32 Support

Um ESP32 Support zu reaktivieren:

1. **Dateien zurück verschieben:**

   ```bash
   mv _disabled_esp32_files/* HW_API/
   # Dann die Dateien in die richtigen Ordner verschieben
   ```

2. **Kommentare in allen CMakeLists.txt entfernen:**
   - Alle `# ESP32...` Kommentare entfernen
   - `elseif(TARGET_PLATFORM STREQUAL "ESP32")` Blocks reaktivieren

3. **Header-Dateien restaurieren:**
   - Alle `// ESP32 PLATFORM DISABLED...` Kommentare entfernen
   - `#elif ESP32_PLATFORM` Blocks reaktivieren

4. **Makefile restaurieren:**
   - ESP32 Targets und Konfiguration reaktivieren

## Aktueller Zustand

- **Funktioniert:** STM32 Build komplett funktionsfähig
- **Standard Platform:** STM32 (anstatt TEST)
- **Deaktiviert:** Alle ESP32-Funktionalität
- **Sauber:** Keine ESP32-Abhängigkeiten im aktiven Code

## Test

```bash
make info  # Zeigt STM32-only Konfiguration
make stm32 # Kompiliert für STM32
```
