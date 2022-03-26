#include "axis_controller.h"

AxisController::AxisController() {
}

AxisController::AxisController(std::map<char*, StepperMotor*> motors) {
}

AxisController::~AxisController() {
}
    
void AxisController::addMotor(char* name, StepperMotor* motor) {
}

void AxisController::queueMove() {
}

void AxisController::queueMoves() {
}
