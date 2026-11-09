#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define STATUS_FILE "status.txt"
#define LOG_FILE "data/occupancy_log.csv"
#define GPIO_PIN 17

static int occupancy = 0;
static int capacity = 5;

/* Optional GPIO support: compile with -DUSE_PIGPIO -lpigpio on Raspberry Pi. */
#ifdef USE_PIGPIO
#include <pigpio.h>
static int gpio_ready = 0;
#endif

static void update_led(void) {
    int full = (occupancy >= capacity);
#ifdef USE_PIGPIO
    if (gpio_ready) gpioWrite(GPIO_PIN, full ? 1 : 0);
#else
    (void)full; /* Simulation mode: LED status is printed instead. */
#endif
}

static void save_status(void) {
    FILE *f = fopen(STATUS_FILE, "w");
    if (!f) { perror("status.txt"); return; }
    fprintf(f, "Occupancy: %d/%d\nStatus: %s\nLED: %s\n", occupancy, capacity,
            occupancy == capacity ? "ROOM FULL" : "SPACE AVAILABLE",
            occupancy == capacity ? "ON" : "OFF");
    fclose(f);
}

static void log_event(const char *event) {
    FILE *f = fopen(LOG_FILE, "a+");
    if (!f) { perror("occupancy log (run from project root)"); return; }
    if (fseek(f, 0, SEEK_END) == 0 && ftell(f) == 0)
        fprintf(f, "timestamp,event,occupancy,capacity,status\n");
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char timestamp[32] = "unknown";
    if (tm_info) strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "%s,%s,%d,%d,%s\n", timestamp, event, occupancy, capacity,
            occupancy == capacity ? "ROOM FULL" : "SPACE AVAILABLE");
    fclose(f);
}

static void refresh(void) { update_led(); save_status(); }

static void show_status(void) {
    printf("\nOccupancy: %d/%d\nStatus: %s\nLED: %s\n", occupancy, capacity,
           occupancy == capacity ? "ROOM FULL" : "SPACE AVAILABLE",
           occupancy == capacity ? "ON" : "OFF");
}

static int read_integer(const char *prompt, int *value) {
    char line[128], extra;
    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, " %d %c", value, &extra) != 1) {
        puts("Please enter a whole number.");
        return -1;
    }
    return 1;
}

int main(void) {
#ifdef USE_PIGPIO
    if (gpioInitialise() < 0) {
        fputs("GPIO initialization failed. Check pigpio installation/permissions.\n", stderr);
        return 1;
    }
    gpio_ready = 1;
    gpioSetMode(GPIO_PIN, PI_OUTPUT);
#else
    puts("Running in simulation mode (no physical LED control).");
#endif
    refresh();
    log_event("START");
    for (;;) {
        int choice, new_capacity, result;
        puts("\n--- STUDY ROOM OCCUPANCY TRACKER ---");
        puts("1. Student enters");
        puts("2. Student exits");
        puts("3. View status");
        puts("4. Change maximum capacity");
        puts("5. Quit");
        result = read_integer("Choose an option: ", &choice);
        if (result == 0) break;
        if (result < 0) continue;
        switch (choice) {
            case 1:
                if (occupancy >= capacity) puts("Entry denied: room is full.");
                else { occupancy++; puts("Student entered."); refresh(); log_event("ENTER"); }
                break;
            case 2:
                if (occupancy <= 0) puts("Exit denied: room is empty.");
                else { occupancy--; puts("Student exited."); refresh(); log_event("EXIT"); }
                break;
            case 3: show_status(); break;
            case 4:
                result = read_integer("Enter new capacity: ", &new_capacity);
                if (result == 0) goto done;
                if (result < 0) break;
                if (new_capacity < 1 || new_capacity < occupancy)
                    puts("Invalid capacity: must be at least 1 and not below current occupancy.");
                else { capacity = new_capacity; puts("Capacity updated."); refresh(); log_event("CAPACITY_CHANGED"); }
                break;
            case 5: goto done;
            default: puts("Invalid menu option.");
        }
    }
done:
    log_event("STOP");
#ifdef USE_PIGPIO
    if (gpio_ready) { gpioWrite(GPIO_PIN, 0); gpioTerminate(); }
#endif
    puts("Goodbye!");
    return 0;
}
