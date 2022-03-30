#include <iostream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include "TableManager.h"
#include "CubeSearch.h"

std::vector<std::string> stringToVector(std::string solution) {
    std::vector<std::string> list;
    std::stringstream scrambleStream(solution);
    std::string currMove;
    while (scrambleStream >> currMove) {
        list.push_back(currMove);
    }
    return list;
}

std::string vectorToString(std::vector<std::string> alg) {
    std::string ans = "";
    for (int i = 0; i < alg.size(); i++) {
        ans += " " + alg[i];
    }
    return ans;
}

std::string convertTo4Arm(std::string solution) {

    std::unordered_map<std::string, std::string> xMoves;
    std::unordered_map<std::string, std::string> zMoves;
    std::unordered_map<std::string, std::string> xPrimeMoves;
    std::unordered_map<std::string, std::string> zPrimeMoves;
    std::vector<std::string> rotations = { "X", "Z"};

    for (int i = 0; i < CubeConstants::PHASE_1_MOVE_COUNT; i++) {
        xMoves[CubeConstants::PHASE_1_MOVES[i]] = CubeConstants::PHASE_1_X_ROTATE_MOVES[i];
        xPrimeMoves[CubeConstants::PHASE_1_X_ROTATE_MOVES[i]] = CubeConstants::PHASE_1_MOVES[i];
        zMoves[CubeConstants::PHASE_1_MOVES[i]] = CubeConstants::PHASE_1_Z_ROTATE_MOVES[i];
        zPrimeMoves[CubeConstants::PHASE_1_Z_ROTATE_MOVES[i]] = CubeConstants::PHASE_1_MOVES[i];
    }

    class AlgorithmBranch {
    public:
        std::vector<std::string> algorithm;
        std::vector<std::string> rotations;
        int moves;
        AlgorithmBranch(std::vector<std::string> algorithm, std::vector<std::string> rotations, int moves) {
            this->algorithm = algorithm;
            this->rotations = rotations;
            this->moves = moves;
        }
    };

    std::vector<std::string> algList = stringToVector(solution);
    std::queue<AlgorithmBranch> queue;
    queue.push(AlgorithmBranch({}, {}, 0));

    while (!queue.empty()) {

        bool solved = true;
        bool terminateLoop = false;
        AlgorithmBranch current = queue.front();
        queue.pop();

        for (int move = current.moves; move < algList.size(); move++) {

            //  convert move
            std::string convertedMove = algList[move];
            for (int i = 0; i < current.rotations.size(); i++) {

                if (current.rotations[i] == "X") {
                    convertedMove = xMoves[convertedMove];
                }
                else if (current.rotations[i] == "Z") {
                    convertedMove = zMoves[convertedMove];
                }
            }

            if (convertedMove == "U" || convertedMove == "D" || 
                convertedMove == "U'" || convertedMove == "D'" || 
                convertedMove == "U2" || convertedMove == "D2") {

                int finalMove = move;
                for (int rotation = 0; rotation < rotations.size(); rotation++) {
                    std::vector<std::string> newRotations = current.rotations;
                    newRotations.push_back(rotations[rotation]);
                    std::vector<std::string> newAlgorithm = current.algorithm;
                    newAlgorithm.push_back(rotations[rotation]);
                    queue.push(AlgorithmBranch(newAlgorithm, newRotations, finalMove));
                }
                solved = false;
                terminateLoop = true;
            }
            else {
                current.algorithm.push_back(convertedMove);
                current.moves++;
            }
            if (terminateLoop) {
                break;
            }
        }
        if (solved) {
            return vectorToString(current.algorithm);
        }
    }
    return "";
}