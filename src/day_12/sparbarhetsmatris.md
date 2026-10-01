# Spårbarhetsmatris

| Krav-ID | Testbart krav | Källa/version | Kontrakt eller kodreferens | Test-ID | Verifieringsbevis | Driftreferens | Status |
|---|---|---|---|---|---|---|---|
| REQ-001 | API-klienten ska kunna hantera ett lyckat API-svar och avsluta med `success`. | Day 11 – Robust API-klient | `client.cpp` – success-hantering | T11-OK | Scenario `ok`: HTTP 200, attempt=1, decision=success | `README.md` – `robust_api_client ok` | Verifierad |
| REQ-002 | HTTP 400 och 401 ska inte automatiskt återförsökas. | Day 11 – Robust API-klient | `client.cpp` – `retryable()` | T11-ERR | `bad-request`: 400 → stop. `unauthorized`: 401 → stop. | `README.md` – error scenarios | Verifierad |
| REQ-003 | HTTP 429 och 500 ska kunna orsaka ett kontrollerat återförsök, med högst 3 försök. | Day 11 – Robust API-klient | `client.cpp` – `retryable()`, `max_attempts = 3` | T11-RETRY | `rate-limit`: 429 → retry → 200. `flaky`: 500 → retry → 200. | `README.md` – retry scenarios | Verifierad |
| REQ-004 | Klienten ska använda timeout för API-anrop så att ett långsamt svar inte väntar obegränsat. | Day 11 – Robust API-klient | `client.cpp` – `timeout_ms = 400`, `set_receive_timeout()` | T11-TIMEOUT | `slow`: timeout/connection → stop | `README.md` – `slow` | Verifierad |
| REQ-005 | Klienten ska upptäcka och stoppa vid ogiltig JSON eller fel datatyp i ett HTTP 200-svar. | Day 11 – Robust API-klient | `server.cpp` – `bad-json`, `wrong-type`; `client.cpp` – validation | T11-CONTRACT | `bad-json` och `wrong-type` → `error=contract`, `decision=stop` | `README.md` – contract scenarios | Verifierad |

## Statusvärden

* Ej granskad: Underlaget är inte kontrollerat
* Pågår: Minst en länk eller verifiering saknas
* Verifierad: Kravet har godkänt testbevis och dokumenterade referenser
* Avvikelse: Resultatet följer inte kravet och kräver beslut

## Granskningsfrågor

* Kan en annan person förstå exakt vad som ska observeras?
* Är källans dokument, version och relevanta avsnitt identifierade?
* Leder kodreferensen till den plats där kravet realiseras?
* Innehåller testbeviset miljö, version, förväntat och faktiskt resultat?
* Är driftkonsekvensen dokumenterad?
