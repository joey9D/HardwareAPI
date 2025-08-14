# LSI_STARTUP_TIME Redefinition Warning

## Problem
Build-Warnungen beim Kompilieren des STM32-Projekts wegen doppelter Definition von `LSI_STARTUP_TIME`:

```
warning: "LSI_STARTUP_TIME" redefined
  830 | #define LSI_STARTUP_TIME 130U /*!< LSI Maximum startup time in us */
      | 
note: this is the location of the previous definition
  129 | #define LSI_STARTUP_TIME 85UL /*!< Time out for LSI start up, in ms */
```

## Ursache
Die Makrodefinition `LSI_STARTUP_TIME` wird in zwei verschiedenen Dateien definiert:

1. **Erste Definition** in:
   - `stm32g0xx_hal_conf.h:129`
   - Wert: `85UL`
   - Einheit: Millisekunden (ms)

2. **Redefinition** in:
   - `stm32g071xx.h:830`
   - Wert: `130U`
   - Einheit: Mikrosekunden (us)

## Lösungsmöglichkeiten

### Option 1: Explizites Undefine
```c
// In einer zentralen Header-Datei vor dem Einbinden von stm32g071xx.h
#ifdef LSI_STARTUP_TIME
#undef LSI_STARTUP_TIME
#endif
```

### Option 2: Custom Defines Header erstellen
Eine eigene Header-Datei (`custom_defines.h`) erstellen, die nach allen anderen Includes eingefügt wird:

```c
// custom_defines.h
#ifdef LSI_STARTUP_TIME
#undef LSI_STARTUP_TIME
#endif

// Bevorzugte Definition verwenden
#define LSI_STARTUP_TIME 130U  // oder 85UL je nach Bedarf
```

### Option 3: HAL-Wrapper anpassen
Die HAL-Wrapper-Datei modifizieren, um den Konflikt zu vermeiden:

```c
// In der HAL-Wrapper-Datei
#include "stm32g0xx_hal_conf.h"

#ifdef LSI_STARTUP_TIME
#undef LSI_STARTUP_TIME
#endif

#include "stm32g0xx.h"
```

## Priorität
⚠️ Diese Warnung beeinflusst die Funktionalität nicht kritisch, sollte aber für eine saubere Codebase behoben werden.

## Weitere Hinweise
Die beiden Werte unterscheiden sich nicht nur im Wert, sondern auch in der Einheit (ms vs. us)!
