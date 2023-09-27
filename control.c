#include <stdbool.h>
#include <math.h>

#include "grader.h"

bool liftoff_detected;
bool apogee_detected;

float lowest_pressure;

const float GYRO_STOP_THRESHOLD = 0.1;
const float MIN_LIFTOFF_ACCELERATION = 10.5;
const float PRESSURE_CHANGE_FACTOR = 1.003; //I'm looking for a 200/75000 pascal bump, that is roughly 3/1000

void init() {
    liftoff_detected = false;
    apogee_detected = false;
    lowest_pressure = MAXFLOAT;
}

void update(float acc_x, float acc_y, float acc_z, float gyro_x, float gyro_y,
            float gyro_z, float baro)
{
    if(!liftoff_detected){
        double acc_magnitude = sqrt(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2));
        if(acc_magnitude > MIN_LIFTOFF_ACCELERATION){
            liftoff();
            liftoff_detected = true;
        }
    }

    if(liftoff_detected && !apogee_detected){
        if (baro < lowest_pressure) {
            lowest_pressure = baro;
        }

        else if(baro > lowest_pressure * PRESSURE_CHANGE_FACTOR){
            apogee();
            apogee_detected = true;
        }
    }

    if(apogee_detected){
        double gyro_magnitude = sqrt(pow(gyro_x, 2) + pow(gyro_y, 2) + pow(gyro_z, 2));

        if(gyro_magnitude < GYRO_STOP_THRESHOLD){
                landed();
        }
    }
}

