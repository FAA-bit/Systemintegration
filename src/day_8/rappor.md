

## Threat
I ran the thread program three times. In each run, the final value was `counter = 4000000` and `expected = 4000000`, which confirms that the program behaves correctly. The worker threads share the same counter, but a mutex protects the critical section so that only one thread can update it at a time. The `join()` calls ensure that the main thread waits until all worker threads have completed their work. Although the order of the printed output may vary because the operating system schedules threads independently, the final counter remains correct because access to the shared value is synchronized.

## Simulator
A suitable approach for the simulator is:
- Temperature and humidity: Keep only the latest value during an outage, since older readings become less relevant over time.
- Alarm: Store critical alarm events in RAM until the connection is restored, so that important alerts are not lost during a temporary network interruption.

## ESP32_mqtts

The ESP32-C6 application was built with ESP-IDF and flashed to the board successfully. The device connected to Wi-Fi and used separate FreeRTOS tasks for temperature and humidity events. The temperature task generated an event every five seconds, while the humidity task generated an event every seven seconds. A shared queue was used to send events to the publishing task, so the sensor tasks did not need to communicate directly with MQTT.

The application was designed to publish the sensor readings as JSON messages over MQTT using TLS. The MQTT broker used the secure `mqtts://` protocol on port `8883`, required a username and password, and used a CA certificate installed in the ESP32 firmware. The device also had reconnect logic for both Wi-Fi and MQTT, which is important when the network connection is interrupted.

The ESP32 successfully created its tasks and timers and generated sensor events. However, the complete MQTT/TLS connection was not verified yet. The remaining work is to check the broker certificate, IP address, credentials and connection logs, and then test that messages are published after the device reconnects. Events created while MQTT is disconnected are dropped according to the current policy, while counters are used to monitor created, published and dropped events.

## Summary of day 8 work.
During Day 8 I learned how threads, mutexes and join() work and how multiple event sources can be handled using a common queue.

The simulator demonstrated how events behave when the MQTT connection is interrupted. I also added an alarm event and verified the counters.

On the ESP32-C6, I successfully built and flashed the application. The ESP32 connected to Wi-Fi, created the required tasks and timers, and generated sensor events. The remaining part is to solve the MQTT/TLS connection and verify the complete disconnect/reconnect flow.

Overall, the lab gave me a better understanding of how asynchronous events, timers, queues and connection states work together in an IoT system.