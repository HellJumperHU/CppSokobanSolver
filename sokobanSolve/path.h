//#pragma once
#ifndef PATH_H
#define PATH_H

#include "position.h"
#include "sokoMap.h"
#include <vector>

class Path
{
public:
	Path* firstStepOfPath = nullptr;
	Path* previousStepOfPath = nullptr;
	Path* nextStepOfPath = nullptr;
	Position position;
	Position latestUsedMovement;
	std::vector<Position> possibleMovement;

	void SetFirstPartOfPath(SokoMap sokoMap, Position pos);
	void SetNextPartOfPath(SokoMap sokoMap, Position pos);
	void MovementVectorCopy(std::vector<Position> movement);
	void GetPossibleMovementsPlayer(SokoMap sokoMap);
	void GetPossibleMovementsCrate(SokoMap sokoMap);
	Position GetBestNextStep(SokoMap sokoMap, Position destinationPos);
	void RemoveAppliedBestStep(Position appliedStep);
	void ApplyBestStep(SokoMap& sokoMap, Position applicableStep);
	void CreateNewPathElementPlayer(Path* newPath, SokoMap sokoMap);
	void CreateNewPathElementCrate(Path* newPath, SokoMap sokoMap);


private:
};

void FindPathPlayer(SokoMap sokoMap, State* state, Position toPos2);
void FindPathCrate(SokoMap sokoMap, State* state, Crate fromCrate, Position toPos2);

float DistanceBetweenPositions(Position pos1, Position pos2);



#endif // !PATH_H