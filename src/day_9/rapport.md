# Day 9 – Make the IoT flow observable.

Observability means that we can understand what is happening inside a system through its external signals, above all:
            - Logs
            - Metrics
            - Traces / request IDs

## Summary
The goal of the lab was to make an IoT flow observable, enabling an understanding of system activity through structured logs and metrics. The lab requires a normal scenario, an intentional fault, at least one metric, and a reproducible troubleshooting guide.

## Part 1 - Build and run

The project was built with CMake:

```powershell
cmake -S . -B build
cmake --build build
The build created:
- observability_server.exe
- observability_client.exe
The server runs on: 127.0.0.1:8090

## Part 2 - Client/server test

The server was run on: 127.0.0.1:8090
The client sent four test requests. The result was:

| Request           | Status | Resultat         |
| ----------------- | -----: | ---------------- |
| `demo-temp-1`     |    202 | Accepted         |
| `demo-humidity-1` |    202 | Accepted         |
| `demo-invalid-1`  |    400 | Validation error |
| `demo-missing-1`  |    404 | Not found        |

This means the test was successful.
Key figures
- Accepted measurements: 2
- Validation errors: 1
- Unknown resources: 1
- HTTP requests in the client scenario: 4


## Part 3 - Correlate an error with request_id

I investigated: demo-invalid-1
The server log showed:
{ 
level: WARNING
event: reading_rejected
request_id: demo-invalid-1
method: POST
path: /api/readings
status: 400
duration_ms: 0.564
reason: value must be a finite number
}
The client received the same request_id back, along with the status: 400
Conclusion:
- This is a client/validation error, not a server error.
- The server functioned correctly:
- It received the request.
- It identified that the value was invalid.
- It logged the error.
- It returned HTTP 400.

## Part 4 - Metrics

I tested: curl.exe http://127.0.0.1:8090/api/metrics / curl.exe http://127.0.0.1:8090/metrics
I received, among other things:
- http_requests_total = 7
- readings_accepted_total = 2
- validation_errors_total = 1
- not_found_total = 1
- request_duration_ms_max = 8.018

## part 5 - Wireshark

Wireshark was used to capture localhost traffic.
Interface: Adapter for loopback traffic capture
Capture filter: tcp port 8090
Display filter: tcp.port == 8090 && http
Observed:
- 127.0.0.1 → 127.0.0.1
- Client port → 8090
- POST /api/readings
- POST /api/unknown
- 202 Accepted
- 400 Bad Request
- 404 Not Found
One captured connection used: 
- Source port: 53568
- Destination port: 8090
Because the connection used HTTP without TLS, the HTTP requests and JSON data were visible in Wireshark. With TLS, the application data would be encrypted.

## Part 6 - What i have implemented

My final improvement was: unknown_paths_total
Definition:
- Type: Counter
- Unit: Requests
- Increases: When an unknown API path is requested
- Purpose: Shows how many requests went to unknown resources
Verified result:
- http_requests_total       = 4
- readings_accepted_total   = 2
- validation_errors_total   = 1
- not_found_total           = 1
- unknown_paths_total       = 1

## Part 7 — Troubleshooting Guide

Important troubleshooting steps:
1. Build the project with CMake.
2. Start observability_server.exe.
3. Run observability_client.exe.
4. Check the HTTP status codes.
5. Check the server logs using the request_id.
7. Check /api/metrics.
8. Use Wireshark to inspect network traffic.
