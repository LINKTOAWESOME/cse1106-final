# Test Plan

Run `make && ./tracker` in the project root, or `make pi && sudo ./tracker` for physical GPIO testing. Record the actual outcome and pass/fail after running each test; these are planned tests, not claimed results.

| ID | Steps | Expected result | Actual result | Pass/Fail |
|---|---|---|---|---|
| T1 | Start program, choose 3 | 0/5, SPACE AVAILABLE, LED OFF | Not yet run | Pending |
| T2 | From 0/5 choose 2 | Exit denied; remains 0/5 | Not yet run | Pending |
| T3 | From 0/5 choose 1 five times | 5/5, ROOM FULL, LED ON | Not yet run | Pending |
| T4 | At 5/5 choose 1 | Entry denied; remains 5/5 | Not yet run | Pending |
| T5 | At 5/5 choose 2 | 4/5, SPACE AVAILABLE, LED OFF | Not yet run | Pending |
| T6 | At 4/5 choose 4 and enter 3 | Capacity rejected; remains 4/5 | Not yet run | Pending |
| T7 | At 4/5 choose 4 and enter 4 | 4/4, ROOM FULL, LED ON | Not yet run | Pending |
| T8 | Choose a letter at menu | Error message, no crash | Not yet run | Pending |
| T9 | Check `data/occupancy_log.csv` | Timestamped events saved | Not yet run | Pending |

## Demonstration checklist
- Show physical LED off when room is below capacity.
- Fill room using menu; show LED turns on.
- Attempt entry when full; show denial.
- Exit once; show LED turns off.
- Show CSV log and Git history.
