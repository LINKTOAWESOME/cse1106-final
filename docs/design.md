# Design

## Inputs
A menu option (1–5), and a new positive capacity for option 4.

## State
Two integers: `occupancy` (starts at 0) and `capacity` (starts at 5).

## Logic
- ENTER: if occupancy < capacity, increment, refresh status/LED, and log ENTER; otherwise deny.
- EXIT: if occupancy > 0, decrement, refresh status/LED, and log EXIT; otherwise deny.
- STATUS: print occupancy, status, and LED state.
- CAPACITY: reject values below 1 or below occupancy; otherwise update, refresh, and log.
- QUIT: log STOP, turn physical LED off, terminate GPIO.

## GPIO wiring
GPIO17 (physical pin 11) -> 1 kΩ resistor -> LED anode (+); LED cathode (-) -> GND (physical pin 9). Power off before wiring. `gpioWrite(17, 1)` when full, `gpioWrite(17, 0)` otherwise.

## Data flow
Keyboard menu -> validation -> occupancy/capacity update -> status.txt + GPIO output -> CSV log.

## Error handling
Noninteger input is rejected. Invalid menu selections and impossible occupancy changes do not modify the state. File-open failures are reported.
