# Klassen  

Vorteile eines Ansatzes mit Klassen:  

**Plattformunabhängigkeit:**

- Die Applikation nutzt immer die GPIOBase-Schnittstelle, egal welche Plattform darunter liegt.

**Gute Erweiterbarkeit:**

- Neue Plattformen können leicht durch eine neue abgeleitete Klasse hinzugefügt werden.

**Saubere Trennung von Code:**

- Die Applikation kennt nur die abstrakte Klasse GPIOBase, nicht die spezifischen Implementierungen.

**Polymorphismus:**

- Das GPIO-Objekt kann zur Laufzeit je nach Plattform unterschiedlich sein.
