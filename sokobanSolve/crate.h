//#pragma once
#ifndef CRATE_H
#define CRATE_H

#include "freeSideQuality.h"
#include <vector>
#include "sokoMap.h"

class Crate
{
public:
	friend class SokoMap;
	short id = -1;
	unsigned short queuePos;
	Position cratePosition;
	std::vector<FreeSideQuality> freeSides;
	std::vector<Position> possibleMovement;
	std::vector<bool> isNthTargetReachable;
	short numberOfCratesBlockingTheWayToReachIt = 0;


	void GetPushableSides(SokoMap sokoMap);
	bool IsAtTarget(SokoMap sokoMap);

private:

};

#endif // !CRATE_H