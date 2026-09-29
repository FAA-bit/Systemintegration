# Day 11 - Robust API Client

## Objective

Build and test a C++ API client that handles successful responses, temporary failures, permanent failures, invalid responses, and timeouts predictably.

## Setup

- Endpoint: `GET /api/config?scenario=<scenario>`
- HTTP port: `8093`
- Client timeout: `400 ms`

## Scenario Results

| Scenario | Observed response | Client behavior |
| --- | --- | --- |
| `ok` | HTTP 200 | Accepted immediately |
| `bad-request` | HTTP 400 | Stopped without retrying |
| `unauthorized` | HTTP 401 | Stopped without retrying |
| `rate-limit` | HTTP 429, then HTTP 200 | Retried after `1000 ms`; second attempt succeeded |
| `flaky` | HTTP 500, then HTTP 200 | Retried after `100 ms`; second attempt succeeded |
| `bad-json` | Invalid JSON | Reported a contract error and stopped |
| `wrong-type` | Incorrect data type | Reported a contract error and stopped |
| `slow` | Exceeded the client timeout | Reported `timeout_or_connection` and stopped |

## Retry Policy

The tests show that retries should depend on the failure type. Temporary server responses can be retried, while permanent client errors and responses that violate the API contract should stop immediately.

| Result | Recommended action |
| --- | --- |
| HTTP 200 | Accept the response |
| HTTP 400 or 401 | Stop; do not retry |
| HTTP 429 | Retry after the specified delay |
| HTTP 500 or 503 | Retry with backoff |
| Timeout | Stop |
| Invalid JSON or wrong data type | Stop; treat as an API contract error |

The `503` behavior is a recommendation; it was not one of the scenarios tested in this lab. Timeouts and bounded retry limits help prevent the client from waiting indefinitely.

## Conclusion

The lab demonstrated how a client can distinguish retryable temporary failures from permanent errors and invalid responses. Applying those decisions consistently makes API behavior more predictable and robust for an IoT system.