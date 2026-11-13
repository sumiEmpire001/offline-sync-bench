# Offline Sync Bench — C++11 embedded queue

Fixed-capacity, allocation-free pending record queue for Arduino/ESP32 synchronization experiments. Each record has a nonzero ID and version. Version conflicts and stale acknowledgments are rejected; acknowledgments are idempotently recognized; acknowledged records can be compacted to reclaim slots. FIFO is by first insertion, with updates retaining their original position.

## Host verification
```sh
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
```

## Important limitations
RAM-only; reset loses all pending updates. No real transport, encryption, persistent journal, clock, retry/backoff, distributed conflict resolution or exactly-once guarantees. **Do not use for safety-critical actuator commands.** The serial example uses no Wi-Fi and does not operate hardware. A production ESP32 implementation needs durable flash/NVS with wear management, crash-consistent writes, authenticated transport, explicit server acknowledgments, bounded retries and reboot tests. The sample relative include path may need adjustment in Arduino IDE. Host CI does not verify board compilation. This repository previously contained only a placeholder, not a Python implementation.
