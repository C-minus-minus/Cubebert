#include "stepper_motor.h"
#include "stb_image.h"

#include <chrono>
#include <thread>

extern "C" {
    #include <pigpio.h>
}

#define M1_DIR  24  // Direction Pin
#define M1_STEP 23  // Step Pin
#define M1_EN   18  // Enable Pin

#define M2_DIR  3  // Direction Pin
#define M2_STEP 2  // Step Pin
#define M2_EN   4  // Enable Pin

int main(int argc, char* argv[]) {
    if(gpioInitialise() >= 0) {
        StepperMotor* stepper1 = new StepperMotor(M1_DIR, M1_STEP, M1_EN);
        stepper1->step(1600);
        
        delete stepper1;
        
        gpioTerminate();
    }
    
    return 0;
}
