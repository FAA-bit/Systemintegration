

## Threat
I ran the thread program three times. In each run, the final value was `counter = 4000000` and `expected = 4000000`, which confirms that the program behaves correctly. The worker threads share the same counter, but a mutex protects the critical section so that only one thread can update it at a time. The `join()` calls ensure that the main thread waits until all worker threads have completed their work. Although the order of the printed output may vary because the operating system schedules threads independently, the final counter remains correct because access to the shared value is synchronized.

## Simulator
A suitable approach for the simulator is:
- Temperature and humidity: Keep only the latest value during an outage, since older readings become less relevant over time.
- Alarm: Store critical alarm events in RAM until the connection is restored, so that important alerts are not lost during a temporary network interruption.