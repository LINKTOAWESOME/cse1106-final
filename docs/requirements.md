# Requirements — Option 2

1. The user can record a student entering the room.
2. The user can record a student exiting the room.
3. The program maintains a current occupancy count.
4. Occupancy cannot fall below zero.
5. Occupancy cannot exceed maximum capacity.
6. The program displays occupancy and `SPACE AVAILABLE` or `ROOM FULL`.
7. Valid occupancy events are written to a timestamped CSV log.
8. A red LED on GPIO 17 turns on at full capacity and off otherwise (Pi hardware build).
9. The user can change maximum capacity to a positive integer not below occupancy.

## Additional assumptions
- Default maximum capacity is 5.
- Each launch starts at occupancy 0; prior logs are preserved.
- Keyboard menu simulates entry and exit events (no physical occupancy sensor).
- A `status.txt` file contains the most recent status.
