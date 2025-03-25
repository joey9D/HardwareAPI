# Interfaces

Votreile eines Ansatzes mit Interfaces:

**Plattformunabhängigkeit:**

- Die Applikation bleibt unverändert, egal ob STM32, Zephyr oder Raspberry Pi genutzt wird.

**Erweiterbarkeit:**

- Neue Plattformen (z. B. ESP32, Raspberry Pi) können leicht hinzugefügt werden.

**Saubere Trennung:**

- Die Plattform-spezifische Implementierung ist klar vom Applikationscode getrennt.

**Flexibilität:**

- Die Factory-Funktion erlaubt dynamische Auswahl zur Laufzeit oder bei Kompilierung.
