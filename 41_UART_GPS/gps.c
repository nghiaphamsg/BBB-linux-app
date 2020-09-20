#include <stdio.h>
#include <stdlib.h>
#include <gps.h>

int main(void) {
    // Open
    gps_init();

    loc_t data;

    while (1) {
        gps_location(&data);

        printf("The location is %lf,%lf\n", data.latitude, data.longitude);
        printf("Altitude: %lf m. Speed: %lf knots\n", data.altitude, data.speed);
    }

    return EXIT_SUCCESS;
}