# Day 10 – Systematic Troubleshooting

## Summary

The goal of the lab was to troubleshoot an IoT system systematically by establishing a normal baseline, introducing controlled faults, and using measurements and logs to identify the cause.

## Part A — Start check ✅
- Find/open the C++ demo.
- Start the server.
- Check: http://127.0.0.1:8091/health
- Run 3 requests.
- Verify the same request_id appears on client and server.
- Record the port and start command.

## Part B — Baseline 📊

We'll run the normal system at least twice and record: 
| Metric            |        Run 1 |        Run 2 |
| ----------------- | -----------: | -----------: |
| Requests          |           20 |           20 |
| Successes         |           20 |           20 |
| Failures          |            0 |            0 |
| Error fraction    |           0% |           0% |
| Throughput        | 15.798 req/s | 15.625 req/s |
| Min latency       |     4.642 ms |     3.101 ms |
| Average latency   |     8.232 ms |     5.429 ms |
| p95 latency       |     8.542 ms |     6.822 ms |
| Max latency       |    39.305 ms |    16.011 ms |
| HTTP 400          |            0 |            0 |
| HTTP 500          |            0 |            0 |
| Connection errors |            0 |            0 |
Both runs were successful:
- 40/40 requests succeeded
- 0 failures
- 0 connection errors
- No HTTP 400 or 500 responses
- Normal latency was roughly 3–8 ms for most requests
- Run 1 had one larger maximum of 39.305 ms
This gives us our normal baseline.

## Part C — Controlled delay 🔧

Now, I will introduce my first controlled fault.
Before testing, this is my hypothesis.
Hypothesis: If the server adds an artificial processing delay, client latency should increase by approximately the same amount, while the server's processing_ms should also increase. I will be using a 100 ms delay. ´ .\build\Debug\troubleshooting_server.exe --delay-ms 100´

Hypothesis result: 
| Metric            |    Normal baseline | With 100 ms delay |
| ----------------- | -----------------: | ----------------: |
| Requests          |                 20 |                20 |
| Successes         |                 20 |                20 |
| Failures          |                  0 |                 0 |
| Average latency   |   8.232 / 5.429 ms |    **114.071 ms** |
| p95 latency       |   8.542 / 6.822 ms |    **118.445 ms** |
| Maximum latency   | 39.305 / 16.011 ms |    **121.339 ms** |
| Throughput        |        ~15.7 req/s |   **5.805 req/s** |
| Connection errors |                  0 |                 0 |
The result supports the hypothesis. The client latency increased from roughly 5–8 ms normally to about 114 ms with the 100 ms delay.

## Part D — Three fault types 🔎
We'll test these separately:
| Fault            | How we create it        |
| ---------------- | ----------------------- |
| Connection error | Client uses port `8092` |
| Server error     | `--failure-every 3`     |
| Validation error | `--invalid-every 3`     |
For each one i will be recording the client symptom, server log/no log, another piece of evidence, and classify where the fault occurs.

**Fault 1 Connection error:**
| Observation            | Result                        |
| ---------------------- | ----------------------------- |
| Client used wrong port | `8092`                        |
| Server listening       | `8091`                        |
| Successful requests    | `0/20`                        |
| Connection errors      | `20`                          |
| HTTP 400/500           | `0`                           |
| Fault location         | Client/network connection     |

**Fault 2 — Server error:**
In the server run: .\build\Debug\troubleshooting_server.exe --failure-every 3
Client results:
- Attempts:          20
- Successes:         14
- Failures:           6
- Error fraction:   0.300
- HTTP 400:           0
- HTTP 500:           6
- Connection errors:  0

The server shows simulated failures on:
- day10-003 → 500
- day10-006 → 500
- day10-009 → 500
- day10-012 → 500
- day10-015 → 500
- day10-018 → 500

Conclusion:
The connection itself was working because: connection_errors = 0
The problem occurred inside the server, which returned HTTP 500 responses

**Fault 3 — Validation error**
This time:
- Server connection should work normally.
- The server will intentionally treat every 3rd request as invalid.
- We expect HTTP 400 Bad Request responses.
- Run the client with invalid data every 3rd request: .\build\Debug\troubleshooting_client.exe --invalid-every 3

The clients result:
- Attempts:          20
- Successes:         14
- Failures:           6
- Error fraction:   0.300
- HTTP 400:           6
- HTTP 500:           0
- Connection errors:  0

Summary:
| Fault               | Client result        | Server reached? | Classification     |
| ------------------- | -------------------- | --------------- | ------------------ |
| Wrong port `8092`   | 20 connection errors | ❌ No            | Connection/network |
| `--failure-every 3` | 6 × HTTP 500         | ✅ Yes           | Server/application |
| `--invalid-every 3` | 6 × HTTP 400         | ✅ Yes           | Validation/input   |

## Final result

The lab demonstrated how to use baseline measurements, latency, HTTP status codes, connection errors, server logs and request IDs to systematically locate faults in an IoT system.