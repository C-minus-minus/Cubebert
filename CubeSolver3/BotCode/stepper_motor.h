#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#define MIN_PF      384
#define MAX_PF      768
#define PULSE_FREQ  MAX_PF

#define ENABLED 0
#define DISABLED 1

#include <stdint.h>

class StepperMotor {
public:
    StepperMotor(int dirPin, int stepPin, int enablePin);
    ~StepperMotor();
    
    void step(int steps);
    static void stepHappened(int gpio, int level, uint32_t tick);
    
private:
    int m_dirPin;
    int m_stepPin;
    int m_enablePin;
    
    static int m_curSteps;
};

#endif // STEPPER_MOTOR_H
