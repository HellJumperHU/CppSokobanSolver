#include "solve.h"

void Solve(SokoMap sokoMap) {
	State* stateHEAD = new State;
	State* stateCurrent ;
	State* stateTmp;
	stateHEAD->SetFirstState(sokoMap);
	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(stateHEAD);
	GetReachableSidesOfCratesPushableSides(sokoMap, stateHEAD);
	stateCurrent = stateHEAD;
	stateTmp = stateHEAD;	
	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(stateCurrent);
	GetFirstPossibleCratePushToDestination(sokoMap, stateCurrent);
	FindPathPlayer(sokoMap, stateCurrent, stateCurrent->playerAtNonPushedCrate);
	
	if (!stateCurrent->cratePushToNextPosition.size())
	{
		stateCurrent = stateCurrent->previousState;
	}
	while (stateCurrent != nullptr && !stateCurrent->IsStateDestination(sokoMap))
	{
		if (stateCurrent->cratePushToNextPosition.size())
		{
			stateCurrent->CreateNewState(sokoMap, stateTmp);
			stateCurrent = stateCurrent->nextState;
			sokoMap.SetToTemplateMap();
			sokoMap.SetToMatchCurrentState(stateCurrent);
			if (stateCurrent->IsStateDestination(sokoMap))
			{
				break;
			}
			GetFirstPossibleCratePushToDestination(sokoMap, stateCurrent);
			FindPathPlayer(sokoMap, stateCurrent, stateCurrent->playerAtNonPushedCrate);
		}
		else
		{
			State* stateToBeDeleted;
			stateToBeDeleted = stateCurrent;
			stateCurrent = stateToBeDeleted->previousState;
			stateTmp = stateToBeDeleted->previousState;
			delete stateToBeDeleted;
		}
	}

	if (stateCurrent!=nullptr)
	{
		stateTmp = stateCurrent->firstState;
		for (stateTmp; stateTmp!=nullptr;)
		{
			stateTmp->WriteOutPathAsText();
			stateTmp = stateTmp->nextState;
		}
		for (stateCurrent; stateCurrent != nullptr;)
		{
			State* stateDelete;
			stateDelete = stateCurrent;
			stateCurrent = stateCurrent->previousState;
			delete stateDelete;
		}
	}
	else
	{
		delete stateHEAD;
	}
};

// Filter further the "pushable sides" that collected in the crate.cpp
// So only free sides remain that can be reached by the player in the current state
void GetReachableSidesOfCratesPushableSides(SokoMap sokoMap, State* state) {
	for (short i = 0; i < state->crate.size(); i++)
	{
		for (short j = state->crate[i].freeSides.size(); j > 0; j--)
		{
			state->pathToOneCrateFreeSide.clear();
			FindPathPlayer(sokoMap, state, state->crate[i].freeSides[j-1].freeSidePos);
			if (!state->pathToOneCrateFreeSide.size())
			{
				for (short l = 0; l < state->crate[i].possibleMovement.size(); l++)
				{
					if ((state->crate[i].cratePosition - state->crate[i].possibleMovement[l]) == state->crate[i].freeSides[j - 1].freeSidePos)
					{
						state->crate[i].possibleMovement.erase(state->crate[i].possibleMovement.begin() + l);
						break;
					}
				}
				state->crate[i].freeSides.erase(state->crate[i].freeSides.begin() + (j-1));
			}
		}
	}
	state->pathToOneCrateFreeSide.clear();
};

void GetFirstPossibleCratePushToDestination(SokoMap sokoMap, State* state) {
	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(state);
	for (short i = 0; i < state->crate.size(); i++)
	{
		if (!state->crate[i].IsAtTarget(sokoMap))
		{
			state->pushedCrateId = i;
			for (short j = 0; j < sokoMap.targetPosition.size(); j++)
			{
				if (!sokoMap.IsOccupied(state, sokoMap.targetPosition[j]))
				{
					FindPathCrate(sokoMap, state, state->crate[i], sokoMap.targetPosition[j]);
					if (state->cratePushToNextPosition.size())
					{
						break;
					}
				}
			}
		}
		if (state->cratePushToNextPosition.size())
		{
			break;
		}

	}

	if (state->cratePushToNextPosition.size())
	{
		state->playerAtNonPushedCrate = state->crate[state->pushedCrateId].cratePosition;
		state->playerAtNonPushedCrate -= state->cratePushToNextPosition[0];
	}
}