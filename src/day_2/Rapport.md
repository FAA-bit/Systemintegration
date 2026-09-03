# # # Day 2 – TCP Server

## Syfte:
Syftet med Day 2 var att arbeta med grundläggande nätverkskommunikation genom att skapa och kompilera en TCP-server i C++. Målet var att förstå hur en server kan använda TCP för att ta emot och hantera anslutningar från klienter.

## Genomförande:
Arbetet genomfördes i Visual Studio Code och projektet låg i: src/day_2
Jag arbetade med filen: tcp_server.cpp
För att kompilera programmet användes Microsoft C++-kompilatorn, cl.exe, tillsammans med Windows-biblioteket ws2_32.lib.
Kompileringskommandot var: cl /EHsc tcp_server.cpp ws2_32.lib
Till en början fungerade inte kommandot eftersom PowerShell inte kunde hitta cl.
Felmeddelandet var: cl : The term 'cl' is not recognized...

## Problemlösning:
Problemet berodde på att Visual Studio Build Tools fanns installerat, men att Visual Studio C++-miljön inte var tillgänglig i den vanliga PowerShell-terminalens PATH.
Visual Studio 2022 Community var installerat och innehöll Microsoft C++-kompilatorn.
C++-kompilatorn som senare hittades av CMake var: C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe
Det visade att MSVC-kompilatorn var korrekt installerad.

## Resultat:
Arbetet med Day 2 visade hur en C++-baserad TCP-server kan byggas med Microsofts C++-verktyg och Winsock-biblioteket.
En viktig del av arbetet var även felsökning av utvecklingsmiljön. Jag lärde mig att ett program kan vara korrekt installerat på datorn men ändå inte kunna köras från PowerShell om sökvägen till programmet inte finns i PATH.

## Lärdomar:
Under Day 2 lärde jag mig:
- Vad en TCP-server används till.
- Hur C++ kan användas för nätverksprogrammering.
- Att Windows använder Winsock för TCP/IP-kommunikation.
- Att ws2_32.lib behövs för Winsock-program.
- Hur man identifierar problem med PATH.
- Hur Visual Studio C++-verktygen används för att kompilera C++-program.
- Skillnaden mellan en vanlig PowerShell-terminal och Visual Studios Developer-miljö.
