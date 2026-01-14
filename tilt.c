#include <pebble.h>

#define TILT_THRESHOLD 120

typedef enum {
    D_DOWN,
    D_LEFT,
    D_UP,
    D_RIGHT,
    D_NONE
} Direction;

static int accel_cal_x;
static int accel_cal_y;

// I run this whenever I open/close a menu and return to the game
// Or when the user presses a directional button manually iirc
void calibrate_accel() {
    AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
    accel_service_peek(&accel);
    accel_cal_x = accel.x;
    accel_cal_y = accel.y;
}

// This yields the direction of tilt, or no tilt if within the deadzone
// The threshold is set by TILT_THRESHOLD, trial and error to see what feels right
Direction calculate_tilt() {
    AccelData accel = (AccelData) { .x = 0, .y = 0, .z = 0 };
    accel_service_peek(&accel);
    int accel_x = accel.x - accel_cal_x;
    int accel_y = accel.y - accel_cal_y;
    if (abs(accel_x) > abs(accel_y)) {
        if (accel_x < -TILT_THRESHOLD) {
            return D_LEFT;
        } else if (accel_x > TILT_THRESHOLD) {
            return D_RIGHT;
        }
    } else {
        if (accel_y < -TILT_THRESHOLD) {
            return D_DOWN;
        } else if (accel_y > TILT_THRESHOLD) {
            return D_UP;
        }
    }
    return D_NONE;
}

// Mock main loop to give an idea of the logic, really you would
// use timers or something to poll the accel every now and then
void main() { 
    calibrate_accel();

    Direction dir;
    while (1) {
        dir = calculate_tilt();
        // Do something with the tilt direction here
    }
}