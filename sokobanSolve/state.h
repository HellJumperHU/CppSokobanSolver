//#pragma once
#ifndef STATE_H
#define STATE_H

#include "crate.h"
#include "sokoMap.h"
#include <vector>
#include <iostream>

class State
{
public:
	friend class SokoMap;
	State* firstState = nullptr;
	State* previousState = nullptr;
	State* nextState = nullptr;
	Position playerInitial;
	Position playerAtNonPushedCrate;
	Position playerAtPushedCrate;
	std::vector<Crate> crate;
	std::vector<Position> pathToOneCrateFreeSide;
	std::vector<Position> cratePushToNextPosition;
	short pushedCrateId;

	void SetFirstState(SokoMap sokoMap);
	void WriteOutAllInfo();
	bool IsStateDestination(SokoMap sokoMap);
	void WriteOutPaths();
	void WriteOutPathAsText();
	void CreateNewState(SokoMap sokoMap, State* newState);
	void CratePush();

private:

};
#endif // !STATE_H

