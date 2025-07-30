# 🛠️ **Debug-Probleme Zusammenfassung - Aktueller Stand**

## **🚨 Hauptprobleme beim Debugging:**

### **1. Breakpoint-Fehler:**
```
Error: Failed to set breakpoint at address: 0x82c0.
Error: Failed to set more breakpoints
Error: Failed to set breakpoint at address: 0x82c6.
```

### **2. Stepping-Fehler:**
```
"Unable to step in. Operation failed with error code 0x800004004"
```

---

## **🔍 Ursachenanalyse:**

### **Problem 1: Timing-Konflikte bei Breakpoints**
- **Ursache:** Der Debugger versucht Breakpoints zu setzen, BEVOR der Mikrocontroller richtig initialisiert ist
- **Technischer Grund:** Flash-Speicher des STM32 ist noch nicht für Debug-Operationen bereit
- **Setup-Sequenz war falsch:** `load` → `breakpoints` statt `reset` → `load` → `breakpoints`

### **Problem 2: Debug-Symbol-Probleme**
- **Mögliche Ursache:** ELF-Datei könnte ohne vollständige Debug-Informationen kompiliert sein
- **Status:** Unbestätigt - Build läuft noch
- **Debug-Flags:** `-g -O0` sind in CMakeLists.txt konfiguriert (sollte OK sein)

### **Problem 3: GDB-Server Verbindungsprobleme**
- **Ursache:** Inkonsistente Verbindungssequenz zwischen VS Code und ST-LINK GDB Server
- **Symptom:** "target remote" Command-Timing-Probleme
- **Port-Konflikte:** Erfolgreich gelöst (PID 6768 terminiert)

### **Problem 4: Launch-Konfiguration suboptimal**
- **Ursprüngliches Problem:** `request: "launch"` mit gleichzeitigem `load` Command
- **Attach-Mode Problem:** Dropdown für lokale Prozesse (nicht für Remote-Debugging geeignet)
- **Lösung implementiert:** Neue "Remote" Konfiguration ohne Dropdown

---

## **📊 Aktuelle Debug-Setup Status:**

| **Komponente** | **Status** | **Problem** |
|----------------|------------|-------------|
| ST-LINK Hardware | ✅ **OK** | Verbindung erfolgreich |
| GDB Server | ✅ **OK** | Port 2331 verfügbar |
| ELF Binary | ⏳ **Build läuft** | Debug-Symbole unbestätigt |
| VS Code Config | ✅ **Überarbeitet** | Neue Remote-Konfiguration |
| Flash Programming | ✅ **OK** | 15.56 KB erfolgreich geflasht |

---

## **🎯 Identifizierte Lösungsansätze:**

### **Lösung 1: Verbesserte Launch-Konfiguration**
- **"STM32 Debug (Remote)"** - Eliminiert Dropdown und Timing-Probleme
- **Korrekte Command-Sequenz:** Symbole laden → Reset → Halt
- **Kein `load` Command in Debug-Phase** (Programm bereits geflasht)

### **Lösung 2: Manuelle Workflow-Trennung**
```bash
1. make flash    # Programm auf MCU laden
2. make debug    # GDB Server starten  
3. F5 in VS Code # Debug-Session starten
```

### **Lösung 3: Build-Verifikation notwendig**
- **Warten auf Build-Completion**
- **Debug-Symbol-Verifikation** mit objdump
- **Neubuilding** falls Debug-Informationen fehlen

---

## **⚡ Nächste Schritte nach Build-Completion:**

1. **✅ Verify Build:** Debug-Symbole in ELF-Datei prüfen
2. **✅ Fresh Flash:** `make flash` für sauberen Start
3. **✅ GDB Server:** `make debug` starten
4. **✅ Test Remote Config:** "STM32 Debug (Remote)" verwenden
5. **✅ Breakpoint Test:** In `main.cpp` Zeile 29 setzen
6. **✅ Step-by-Step:** F10/F11 Funktionalität testen

---

## **🎯 Erwartetes Ergebnis nach Fixes:**

- **✅ Breakpoints setzen ohne Adress-Fehler**
- **✅ Step-by-Step Debugging (F10, F11)**
- **✅ Variable Inspection im Watch Panel**
- **✅ Register Viewing in Debug Console**
- **✅ Keine "Operation failed" Errors**

---

## **📝 Technische Details:**

### **Aktuelle VS Code Launch-Konfigurationen:**

#### **1. STM32 Debug (Remote) - Empfohlen:**
```json
{
    "name": "STM32 Debug (Remote)",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/build/app/main",
    "MIMode": "gdb",
    "miDebuggerPath": "C:/ST/STM32CubeCLT_1.18.0/GNU-tools-for-STM32/bin/arm-none-eabi-gdb.exe",
    "miDebuggerServerAddress": "localhost:2331",
    "targetArchitecture": "arm",
    "stopAtEntry": false,
    "setupCommands": [
        {
            "description": "Load symbols",
            "text": "file ${workspaceFolder}/build/app/main",
            "ignoreFailures": false
        },
        {
            "description": "Reset and halt target", 
            "text": "monitor reset halt",
            "ignoreFailures": true
        }
    ]
}
```

#### **2. STM32 Debug (Launch Mode - Flash & Debug) - Vollautomatik:**
```json
{
    "name": "STM32 Debug (Launch Mode - Flash & Debug)",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/build/app/main",
    "preLaunchTask": "build",
    "setupCommands": [
        {
            "description": "Reset and halt target",
            "text": "monitor reset halt",
            "ignoreFailures": true
        },
        {
            "description": "Flash the program",
            "text": "load",
            "ignoreFailures": false
        },
        {
            "description": "Enable flash breakpoints",
            "text": "monitor flash breakpoints = 1",
            "ignoreFailures": true
        }
    ]
}
```

---

## **🔧 Debugging Commands:**

### **Manuelle GDB Commands für Troubleshooting:**
```gdb
# Verbindung aufbauen
target remote localhost:2331

# Symbole laden
file build/app/main

# Target reset und anhalten
monitor reset halt

# Flash breakpoints aktivieren
monitor flash breakpoints = 1

# Breakpoint setzen
break main.cpp:29

# Programm starten
continue

# Step commands
step        # F11 (Step into)
next        # F10 (Step over)
continue    # F5  (Continue)
```

### **Terminal Commands:**
```bash
# Projekt bauen
make clean && make stm32

# Flash programmieren
make flash

# Debug server starten
make debug

# Build-Info anzeigen
make info
```

---

**Status:** 🔧 **Bereit für Testing nach Build-Completion**

**Erstellt:** Juli 30, 2025  
**Projekt:** HW_API_final - STM32 Hardware Abstraction Layer  
**Hardware:** NUCLEO-C031C6 mit ST-LINK/V2-1
