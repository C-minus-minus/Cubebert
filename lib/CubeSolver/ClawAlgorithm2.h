#pragma once
#include <vector>
#include <string>
#include <sstream>

/**
 * Represents a list of instruction for Cubert to execute an algorithm on the rubiks cube
 */
class ClawAlgorithm2 {
    
    public:
        //  List of instruction to execute algorithm
        std::vector<Step> steps;

        ClawAlgorithm2(std::string algorithm);

    private:
        /**
         * Generates a set of instruction for Cubert to solve given an algorithm in standard notation
         * @param algorithm - standard notation rubiks cube algorithm with U and D type turns excluded.
         */
        void generateAlgorithm(std::string algorithm);
};

/**
 * Defines a single step of the algorithm.
 * 
 * Holds a list of actions that can all be (and should be) performed in paralel
 */
class Step {
    public:
        Step(std::vector<Action> actions) {
            this->actions = actions;
        }
        std::vector<Action> getActions();

    private:
        // A list of actions that can all be (and should be) performed in paralel
        std::vector<Action> actions;
};

/**
 * Defines a specific actionType for a specific claw
 */
class Action {
    public:
        Action(Claw claw, ActionType action) {
            this->claw = claw;
            this->action = action;
        }
        Claw getClaw();
        ActionType getActionType();
    
    private:
        //  The claw that is performing the action
        Claw claw;

        //  The action the claw is performing
        ActionType action;
};

/**
 * The four claws of the robot
 */
enum Claw {
    FRONT, BACK, LEFT, RIGHT
};

/**
 * Actions for a particular claw
 */
enum ActionType {

    //  grip or ungrip with the 2 horizontal fingers
    HORIZONTAL_GRIP, HORIZONTAL_UNGRIP, 
    
    //  grip or ungrip with the 2 vertical fingers
    VERTICAL_GRIP, VERTICAL_UNGRIP,

    // rotate the claw 90 degrees
    CLOCKWISE, COUNTERCLOCKWISE, 
    
    //  rotate the claw 180 degrees
    DOUBLE
};
