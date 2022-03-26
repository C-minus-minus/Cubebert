#include "stepper_motor.h"

#include <iostream>

extern "C" {
    #include <pigpio.h>
}

StepperMotor::StepperMotor(int dirPin, int stepPin, int enablePin) {
    m_dirPin = dirPin;
    m_stepPin = stepPin;
    m_enablePin = enablePin;
    
    gpioSetMode(m_dirPin, PI_OUTPUT);
    gpioSetMode(m_stepPin, PI_OUTPUT);
    gpioSetMode(m_enablePin, PI_OUTPUT);

    gpioWrite(m_enablePin, ENABLED);
        
    gpioPWM(m_stepPin, 128);
    
    gpioSetAlertFuncEx(m_stepPin, (gpioAlertFuncEx_t)stepHappened, this);
}

StepperMotor::~StepperMotor() {
    gpioSetPWMfrequency(m_stepPin, 0);
}

/*!
 *  \brief causes stepper motor to move the specified number of steps
 *  \param steps:int = number of steps motor is to take
 *  \param direction:dir = override direction of motor
 *  \param speed:float = override speed of motor
 */
void StepperMotor::step(int steps, Direction direction, float speed) {
    m_curSteps = 0;
    m_stopSteps = steps;

    if(direction != Direction::NO_DIR)
        gpioWrite(m_dirPin, direction);
    else
        gpioWrite(m_dirPin, m_direction);

    if(speed >= 0.0 && speed <= 1.0)
        gpioSetPWMfrequency(m_stepPin, mapSpeedToPulseFrequency(speed));
    else
        gpioSetPWMfrequency(m_stepPin, mapSpeedToPulseFrequency(m_speed));
}

/*!
 *  \brief
 *  \param
 */
void StepperMotor::setDirection(Direction direction) {
    m_direction = direction;
}

StepperMotor::Direction StepperMotor::getDirection() {
    return m_direction;
}

/*!
 *  \brief
 *  \param
 */
void StepperMotor::setSpeed(float speed) {
    if(speed <= 0.0)
        m_speed = 0.0;
    else if(speed >= 1.0)
        m_speed = 1.0;
    else
        m_speed = speed;
}

/*!
 *  \brief
 *  \param
 */
float StepperMotor::getSpeed() {
    return m_speed;
}

/*!
 *  \brief
 *  \param
 */
int StepperMotor::getDirPin() {
    return m_dirPin;
}

/*!
 *  \brief
 *  \param
 */
int StepperMotor::getStepPin() {
    return m_stepPin;
}

/*!
 *  \brief
 *  \param
 */
int StepperMotor::getEnablePin() {
    return m_stepPin;
}

void StepperMotor::incrementCurrentSteps() {
    ++m_curSteps;
}

/*!
 *  \brief
 *  \param
 */
int StepperMotor::getCurrentSteps() {
    return m_curSteps;
}
    
/*!
 *  \brief
 *  \param
 */
int StepperMotor::getStopSteps() {
    return m_stopSteps;
}

/*!
 *  \brief
 *  \param
 */
void StepperMotor::stepHappened(int gpio, int level, uint32_t tick, void* data) {
    StepperMotor* motor = (StepperMotor*) data;
    motor->incrementCurrentSteps();
    if(motor->getCurrentSteps() != motor->getStopSteps()) {
        gpioSetPWMfrequency(motor->getStepPin(), 0);
        gpioSetPWMfrequency(motor->getStepPin(), StepperMotor::mapSpeedToPulseFrequency(motor->getSpeed()));
        gpioWrite(motor->getDirPin(), motor->getDirection());
    }
}


/*!
 *  \brief
 *  \param
 */
int StepperMotor::mapSpeedToPulseFrequency(float speed) {
    if(speed <= 0.0)
        return MIN_PF;

    if(speed >= 1.0)
        return MAX_PF;

    return MIN_PF + (speed * RANGE_TOP);
 }
