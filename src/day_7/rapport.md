## Day 7 – Lab Report
TLS, Authentication and Secrets

1. Purpose
The purpose of this lab was to understand how TLS, authentication, and secret management can protect communication in an IoT system.

2. MQTTS Tests
I tested an MQTT connection using TLS.
- Wrong CA: TLS verification failed
- The client did not trust the broker certificate.
- Correct CA: The sensor data was successfully received: {"sensorId":"room-a-temp-01","value":21.7,"unit":"C"}
- The test result was 2/2 expected outcomes.

3. Certificate Inspection
The certificate contained:
- Name: localhost
- IP: 127.0.0.1
- Issuer: IOT25 MQTT Demo CA
- Valid until: 17 September 2026
- The client uses 'generated/ca.crt' to verify the server certificate

4. HTTPS Authentication
I also tested the HTTPS server.
- Wrong API key: 'python3 https_client.py --trust-ca --api-key felaktig'
and you get: HTTP 401 {"error":"unauthorized"}
- Correct API key: 'python3 https_client.py --trust-ca --api-key "iot25-local-demo-key"'
and you get: HTTP 200 {"sensorId": "room-a-temp-01", "value": 21.7, "unit": "C"}

5. Threats and Security
Two important threats were identified:
- Fake server/broker → prevent with certificate verification.
- Wrong or leaked API key → reject unauthorized clients.

6. Conclusion
The lab showed that TLS and authentication are two different security layers. TLS verifies and protects the connection, while the API key determines whether the client is authorized to use the service.
The successful MQTTS and HTTPS tests demonstrated how these security mechanisms can be applied to an IoT communication system.
