#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#define MIN_PF      384
#define MAX_PF      768
#define RANGE_TOP   MAX_PF - MIN_PF

#define ENABLED 0
#define DISABLED 1

#include <stdint.h>

class StepperMotor {
public:
    StepperMotor(int dirPin, int stepPin, int enablePin);
    ~StepperMotor();
    
    enum Direction {
        NO_DIR = -1,
        CW = 0,
        CCW = 1
    };

    void step(int steps, Direction direction = Direction::NO_DIR, float speed = -1);
    
    void setDirection(Direction direction);
    Direction getDirection();
    
    void setSpeed(float speed);
    float getSpeed();

    int getDirPin();
    int getStepPin();
    int getEnablePin();

    void incrementCurrentSteps();
    int getCurrentSteps();

    int getStopSteps();
    
    static void stepHappened(int gpio, int level, uint32_t tick, void* data);
    
private:
    Direction m_direction;
    float m_speed;

    int m_dirPin;
    int m_stepPin;
    int m_enablePin;
    
    int m_curSteps;
    int m_stopSteps;
    
    int mapSpeedToPulseFrequency(float speed);
};

#endif // STEPPER_MOTOR_H
