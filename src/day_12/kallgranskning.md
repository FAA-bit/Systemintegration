# Källgranskning

## Källa 1 – Svenska

* **Fullständig referens och länk:**  
  MSB, *Grundläggande säkerhet i cyberfysiska system*, Vägledning, december 2021.  
  https://rib.msb.se/filer/pdf/29983.pdf

* **Typ av källa:**  
  Svensk myndighetsvägledning.

* **Påstående eller beslut som källan stöder:**  
  IoT-system kan vara en del av cyberfysiska system och behöver hanteras med cybersäkerhet i åtanke. Källan stödjer därför projektets fokus på säkerhet, dokumentation och skydd av IoT-system.

* **Varför källan är trovärdig:**  
  Källan är publicerad av Myndigheten för samhällsskydd och beredskap (MSB), en svensk myndighet med ansvar inom bland annat cybersäkerhet och samhällsskydd.

* **Aktualitet eller version:**  
  Publicerad i december 2021.

* **Begränsning:**  
  Vägledningen ger generell vägledning och beskriver inte exakt hur vår specifika C++-klient eller vårt API ska implementeras.


## Källa 2 – Engelska

* **Fullständig referens och länk:**  
  Fielding, R. T., Nottingham, M. & Reschke, J., *RFC 9110 – HTTP Semantics*, IETF, June 2022.  
  https://www.rfc-editor.org/rfc/rfc9110.html

* **Typ av källa:**  
  Internationell teknisk standard/specifikation från IETF.

* **Påstående eller beslut som källan stöder:**  
  HTTP status codes beskriver resultatet av en HTTP-request. RFC 9110 definierar bland annat 2xx som lyckade svar, 4xx som klientfel och 5xx som serverfel. Detta används i Day 11 för att avgöra när API-klienten ska lyckas, stoppa eller försöka igen.

* **Varför källan är trovärdig:**  
  RFC 9110 är en Standards Track RFC från Internet Engineering Task Force (IETF) och har genomgått offentlig granskning och godkänts av IESG.

* **Aktualitet eller version:**  
  RFC 9110, publicerad juni 2022. Den ersätter flera tidigare HTTP-specifikationer.

* **Begränsning:**  
  RFC 9110 beskriver HTTP-semantik men bestämmer inte exakt vilken retry-policy en specifik IoT-klient ska använda.


## Terminologi

| Svenska | English | Betydelse i lösningen |
|---|---|---|
| Krav | Requirement | Ett mätbart villkor som systemet ska uppfylla. |
| Spårbarhet | Traceability | Kopplingen mellan krav, kod, test och verifieringsbevis. |
| Verifieringsbevis | Verification evidence | Resultat eller observation som visar att ett krav har testats. |
| Statuskod | Status code | HTTP-kod som beskriver resultatet av en request. |
| Återförsök | Retry | Ett nytt API-anrop efter ett tidigare misslyckat försök. |


## Kort teknisk sammanfattning

**Svenska, 80–120 ord:**

Källorna används för att koppla IoT-lösningen till både cybersäkerhet och tekniska HTTP-regler. MSB:s vägledning beskriver cyberfysiska system och inkluderar IoT-system som ett exempel. Den används som stöd för projektets säkerhets- och dokumentationsperspektiv. RFC 9110 beskriver HTTP:s semantik och statuskoder. Detta är relevant för Day 11 eftersom klienten använder HTTP-statuskoder för att avgöra om ett anrop ska lyckas, stoppas eller göras om. Källorna kompletterar därför projektets egna tester: MSB ger säkerhets- och systemperspektiv medan RFC 9110 ger den tekniska HTTP-grunden.


**English, 80–120 words:**

The sources connect the IoT solution to both cybersecurity and HTTP protocol requirements. The Swedish MSB guidance describes cyber-physical systems and includes IoT systems as an example. It is used to support the project's security and documentation perspective. RFC 9110 defines HTTP semantics and status codes. This is directly relevant to Day 11 because the API client uses HTTP status codes to decide whether a request should succeed, stop, or be retried. The sources therefore complement the project's own tests: the MSB guidance provides a security and system perspective, while RFC 9110 provides the technical foundation for HTTP communication and status handling.