//#pragma once
#ifndef SOKOMAP_H
#define SOKOMAP_H

#include "state.h"
#include "position.h"
#include <vector>

class SokoMap
{
public:
	friend class State;
	friend class Crate;
	friend class Path;
	char** sokobanMap =nullptr;
	unsigned short row;
	unsigned short column;
	std::vector<Position> targetPosition;

	void SetCharAtPosTo(Position pos, char toChar);
	void GatherTargetPositions();
	void SetToTemplateMap();
	void SetToMatchCurrentState(State* state);
	void WriteOutMap();
	bool IsOccupied(State* state, Position targetPos);

private:

};

#endif // SOKOMAP_H