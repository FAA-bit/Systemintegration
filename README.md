# System Integration

This repository contains coursework in system integration with a focus on
network communication, REST APIs, IoT systems, structured data formats,
security, testing, troubleshooting, and documentation.

## Day 2 – TCP, UDP and Network Traffic

During Day 2, TCP and UDP communication programs were developed and tested
in C++.

The TCP implementation consists of a server and a client that establish a
connection, exchange messages, and receive responses. The UDP implementation
consists of a sender and receiver communicating using datagrams without first
establishing a connection.

The work also included compiling with Microsoft C++ and Winsock and observing
network traffic using Wireshark.

Communication was tested locally using:

- TCP: `127.0.0.1:5000`
- UDP: `127.0.0.1:5001`

See [Day 2 README](src/day_2/README.md) for build instructions, execution,
and Wireshark filters.


## Day 3 – REST API and CMake

During Day 3, a REST API was created in C++ using HTTP communication and JSON
data.

The project is configured and built using CMake. External dependencies are
downloaded using `FetchContent`.

The work provided practical experience with:

- REST APIs
- HTTP communication
- JSON
- CMake
- Project structure
- Microsoft Visual Studio
- Debug builds

See the [API documentation](src/day_3/API.md) and
[Day 3 README](src/day_3/README.md).


## Day 4 – JSON and XML

During Day 4, JSON and XML were compared as data formats for sensor
measurements.

Two C++ programs read, validate, and serialize the same temperature data:

- `json_demo.cpp` uses nlohmann/json.
- `xml_demo.cpp` uses pugixml.

The programs validate, among other things:

- Sensor ID
- Temperature value
- Unit
- Data types
- Valid temperature range

The temperature must be between `-50` and `100` degrees and the unit must be
`C`.

The project is built using CMake and demonstrates how the same data model can
be represented using different data formats.

See the [Day 4 README](src/day_4/README.md) and
[Day 4 report](src/day_4/Rapport.md).


## Day 5 – MQTT, API and Consumer

During Day 5, a larger integration flow for sensor data was developed for a
local IoT system.

The system demonstrates how sensor data can travel from a sensor through MQTT
to a broker, through an adapter to a REST API, and finally to a consumer that
displays the latest measurement.

The project includes:

- `sensor.cpp` – creates and validates measurements
- `capture.py` – receives MQTT messages
- `bridge.cpp` – sends data to the API
- `api.cpp` – stores the latest value and responds to HTTP requests
- `consumer.cpp` – retrieves and displays the latest measurement
- `contract_test.cpp` – verifies the data model rules

The flow runs locally on `127.0.0.1` using:

- MQTT: port `1885`
- HTTP: port `8085`

The work focuses on data validation, protocol integration, and testing of a
complete producer-to-consumer system.

See the [Day 5 README](src/day_5/README.md) and
[Day 5 report](src/day_5/Rapport.md).


## Day 6 – Network Namespaces, Routing and Firewall

During Day 6, an isolated network environment was created in Linux/WSL2
using four network namespaces:

- IoT network
- Service network
- Administration network
- Router

The client networks were connected to the router using virtual Ethernet
links and were separated from the host computer's normal network.

The work included:

- IP addresses
- Subnets
- Gateways
- Routing
- IPv4 forwarding
- Firewall rules
- Network isolation

`nftables` firewall rules were created to control traffic based on source,
destination, and destination port.

Network access was verified using Python-based TCP tests.

The lab also included status checks, firewall rule backups, an intentional
fault, and recovery.

See the [Day 6 documentation](src/day_6/Mydoc.md) and
[Day 6 report](src/day_6/Rapport.md).


## Day 7 – TLS, MQTTS and HTTPS

During Day 7, secure communication for IoT systems was studied and tested.

MQTTS was used to protect MQTT communication with TLS, while HTTPS was used
for secure HTTP communication.

The work included:

- TLS certificates
- Certificate authorities (CA)
- Certificate verification
- TLS errors
- API authentication
- Correct and incorrect API credentials

Tests were performed using both incorrect and correct certificates and API
keys.

See the [Day 7 report](src/day_7/rapport.md) and
[MQTTS README](src/day_7/demo_mqtts/README.md).


## Day 8 – Events, Timers and Reconnection

During Day 8, events, timers, threads, and reconnection were implemented and
tested in an IoT flow.

The work included both a C++ simulator and an ESP32-C6.

The simulator was used to test:

- Message publishing
- Message loss
- Reconnection
- Alarm events
- Event handling

The ESP32-C6 was used to test the IoT communication on physical hardware.

See the [ESP32 MQTTS README](src/day_8/demo_esp32_mqtts/README.md).


## Day 9 – Observability

During Day 9, an observable IoT flow was developed using logging, metrics,
and request IDs.

HTTP requests were tested using both successful and invalid requests.

Metrics were used to monitor:

- Total HTTP requests
- Accepted sensor readings
- Validation errors
- Unknown paths
- Request processing time

Network traffic was also analyzed using Wireshark on the loopback interface.

See the documentation under `src/day_9/`.


## Day 10 – Troubleshooting and Fault Hypotheses

During Day 10, systematic troubleshooting of an API system was performed.

A normal baseline was first established. Controlled faults were then
introduced and analyzed.

The tests included:

- Normal API requests
- Increased processing delay
- Connection errors
- HTTP 500 server errors
- HTTP 400 validation errors

Request IDs were used to connect client results with server log entries.

The troubleshooting process followed:

1. Establish a baseline.
2. Create a fault hypothesis.
3. Introduce a controlled fault.
4. Collect evidence.
5. Classify the fault.
6. Verify recovery.

See the [Day 10 report](src/day_10/rapport.md) and
[Troubleshooting README](src/day_10/demo_felsokning_cpp/README.md).


## Day 11 – Robust API Client

During Day 11, a robust C++ API client was developed.

The client handles:

- Successful responses
- Permanent HTTP errors
- Temporary HTTP errors
- Rate limiting
- Retries
- Retry delays
- Timeouts
- Invalid JSON
- Incorrect data types

The following scenarios were tested:

- `ok`
- `bad-request`
- `unauthorized`
- `rate-limit`
- `flaky`
- `bad-json`
- `wrong-type`
- `slow`

The client uses a controlled retry policy for temporary errors and stops
when an error should not be retried.

See the [Robust API Client README](src/day_11/demo_robust_api_cpp/README.md).


## Day 12 – From Requirements to Verification Evidence

During Day 12, requirements, implementation, API contracts, tests, and
verification evidence were connected using a traceability matrix.

The goal is to make it possible for another person to understand:

- What the system is supposed to do
- Where each requirement is implemented
- How each requirement is tested
- What evidence verifies the requirement
- How the system is started and troubleshooted

The work also includes source review in both Swedish and English.

Documentation created during Day 12:

- [Traceability Matrix](src/day_12/sparbarhetsmatris.md)
- [Source Review](src/day_12/kallgranskning.md)


## Build and Development Environment

The projects in this repository use different tools depending on the lab.

Common tools include:

- C++
- CMake
- Microsoft Visual Studio
- Visual Studio Code
- Windows PowerShell
- WSL2 / Ubuntu
- ESP32-C6
- ESP-IDF
- MQTT
- REST APIs
- JSON
- XML
- Wireshark
- Git and GitHub


## System Integration Progression

The coursework demonstrates a progression from basic network communication
to complete IoT system integration.

The progression includes:

1. TCP and UDP communication
2. REST APIs and HTTP
3. JSON and XML data formats
4. MQTT and sensor integration
5. Complete sensor-to-consumer integration
6. Network isolation and firewall configuration
7. TLS, MQTTS and HTTPS
8. Events, timers and reconnection
9. Logging, metrics and observability
10. Systematic troubleshooting
11. Robust API clients and retry handling
12. Requirements, traceability and verification evidence

Together, the labs demonstrate how IoT systems can be designed, integrated,
tested, secured, monitored, troubleshooted, and documented.