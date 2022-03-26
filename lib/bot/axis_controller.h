#ifndef AXIS_CONTROLLER_H
#define AXIS_CONTROLLER_H

#include <map>

typedef struct MotorMove {
    char* motor;
    
};

class StepperMotor;

class AxisController {
public:
    AxisController();
    AxisController(std::map<char*, StepperMotor*> motors)
    ~AxisController();
    
    void addMotor(char* name, StepperMotor* motor);
    void queueMove();
    void queueMoves();
    
private:
    
};

#endif // AXIS_CONTROLLER_H
