# Nitmod-Portierung: verbindliche Arbeitsregeln

Vom Nutzer am 08.09.2026 festgelegt:

- Eine Cvar wird als vollständiger Funktionsbereich portiert. Nicht nach einem einzelnen Waffen- oder Beispielpfad als abgeschlossen melden.
- Vor Abschluss alle direkten und indirekten Verbraucher, Waffen, Zustandswechsel, Client-/Server-Abhängigkeiten und Sonderfälle mit den Original-Nitmod-Binaries abgleichen. Registrierung und isolierte Hilfsfunktionstests allein belegen keine Parität.
- Die Original-Binaries sind die maßgebliche Quelle für Parität. Dekompilierter Code und die Kommentare auf etmods.net/nitmod_cvars.php, nitmod_install.php und nxac_setup.php dienen ausschließlich als ergänzende Referenzen.
- Für g_noCharge ausdrücklich alle Ladeenergie verbrauchenden Waffen, Minen, Adrenalin, Versorgung, Luftunterstützung, Konstruktion und Reparatur berücksichtigen. Originale Ausnahmen bewahren; keinen pauschalen Bypass erfinden.
- Pro Cvar einen nachvollziehbaren Soll-/Ist-Nachweis und einen passenden aktuellen Build hinterlegen. Bereits bestehende Nachweise weiterverwenden; gezielt die geänderten tatsächlichen Ausführungspfade prüfen.
- Änderungen bleiben lokal. Nur auf erneute ausdrückliche Nutzeranweisung nach GitHub pushen.

Kanonischer Arbeitsordner: C:/Users/micha/Documents/GitHub/nitmod-master.
Original-Binaries: original_nitmod_shared_objects_32bit/ (lokaler, ignorierter Ordner).
Lokale Abnahmeberichte: reference/; Buildausgaben: build/wasm und build/ci-windows-x86/Release.
