#include "ClawAlgorithm.h"

/**
 * Generates a set of instruction for Cubert to solve given an algorithm in standard notation
 * @param algorithm - standard notation rubiks cube algorithm with U and D type turns excluded.
 */
ClawAlgorithm::ClawAlgorithm(std::string algorithm) {
    this->generateAlgorithm(algorithm);
}


/**
 * Generates a set of instruction for Cubert to solve given an algorithm in standard notation
 * @param algorithm - standard notation rubiks cube algorithm with U and D type turns excluded
 */
void ClawAlgorithm::generateAlgorithm(std::string algorithm) {
    this->steps.clear();

    std::stringstream scrambleStream(algorithm);
    std::string currMove;

    while (scrambleStream >> currMove) {
        
        //  populate this->steps
    }
}