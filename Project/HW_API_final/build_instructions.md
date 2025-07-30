# Build Instructions für STM32CubeIDE

## Terminal-basierter Build (empfohlen):
1. Öffne eine Eingabeaufforderung im Projektverzeichnis
2. Führe aus: `make stm32 MCU_FAMILY=stm32c0xx MCU_SPECIFIC=STM32C031C6`
3. Das Build-Artefakt wird in `build/app/main` erstellt

## Alternative für STM32CubeIDE:
1. Erstelle ein neues STM32 C++ Projekt
2. Kopiere die Projektdateien in das neue Projekt
3. Konfiguriere die Include-Pfade und Linker-Einstellungen manuell

## Debug-Konfiguration:
- Target: STM32C031C6
- Debug Probe: ST-Link
- Executable: build/app/main