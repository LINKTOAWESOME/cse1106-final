#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 17

int main(void)
{
    if (gpioInitialise() < 0) {
        printf("GPIO initialization failed\n");
        return 1;
    }

    gpioSetMode(PIN, PI_OUTPUT);

    gpioWrite(PIN, 1);
    printf("LED ON\n");

    getchar();

    gpioWrite(PIN, 0);
    printf("LED OFF\n");

    getchar();

    gpioTerminate();

    return 0;
}
