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
    void setSpeed(float speed);
    static void stepHappened(int gpio, int level, uint32_t tick);
    
private:
    Direction m_direction;
    float m_speed;

    int m_dirPin;
    int m_stepPin;
    int m_enablePin;
    
    static int m_curSteps;

    int mapSpeedToPulseFrequency(float speed);
};

#endif // STEPPER_MOTOR_H
