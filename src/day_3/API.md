Day 3 – REST API och CMake
Syfte:
Syftet med Day 3 var att arbeta vidare med systemintegration genom att skapa och bygga ett projekt för ett REST API.

Målet var att förstå hur ett API kan fungera som en integrationsyta mellan olika program och tjänster.

Projektet låg i:

src/day_3

och innehåll bland annat:

main.cpp

samt en CMakeLists.txt som används för att konfigurera och bygga projektet.

CMake

För att bygga projektet användes CMake.

Först kontrollerades om CMake var installerat:

cmake --version

PowerShell kunde först inte hitta CMake och gav följande fel:

cmake : The term 'cmake' is not recognized...

Därefter undersöktes Visual Studio-installationen och CMake hittades i Visual Studio 2022 Community:

C:\Program Files\Microsoft Visual Studio\2022\Community\
Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe

Versionen som användes var:

cmake version 3.31.6-msvc6

CMake lades därefter till i den aktuella PowerShell-sessionens PATH.

Konfigurering av projektet

Projektet konfigurerades med:

cmake -S .\src\day_3 -B .\src\day_3\build

CMake identifierade Visual Studio 2022 som generator:

-- Building for: Visual Studio 17 2022

CMake hittade även Microsoft C++-kompilatorn:

-- The CXX compiler identification is MSVC 19.44.35228.0

Projektet konfigurerades utan kritiska fel och build-filer skapades i:

src/day_3/build
Bygga projektet

Efter konfigureringen byggdes projektet med:

cmake --build .\src\day_3\build --config Debug

Bygget genomfördes framgångsrikt.

Det genererade programmet var:

rest_api.exe

och placerades i:

src/day_3/build/Debug/rest_api.exe

Detta bekräftade att projektets CMake-konfiguration, Microsoft C++-kompilator och byggprocess fungerade korrekt.

JSON

Under konfigureringen visade CMake även att projektet använder JSON-biblioteket:

Using the multi-header code from .../_deps/json-src/include/

Det innebär att projektet har stöd för att arbeta med JSON-data, vilket är vanligt i REST API-kommunikation.

JSON används ofta för att strukturera data som skickas mellan en klient och en server.

Resultat

Day 3 avslutades med ett lyckat bygge av REST API-projektet.

Programmet genererades som:

rest_api.exe

och kan köras från projektets rotmapp med:

.\src\day_3\build\Debug\rest_api.exe
Lärdomar

Under Day 3 lärde jag mig:
- Vad CMake används till.
- Hur CMakeLists.txt styr byggprocessen.
- Hur man konfigurerar ett C++-projekt med CMake.
- Hur CMake använder Visual Studio som build-system.
- Hur MSVC används som C++-kompilator.
- Hur ett projekt byggs i Debug-konfiguration.
- Hur JSON kan användas i samband med REST API.
- Hur man felsöker problem när cmake inte hittas av PowerShell.
- Hur man hittar var installerade utvecklingsverktyg finns på Windows.