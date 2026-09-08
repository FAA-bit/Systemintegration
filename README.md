# Systemintegration

Detta repository innehåller arbeten inom systemintegration med fokus på
nätverkskommunikation, REST API:er och strukturerade dataformat.

## Dag 2 – TCP, UDP och nätverkstrafik

Under dag 2 byggdes och testades program för TCP- och UDP-kommunikation i
C++. TCP-delen består av en server och en klient som upprättar en anslutning,
skickar meddelanden och tar emot svar. UDP-delen består av en sändare och en
mottagare som kommunicerar med datagram utan att först skapa en anslutning.

Arbetet omfattade även kompilering med Microsoft C++ och Winsock samt
observering av nätverkstrafik i Wireshark. Kommunikation testades lokalt via
`127.0.0.1` på port 5000 för TCP och port 5001 för UDP.

Se [README för dag 2](src/day_2/README.md) för bygginstruktioner, körning och
Wireshark-filter.

## Dag 3 – REST API och CMake

Under dag 3 skapades ett REST API i C++ med HTTP-kommunikation och JSON-data.
Projektet konfigureras och byggs med CMake, som även hämtar externa beroenden
med `FetchContent`. Arbetet gav praktisk erfarenhet av projektstruktur,
Microsoft Visual Studio som C++-verktyg och byggning i Debug-konfiguration.

Se [API-dokumentationen](src/day_3/API.md) och
[README för dag 3](src/day_3/README.md).

## Dag 4 – JSON och XML

Under dag 4 jämfördes JSON och XML som dataformat för sensormätningar. Två
C++-program läser in, validerar och serialiserar samma temperaturdata:

- `json_demo.cpp` använder nlohmann/json.
- `xml_demo.cpp` använder pugixml.

Programmen kontrollerar bland annat att sensor-ID, temperaturvärde och enhet
finns och har rätt typ. Temperaturen måste ligga mellan -50 och 100 grader och
enheten måste vara `C`. Projektet byggs med CMake och visar hur samma
datamodell kan användas oberoende av dataformat.

Se [README för dag 4](src/day_4/README.md) och
[rapporten för dag 4](src/day_4/Rapport.md).

## Sammanfattning

Arbetet visar en progression från grundläggande nätverkskommunikation till
API-baserad systemintegration och hantering av strukturerade dataformat. Den
gemensamma sensordatan kan transporteras över nätverk och representeras som
JSON eller XML, medan validering säkerställer att informationen följer det
förväntade datakontraktet.