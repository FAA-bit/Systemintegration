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

## Dag 5 – MQTT, API och konsument

Under dag 5 byggdes ett större integrationsflöde för sensordata i ett lokalt
IoT-system. Arbetet visar hur data kan gå från en sensor via MQTT till en broker,
via en adapter till ett REST API, och slutligen till en konsument som visar den
senaste mätningen.

Projektet innefattar:

- `sensor.cpp` för att skapa och validera mätningar
- `capture.py` för att ta emot MQTT-meddelanden
- `bridge.cpp` för att skicka data till API:t
- `api.cpp` för att lagra senaste värdet och svara på HTTP-anrop
- `consumer.cpp` för att hämta och skriva ut senaste mätningen
- `contract_test.cpp` för att verifiera datamodellens regler

Flödet körs lokalt på `127.0.0.1` med MQTT på port `1885` och HTTP på port
`8085`. Arbetet fokuserar på datavalidering, protokollintegration och testning
av ett komplett system från producer till konsument.

Se [README för dag 5](src/day_5/README.md) och
[rapporten för dag 5](src/day_5/Rapport.md).

## Dag 6 – Nätverksnamespaces, routing och brandvägg

Under dag 6 byggdes en isolerad nätverksmiljö i Linux/WSL2 med fyra network
namespaces: ett IoT-nät, ett tjänstenät, ett administrationsnät och en router.
De tre klientnäten kopplades till routern med virtuella Ethernet-länkar och
var separerade från värddatorns vanliga nätverk.

Arbetet omfattade IP-adresser, subnät, gateways, routing och IPv4 forwarding.
Brandväggsregler skapades med `nftables` för att styra trafik utifrån källa,
destination och målport. IoT-nätet fick ansluta till tjänsten på port 1883
men blockerades från port 8080. Administrationsnätet fick ansluta till port
8080 men blockerades från port 1883.

Nätverksåtkomsten verifierades med Python-baserade TCP-tester. Labben innehöll
även statuskontroll, backup av brandväggsregler, ett avsiktligt fel och
återställning. Arbetet visade skillnaden mellan routing, forwarding och
paketfiltrering samt varför både tillåten och blockerad trafik behöver testas.

Se [dokumentationen för dag 6](src/day_6/Mydoc.md) och
[rapporten för dag 6](src/day_6/Rapport.md).

## Sammanfattning

Arbetet visar en progression från grundläggande nätverkskommunikation till
API-baserad systemintegration och hantering av strukturerade dataformat. Den
gemensamma sensordatan kan transporteras över nätverk och representeras som
JSON eller XML, medan validering säkerställer att informationen följer det
förväntade datakontraktet. Dag 6 bygger vidare på nätverksdelen genom att
visa hur nätverk kan isoleras i namespaces, routas genom en router och skyddas
med brandväggsregler. Tillsammans visar arbetet att både applikationsdata och
nätverksvägen måste vara korrekt konfigurerade för att system ska kunna
kommunicera säkert och tillförlitligt.
