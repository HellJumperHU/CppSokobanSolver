#include "state.h"

void State::SetFirstState(SokoMap sokoMap) {
	this->firstState = this;
	for (unsigned short row = 0; row < sokoMap.row; row++)
	{
		for (unsigned short column = 0; column < sokoMap.column; column++)
		{
			if (sokoMap.sokobanMap[row][column] == '.') {
				Position tmpTarget;
				tmpTarget.SetPos(row, column);
				sokoMap.targetPosition.push_back(tmpTarget);
				continue;
			}

			else if (sokoMap.sokobanMap[row][column] == '$') {
				Crate tmpCrate;
				Position tmpPos;
				tmpPos.SetPos(row, column);
				tmpCrate.cratePosition = tmpPos;
				tmpCrate.id = this->crate.size();
				tmpCrate.GetPushableSides(sokoMap);
				this->crate.push_back(tmpCrate);
				continue;
			}
			else if (sokoMap.sokobanMap[row][column] == '@') {
				this->playerInitial.SetPos(row, column);
				continue;
			}

		}
	}
};

bool State::IsStateDestination(SokoMap sokoMap) {
	bool crateOnTargetPosition = true;
	for (short i = 0; i < this->crate.size() && crateOnTargetPosition; i++)
	{
		crateOnTargetPosition = false;
		for (short j = 0; j < sokoMap.targetPosition.size(); j++)
		{
			if (this->crate[i].cratePosition == sokoMap.targetPosition[j])
			{
				crateOnTargetPosition = true;
				break;
			}
		}
		if (crateOnTargetPosition == false)
		{
			return false;
		}

	}
	return true;
};

void State::WriteOutPaths() {
	std::cout << "PlayerToCrate" << "\n";
	for (short i = 0; i < this->pathToOneCrateFreeSide.size(); i++)
	{
		std::cout << this->pathToOneCrateFreeSide[i].x << "," << this->pathToOneCrateFreeSide[i].y << "\n";
	}
	std::cout << "PlayerPushCrate" << "\n";
	for (short i = 0; i < this->cratePushToNextPosition.size(); i++)
	{
		std::cout << this->cratePushToNextPosition[i].x << "," << this->cratePushToNextPosition[i].y << "\n";
	}
};

void State::WriteOutPathAsText() {
	for (short i = 0; i < this->pathToOneCrateFreeSide.size(); i++)
	{
		if (this->pathToOneCrateFreeSide[i].x == -1) {
			std::cout << "U"; continue;
		}
		if (this->pathToOneCrateFreeSide[i].x == 1) {
			std::cout << "D"; continue;
		}
		if (this->pathToOneCrateFreeSide[i].y == -1) {
			std::cout << "L"; continue;
		}
		if (this->pathToOneCrateFreeSide[i].y == 1) {
			std::cout << "R";continue;
		}

}
	for (short i = 0; i < this->cratePushToNextPosition.size(); i++) {

		if (this->cratePushToNextPosition[i].x == -1) {
			std::cout << "U"; continue;
		}
		if (this->cratePushToNextPosition[i].x == 1) {
			std::cout << "D"; continue;
		}
		if (this->cratePushToNextPosition[i].y == -1) {
			std::cout << "L"; continue;
		}
		if (this->cratePushToNextPosition[i].y == 1) {
			std::cout << "R"; continue;
		}
	}
};

void State::WriteOutAllInfo() {
	std::cout << "Player Initial Pos \n X: " << this->playerInitial.x << ", Y: " << this->playerInitial.y << "\n";
	std::cout << "Player At Non-Pushed Crate Pos \n X: " << this->playerAtNonPushedCrate.x << ", Y: " << this->playerAtNonPushedCrate.y << "\n";
	std::cout << "Player At Pushed Crate Pos \n X: " << this->playerAtPushedCrate.x << ", Y: " << this->playerAtPushedCrate.y << "\n";

	for (unsigned short i = 0; i < this->crate.size(); i++)
	{
		std::cout << "Crate "<< i <<"th Pos \n X : " << this->crate[i].cratePosition.x << ", Y : " << this->crate[i].cratePosition.y << "\n";
		std::cout << "Free sides: ";
		for (unsigned short j = 0; j < this->crate[i].freeSides.size(); j++)
		{
			std::cout << this->crate[i].freeSides[j].freeSidePos.x << "," << this->crate[i].freeSides[j].freeSidePos.y << "  ";
		}
		std::cout << "\n";
	}	

	this->WriteOutPaths();
};

void State::CreateNewState(SokoMap sokoMap, State* newState) {
	newState = new State;
	newState->firstState = this->firstState;
	newState->previousState = this;
	this->nextState = newState;

	for (short i = 0; i < this->crate.size(); i++)
	{
		newState->crate.push_back(this->crate[i]);
		newState->crate[i].freeSides.clear();
		newState->crate[i].possibleMovement.clear();
		newState->crate[i].numberOfCratesBlockingTheWayToReachIt = 0;
		newState->crate[i].queuePos = -2;
	}

	newState->playerInitial = this->playerAtNonPushedCrate;

	for (short i = 0; i < this->cratePushToNextPosition.size(); i++)
	{
		newState->crate[this->pushedCrateId].cratePosition += this->cratePushToNextPosition[i];
		newState->playerInitial += this->cratePushToNextPosition[i];
	}
	this->playerAtPushedCrate = newState->playerInitial;

	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(newState);

	for (short i = 0; i < newState->crate.size(); i++)
	{
		newState->crate[i].GetPushableSides(sokoMap);
	}
};

void State::CratePush() {
	Position tmpPos;
	tmpPos = this->previousState->crate[this->previousState->pushedCrateId].cratePosition;
	for (short i = 0; i < this->cratePushToNextPosition.size(); i++)
	{
		tmpPos += this->previousState->cratePushToNextPosition[i];
	}
	this->playerAtPushedCrate = this->crate[this->pushedCrateId].cratePosition - this->cratePushToNextPosition[0];
}