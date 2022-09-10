#pragma once
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <sstream>
#include "CubeConstants.h"
#include "CubeMath.h"

class StickerCube {

	private:
		int** cubeState;

	public:

		StickerCube();
		StickerCube(int** faces);
		StickerCube(int** faces, int* orientation);
		StickerCube(std::string scramble);
		~StickerCube();

		int** getCubeState();

		void applyScramble(std::string scramble);
		void applyMove(std::string move);

		void turnUp();
		void turnLeft();
		void turnRight();
		void turnDown();
		void turnFront();
		void turnBack();

		static StickerCube* fromCornerPermutation(int coord);
		static StickerCube* fromEdgePermutation(int coord);
		static StickerCube* fromUDSlice(int coord);

		int getPhase1EdgeCoordinate();
		int getPhase1CornerCoordinate();
		int getPhase1UdsliceCoordinate();

		int getPhase2EdgeCoordinate();
		int getPhase2CornerCoordinate();
		int getPhase2UdsliceCoordinate();

		int getPhase2Bar1Coordinate();
		int getPhase2Bar2Coordinate();
		int getPhase2Bar3Coordinate();
		int getPhase2Bar4Coordinate();

		//int getPhase2Side1Coordinate(int** edges, int sizeEdges, int** corners, int sizeCorners);
		int getPhase2Side1Coordinate();
		int getPhase2Side2Coordinate();


	private:

		void applyTurn(
			const int side,
			const int* outsideCorner1,
			const int* outsideCorner2,
			const int* outsideEdge,
			const int* outsideSide);
};

