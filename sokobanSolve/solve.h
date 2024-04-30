//#pragma once
#ifndef SOLVE_H
#define SOLVE_H

#include "sokoMap.h"
#include "state.h"
#include "path.h"
#include <iostream>

void Solve(SokoMap sokoMap);

void GetReachableSidesOfCratesPushableSides(SokoMap sokoMap, State* state);
void GetFirstPossibleCratePushToDestination(SokoMap sokoMap, State* state);
#endif // !SOLVE_H