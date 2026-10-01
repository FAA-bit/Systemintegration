# Peer Review – Day 12

## Reviewer

- Reviewer: Nejirwan Ramadan (Neji)
- Date: 2026-01-10
- Project reviewed: Systemintegration

## Review Checklist

| Checkpoint | Result | Comment |
|---|---|---|
| System startup instructions were found | Pass | README contained build and startup instructions for both server & client |
| An implementation of a requirement was found | Pass | REQ-003 was traced to **retryable()** and **max_attempts** in **client.cpp**  |
| The requirement's test could be repeated or assessed | Pass | T11-Retry repeated using the **rate-limit** scenario. HTTP 429 caused a retry followed by HTTP 200|
| Relevant log/verification evidence was found | Pass | Client output showed 429 -> retry -> wait_ms=1000 -> 200 -> success. Server logged two attempts. |
| Safe recovery procedure could be identified | Not found / Cannot verify | Ingen tillgänglig återställningsfunktion |
| Swedish source was found and its use was understandable | Pass | MSB-källan är dokumenterad med användning och begränsning |
| English source was found and its use was understandable | Pass | RFC 9110 är dokumenterad med användning och begränsning |

## Findings

| ID | Observation | Severity | Responsible | Decision |
|---|---|---|---|---|
| PR-001 | The existing CMake build directory before testing was generated on Windows and then caused configuration errors on macOs. The build had to be removed and regenerated before the project could be tested | Low | Project Group | Document that the build directory should be regenerated when changing operative system or exclude build files from repo|
| PR-002 | A safe recovery procedure couldnt be identified in the reviewed documentation | Medium | Project Group | Add a recovery section on how to stop, restart and verify the system after a failure |
| PR-003 | | | | |

## Summary


### What worked well
- README provided clear build and startup instructions for the server and client
- REQ-003 could be traced from the matrix to implementation in `client.cpp`.
- The T11-RETRY test could be successfully repeated. HTTP 429 resulted in a retry followed by HTTP 200 and success
- Both the Swedish MSB source and English RFC 9110 source were documented with their purpose and limitations

### What needs improvement

- The existing CMake build directory caused errors when the project was built on macOS because it had been generated on Windows
- A safe recovey procedure could not be identified in the documentation

### Actions
- Add a recovery section on how to stop, restart and verify the system after a failure

## Final Decision

- [ ] Approved without changes
- [x] Approved with actions
- [ ] Requires another review