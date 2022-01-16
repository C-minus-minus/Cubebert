#include "stepper_motor.h"

#include <iostream>

extern "C" {
    #include <pigpio.h>
}

int StepperMotor::m_curSteps = 0;

StepperMotor::StepperMotor(int dirPin, int stepPin, int enablePin) {
    m_dirPin = dirPin;
    m_stepPin = stepPin;
    m_enablePin = enablePin;
    
    gpioSetMode(m_dirPin, PI_OUTPUT);
    gpioSetMode(m_stepPin, PI_OUTPUT);
    gpioSetMode(m_enablePin, PI_OUTPUT);
        
    gpioWrite(m_dirPin, 1);
    gpioWrite(m_enablePin, ENABLED);
        
    gpioPWM(m_stepPin, 128);
    
    gpioSetAlertFuncEx(m_stepPin, (gpioAlertFuncEx_t)stepHappened, this);
}

StepperMotor::~StepperMotor() {
    gpioSetPWMfrequency(m_stepPin, 0);
}

void StepperMotor::step(int steps) {
    m_curSteps = 0;
    gpioSetPWMfrequency(m_stepPin, PULSE_FREQ);
    while(m_curSteps != steps) {}
    gpioSetPWMfrequency(m_stepPin, 0);
}

void StepperMotor::stepHappened(int gpio, int level, uint32_t tick) {
    m_curSteps++;
}
