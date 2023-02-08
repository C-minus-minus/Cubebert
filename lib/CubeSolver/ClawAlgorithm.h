#pragma once
#include <vector>
#include <string>
#include <sstream>

/**
 * Represents a list of instruction for Cubert to execute an algorithm on the rubiks cube
 */
class ClawAlgorithm {
    
    public:
        //  List of instruction to execute algorithm
        std::vector<Step> steps;

        ClawAlgorithm(std::string algorithm);

    private:
        /**
         * Generates a set of instruction for Cubert to solve given an algorithm in standard notation
         * @param algorithm - standard notation rubiks cube algorithm with U and D type turns excluded.
         */
        void generateAlgorithm(std::string algorithm);
};

/**
 * Defines the position of the four claws (front, back, left, right)
 * and the claw rotation for a specific cube manuver
 */
class Step {

    public:

        Step(ClawPosition front, ClawPosition back, ClawPosition left, ClawPosition right, ClawRotation rotation) {
            this->front = front;
            this->back = back;
            this->left = left;
            this->right = right;
            this->rotation = rotation;
        }

        //  The position each claw needs to be before the rotation is applied
        ClawPosition front;
        ClawPosition back;
        ClawPosition left;
        ClawPosition right;

        //  The type of claw rotation to execute after setting up the claw positions
        ClawRotation rotation;
};

/**
 * Defines what state a claw should be in before a rotation happens
 */
enum ClawPosition {

    //  open claw position, no fingers gripping
    OPEN,

    //  partially closed claw position, only vertical fingers gripping
    VERTICAL,

    //  partially closed claw position, only horizontal fingers gripping
    HORIZONTAL,

    //  closed claw postion, both horizontal and vertical fingers gripping (may not be required)
    CLOSED
};

/**
 * Defines which claws should rotate and how far they should turn
 */
enum ClawRotation {

    //  Rotates 1 claw 90 degrees clockwise
    FRONT_CLOCKWISE, BACK_CLOCKWISE, LEFT_CLOCKWISE, RIGHT_CLOCKWISE,

    //  Rotates 2 claws 90 degrees clockwise
    FRONT_BACK_CLOCKWISE, LEFT_RIGHT_CLOCKWISE,

     //  Rotates 1 claw 90 degrees clockwise
    FRONT_COUNTERCLOCKWISE, BACK_COUNTERCLOCKWISE, LEFT_COUNTERCLOCKWISE, RIGHT_COUNTERCLOCKWISE,

    //  Rotates 2 claws 90 degrees counterclockwise
    FRONT_BACK_COUNTERCLOCKWISE, LEFT_RIGHT_COUNTERCLOCKWISE,

    //  Rotates both claws 180 degrees
    FRONT_BACK_DOUBLE, LEFT_RIGHT_DOUBLE,
};