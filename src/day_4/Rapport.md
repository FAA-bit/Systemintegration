# Dag 4 – JSON och XML

## Syfte:
Syftet med Dag 4 var att arbeta med olika dataformat inom systemintegration. Målet var att läsa in, validera och skriva ut samma temperaturmätning i både JSON- och XML-format.
Projektet låg i: src/day_4

## Genomförande:
Arbetet genomfördes i C++ och bestod av två separata demonstrationsprogram:

- `json_demo.cpp` använder biblioteket nlohmann/json.
- `xml_demo.cpp` använder biblioteket pugixml.

Båda programmen hanterar en temperaturmätning med följande information:

- `sensorId` – identifierar sensorn.
- `value` – temperaturvärdet som ett tal.
- `unit` – mätenheten, som ska vara `C`.

JSON-programmet läser in ett JSON-objekt med `json::parse`. XML-programmet läser in ett XML-dokument med pugixml och hämtar värden från elementen `sensorId`, `value` och `unit`.

## CMake och beroenden:
Projektet konfigureras och byggs med CMake. I `CMakeLists.txt` används `FetchContent` för att hämta två fastslagna beroenden:

- nlohmann/json version 3.12.0.
- pugixml version 1.15.

Programmen byggdes i Developer PowerShell for Visual Studio med följande kommandon från mappen `src/day_4`:

```powershell
cmake -S .\src\day_4 -B .\src\day_4\build
cmake --build .\src\day_4\build --config Debug
```

Det skapade två körbara program i `build/Debug`:

- `json_demo.exe`  - .\src\day_4\build\Debug\json_demo.exe 
- `xml_demo.exe`  -  .\src\day_4\build\Debug\xml_demo.exe 

## Validering:
Innan en mätning accepteras kontrollerar båda programmen att:

- data har rätt struktur och kan tolkas.
- `sensorId` finns och inte är tomt.
- `value` är ett numeriskt värde.
- `unit` är `C`.
- temperaturen ligger mellan -50 och 100 grader.

Om data är ogiltig kastas ett undantag. Felet skrivs ut och programmet avslutas med felkod 1. På så sätt stoppas felaktig data innan den används vidare i programmet.

## JSON:
JSON är ett objektbaserat format där mätningen representeras med nycklar och värden. Efter valideringen omvandlas informationen till en `Reading`-struktur och skrivs sedan tillbaka som formaterad JSON med två blanksteg för indrag.

## XML:
XML representerar mätningen som ett `reading`-element med underliggande element för sensor-ID, värde och enhet. Efter valideringen skapas ett nytt XML-dokument och skrivs ut med XML-deklaration och indrag.

## Resultat:
Båda programmen kunde konfigureras, byggas och köras. De läste in samma temperaturmätning från respektive format, validerade informationen och skrev ut den i ett strukturerat format.
Resultatet visar att JSON och XML kan användas för att överföra samma typ av sensordata, även om representationen och biblioteksanvändningen skiljer sig åt.

## Lärdomar:
Under Dag 4 lärde jag mig:

- Skillnaden mellan JSON- och XML-struktur.
- Hur JSON kan parsas och serialiseras med nlohmann/json.
- Hur XML kan parsas och skapas med pugixml.
- Hur indata kan valideras innan den används.
- Hur undantag kan användas för att hantera ogiltig data.
- Hur CMake kan hämta och länka externa C++-bibliotek.
- Varför samma datamodell kan användas oavsett vilket dataformat som används.
