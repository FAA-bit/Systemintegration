# Laboration 2 – TCP, UDP och observerbar nätverkstrafik

## Programmens roller

| Program | Roll | Protokoll |
|---|---|---|
| `tcp_server.cpp` | Server (lyssnar, accepterar, svarar) | TCP |
| `tcp_client.cpp` | Klient (ansluter, skickar, tar emot svar) | TCP |
| `udp_receiver.cpp` | Mottagare (bindar, tar emot datagram) | UDP |
| `udp_sender.cpp` | Sändare (skickar datagram, ingen anslutning) | UDP |

## Dokumenterade adresser och portar

| Flöde | IP | Port |
|---|---|---|
| TCP | 127.0.0.1 (lokalt test) | 5000 |
| UDP | 127.0.0.1 (lokalt test) | 5001 |

Byt `SERVER_IP` / `RECEIVER_IP` i respektive `.cpp`-fil till gruppens faktiska
IP-adress om ni kör klient och server på olika datorer (kräver lärarens tillåtelse).

## Bygga

**Linux (g++, POSIX-sockets):**
```bash
g++ -std=c++17 tcp_server.cpp -o tcp_server
g++ -std=c++17 tcp_client.cpp -o tcp_client
g++ -std=c++17 udp_receiver.cpp -o udp_receiver
g++ -std=c++17 udp_sender.cpp -o udp_sender
```

**Windows, MinGW (g++, Winsock):**
```bash
$env:Path += ";C:\msys64\ucrt64\bin"                             
>> cd "d:\STI - IoT25-VC\Systemintegration\Systemintegration\src\day_2"
g++ -std=c++17 tcp_server.cpp -o tcp_server.exe -lws2_32
g++ -std=c++17 tcp_client.cpp -o tcp_client.exe -lws2_32
g++ -std=c++17 udp_receiver.cpp -o udp_receiver.exe -lws2_32
g++ -std=c++17 udp_sender.cpp -o udp_sender.exe -lws2_32
```

**Windows, MSVC (Developer Command Prompt):**
```bash
cl /EHsc tcp_server.cpp ws2_32.lib
cl /EHsc tcp_client.cpp ws2_32.lib
cl /EHsc udp_receiver.cpp
cl /EHsc udp_sender.cpp
```
(`Ws2_32.lib` länkas automatiskt via `#pragma comment` i `net_common.h`.)

## Köra (lokalt test, 127.0.0.1)

TCP:
```bash
./tcp_server      # terminal 1 - starta först
./tcp_client       # terminal 2
```

UDP:
```bash
./udp_receiver    # terminal 1 - starta först
./udp_sender       # terminal 2
```

Verifierat med lokal körning: servern/mottagaren tar emot
`{"sensorId":"sensor-01","value":23.5,"unit":"C"}`, TCP-servern svarar
`{"status":"ok"}`.

## Wireshark

TCP:
```
tcp.port == 5000
```

UDP:
```
udp.port == 5001
```

Starta paketfångsten på loopback-gränssnittet (`lo`/`Loopback`) vid lokalt
test innan ni startar server/mottagare.

## Del 5 – Fel att testa (förslag)

- TCP-klienten pekar på fel `TCP_PORT` → `connect()` misslyckas direkt,
  ingen SYN/SYN-ACK-utväxling syns i Wireshark.
- UDP-sändaren körs innan mottagaren startat → datagrammet skickas ändå
  (UDP är connectionless) men går förlorat eftersom ingen lyssnar.

Dokumentera enligt kraven: vad ni ändrade, vad programmen visade, vad
Wireshark visade, hur ni hittade orsaken, hur ni verifierade att felet
var åtgärdat.

## Del 6 – Jämförelse (påbörjad, fyll i utifrån era observationer)

| Fråga | TCP | UDP | MQTT |
|---|---|---|---|
| Behövs en anslutning? | Ja (`connect`/`accept`) | Nej | Ja (till broker) |
| Bevaras meddelandegränser? | Nej (strömbaserat) | Ja (ett `recvfrom` = ett datagram) | Ja |
| Finns leveransgaranti i protokollet? | Ja | Nej | Beror på QoS-nivå |
| Känner sändaren till mottagaren direkt? | Ja (IP+port vid `connect`) | Ja (IP+port vid `sendto`) | Nej (broker förmedlar) |
| Vad händer om central tjänst/broker stoppas? | Ej tillämpligt (peer-to-peer) | Ej tillämpligt | Alla flöden stannar |
| När passar detta i ert IoT-case? | *fyll i* | *fyll i* | *fyll i* |
