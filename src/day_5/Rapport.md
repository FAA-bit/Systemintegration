# Dag 5 – MQTT, API och konsument

## Syfte:
Syftet med Dag 5 var att bygga en liten IoT-lösning där sensordata skickas från en producent till en broker, vidare till en adapter och slutligen till ett API och en konsument. Projektet fokuserade på att kombinera flera tekniker i ett system: MQTT för meddelanden, JSON för data, C++ för logik och Python för test- och transportstöd.

Projektet ligger i: `src/day_5`

## Genomförande:
Arbetet genomfördes i C++ med stöd av Python-skript och Mosquitto-broker. Hela systemet byggdes upp som en liten datakälla och ett litet integrationstest där en mätning förflyttades mellan olika steg i ett flöde.

### Program i projektet

- `sensor.cpp` – validerar en intern temperaturmätning och skriver den som JSON till en fil.
- `capture.py` – lyssnar på MQTT-topic och sparar inkommande payload till en fil.
- `bridge.cpp` – läser mottagen JSON-fil, validerar den och skickar data via HTTP POST till API:t.
- `api.cpp` – validerar inkommande data, lagrar senaste mätningen i minnet och svarar på GET-anrop.
- `consumer.cpp` – hämtar senaste mätning via HTTP GET och skriver ut den.
- `contract_test.cpp` – testar datamodellens regler utan att behöva nätverkskommunikation.

Den gemensamma modellen definieras i `reading.hpp` och innehåller struktur, validering och serialisering av en temperaturmätning.

## Systemarkitektur:
Det finns flera steg i flödet:

1. En sensor skapar en giltig `Reading` och sparar den i `reading.json`.
2. En MQTT-prenumerant tar emot meddelandet från brokern och sparar det i `received.json`.
3. `bridge.cpp` läser den mottagna filen, validerar den och skickar den till API:t via HTTP.
4. `api.cpp` validerar data igen, lagrar den senaste mätningen och exponeras på en liten HTTP-server.
5. `consumer.cpp` hämtar den senaste mätningen och visar den för användaren.

Kommunikationen går lokalt på loopback-adressen `127.0.0.1`.
- MQTT-broker: port `1885`
- API: port `8085`

## CMake och byggprocess:
Projektet byggs med CMake enligt följande:

```powershell
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Detta skapar en byggkatalog med körbara program samt kör den automatiska kontraktstesten. Om byggningen lyckas förväntas fem körbara filer i `build/Debug` (Windows) eller i `build` (Linux).

Det finns även ett integrationstest:

```powershell
python test_integration.py build/Debug 'C:\Program Files\mosquitto'
```

Testet simulerar hela flödet: broker, MQTT-publicering, adapter, API och konsument. Om allt fungerar passerar testet och systemet anses vara korrekt integrerat.

## Validering och datakontrakt:
Ett centralt mål i Dag 5 var att säkerställa att data alltid är giltig innan den används. Därför finns validering på flera nivåer:

- sensorens interna modell kontrollerar att fälten finns
- `bridge.cpp` validerar indata innan HTTP POST
- `api.cpp` validerar indata igen för att skydda tjänsten
- `contract_test.cpp` verifierar datamodellens regler i automatiska tester

Reglerna innefattar bland annat:

- `sensorId` får inte vara tomt
- `value` måste vara ett korrekt tal
- `unit` måste vara `C`
- temperaturvärdet måste ligga inom rimliga gränser
- data måste vara korrekt formaterad JSON

Om någon av dessa regler bryts stoppas programmet med fel och validationen misslyckas innan data skickas vidare.

## Exekvering i praktiken:
Arbetet kördes i ett stegvis flöde enligt instruktionerna:

### 1. Starta broker
Mosquitto startades med konfigurationen i `mosquitto.conf` så att den lyssnar på port 1885.

### 2. Starta API:t
API-servern startade och lyssnade på `127.0.0.1:8085`.

### 3. Kontrollera tjänsten
`curl` användes för att kontrollera `/health`, vilket förväntades svara med HTTP 200 och texten `ok`.

### 4. Skapa mätning
`sensor.exe` skapade `reading.json` med ett exempel som innehöll:

- `sensorId = temp-01`
- `value = 21.7`
- `unit = C`

### 5. Publicera via MQTT
`capture.py` kopplades till `mosquitto_sub` och väntade på ett meddelande. Därefter publicerades JSON-filen med `mosquitto_pub` på topic `iot25/dag5/reading`.

### 6. Skicka data via adapter
`bridge.exe` läste `received.json`, validerade innehållet och skickade det via HTTP POST till API:t.

### 7. Läs tillbaka via konsument
`consumer.exe` skickade GET till `/api/readings/latest`, läste svaret och skrev ut informationen, exempelvis:

```text
temp-01: 21.7 C
```

Det visade att ett komplett flöde från sensor till API och konsument fungerade.

## Resultat:
Projektet fungerade som en fungerande demonstration av ett litet system för sensordata i realtid. Lösningen visar hur ett ämne kan gå från:

sensor → MQTT → broker → mottagare → adapter → REST API → konsument

Alla dessa steg kontrollerades med validering och testning, vilket gjorde systemet robust samt lättare att felsöka.

## Lärdomar:
Under Dag 5 lärde jag mig:

- Hur MQTT används för att skicka meddelanden mellan systemkomponenter.
- Hur ett API kan ta emot JSON-data och lagra det i minnet.
- Hur en adapter kan användas som länk mellan olika protokoll och format.
- Hur validering behövs både i producenten och i tjänsten för att undvika skadlig eller felaktig data.
- Hur integrationstester kan verifiera hela systemflödet från start till slut.
- Hur C++-, Python- och brokerkomponenter kan samarbeta i samma projekt.
- Varför det är viktigt att starta komponenter i rätt ordning och att hålla koll på portar och topics.

## Slutsats:
Dag 5 gav en tydlig bild av hur systemintegration fungerar i praktiken. Det visade att ett modernt IoT-flöde inte bara handlar om att skicka data, utan också om att validera, strukturera och säkra den data som flyter mellan olika delar av systemet. Detta är ett viktigt grundläggande koncept inom systemintegration och distribuerade applikationer.
