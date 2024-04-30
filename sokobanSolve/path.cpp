#include "path.h"
#include <math.h>


void Path::SetFirstPartOfPath(SokoMap sokoMap, Position pos) {
	this->firstStepOfPath = this;
	this->position = pos;
};

void Path::SetNextPartOfPath(SokoMap sokoMap, Position pos) {

};

void Path::GetPossibleMovementsPlayer(SokoMap sokoMap) {
	Position pos = this->position;

	if (sokoMap.sokobanMap[pos.x + 1][pos.y] != '#'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != '$'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != '@'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != 'x')
	{
		Position tmpPos;
		tmpPos.SetPos(1, 0);
		this->possibleMovement.push_back(tmpPos);
	};
	if (sokoMap.sokobanMap[pos.x - 1][pos.y] != '#'
		&& sokoMap.sokobanMap[pos.x - 1][pos.y] != '$'
		&& sokoMap.sokobanMap[pos.x - 1][pos.y] != '@'
		&& sokoMap.sokobanMap[pos.x - 1][pos.y] != 'x')
	{
		Position tmpPos;
		tmpPos.SetPos(-1, 0);
		this->possibleMovement.push_back(tmpPos);
	};

	if (sokoMap.sokobanMap[pos.x][pos.y + 1] != '#'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != '$'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != '@'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != 'x')
	{
		Position tmpPos;
		tmpPos.SetPos(0, 1);
		this->possibleMovement.push_back(tmpPos);
	};

	if (sokoMap.sokobanMap[pos.x][pos.y - 1] != '#'
		&& sokoMap.sokobanMap[pos.x][pos.y - 1] != '$'
		&& sokoMap.sokobanMap[pos.x][pos.y - 1] != '@'
		&& sokoMap.sokobanMap[pos.x][pos.y - 1] != 'x')
	{
		Position tmpPos;
		tmpPos.SetPos(0, -1);
		this->possibleMovement.push_back(tmpPos);
	};

};

void Path::GetPossibleMovementsCrate(SokoMap sokoMap) {
	Position pos = this->position;
	if (sokoMap.sokobanMap[pos.x - 1][pos.y] != '#'
		&& sokoMap.sokobanMap[pos.x - 1][pos.y] != '$'
		&& sokoMap.sokobanMap[pos.x - 1][pos.y] != 'x'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != '#'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != '$'
		&& sokoMap.sokobanMap[pos.x + 1][pos.y] != 'x')
	{
		Position movement;
		movement.SetPos(1, 0);
		this->possibleMovement.push_back(movement);
		movement.SetPos(-1, 0);
		this->possibleMovement.push_back(movement);
	};
	if (sokoMap.sokobanMap[pos.x][pos.y - 1] != '#'
		&& sokoMap.sokobanMap[pos.x][pos.y - 1] != '$'
		&& sokoMap.sokobanMap[pos.x][pos.y - 1] != 'x'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != '#'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != '$'
		&& sokoMap.sokobanMap[pos.x][pos.y + 1] != 'x')
	{
		Position movement;
		movement.SetPos(0, 1);
		this->possibleMovement.push_back(movement);
		movement.SetPos(0, -1);
		this->possibleMovement.push_back(movement);
	};
	pos += this->previousStepOfPath->latestUsedMovement;
	if (sokoMap.sokobanMap[pos.x][pos.y] != '#'
		&& sokoMap.sokobanMap[pos.x][pos.y] != '$'
		&& sokoMap.sokobanMap[pos.x][pos.y] != 'x') {
		Position movement;
		movement = this->previousStepOfPath->latestUsedMovement;
		this->possibleMovement.push_back(movement);
	}

}

float DistanceBetweenPositions(Position pos1, Position pos2) {
	float distance;
	distance = pow(pos1.x - pos2.x,2);
	distance += pow(pos1.y - pos2.y,2);
	return sqrt(distance);
};

Position Path::GetBestNextStep(SokoMap sokoMap, Position destinationPos) {
	float tmpSmallestDistance;
	tmpSmallestDistance = sokoMap.column * sokoMap.row;
	Position bestNextStep=this->position;
	for (unsigned short i = 0; i < this->possibleMovement.size(); i++)
	{
		float tmpDistance;
		tmpDistance = DistanceBetweenPositions(this->position + this->possibleMovement[i], destinationPos);
		if (tmpDistance<tmpSmallestDistance)
		{
			tmpSmallestDistance = tmpDistance;
			bestNextStep = this->possibleMovement[i];
		}
	}
	return bestNextStep;
};

void Path::RemoveAppliedBestStep(Position appliedStep) {
	this->latestUsedMovement = appliedStep;

	for (unsigned short i = 0; i < this->possibleMovement.size(); i++)
	{
		if (this->possibleMovement[i] == appliedStep)
		{
			this->possibleMovement.erase(this->possibleMovement.begin() + i);
			break;
		}
	}
};

void Path::ApplyBestStep(SokoMap& sokoMap, Position applicableStep) {
	this->RemoveAppliedBestStep(applicableStep);	
	if (sokoMap.sokobanMap[this->position.x][this->position.y] == '$') 
	{
		sokoMap.SetCharAtPosTo(this->position + applicableStep, '$');
	}
	else
	{
		sokoMap.SetCharAtPosTo(this->position + applicableStep, '@');
	}
	sokoMap.SetCharAtPosTo(this->position, 'x');
};

void Path::CreateNewPathElementPlayer(Path* newPath, SokoMap sokoMap) {
	newPath = new Path;
	newPath->firstStepOfPath = this->firstStepOfPath;
	newPath->previousStepOfPath = this;
	this->nextStepOfPath = newPath;
	newPath->position = this->position + this->latestUsedMovement;
	newPath->GetPossibleMovementsPlayer(sokoMap);
};

void Path::CreateNewPathElementCrate(Path* newPath, SokoMap sokoMap) {
	newPath = new Path;
	newPath->firstStepOfPath = this->firstStepOfPath;
	newPath->previousStepOfPath = this;
	this->nextStepOfPath = newPath;
	newPath->position = this->position + this->latestUsedMovement;
	newPath->GetPossibleMovementsCrate(sokoMap);

};

void Path::MovementVectorCopy(std::vector<Position> movement) {
	for (unsigned short i = 0; i < movement.size(); i++)
	{
		this->possibleMovement.push_back(movement[i]);
	}
};

void FindPathPlayer(SokoMap sokoMap, State* state, Position toPos2) {
	Path* HEAD;
	Path* currentPathElement;
	Path* tmpPath;

	Position fromPos1 = state->playerInitial;
	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(state);
	currentPathElement = new Path();
	currentPathElement->firstStepOfPath = currentPathElement;
	currentPathElement->position = fromPos1;
	currentPathElement->GetPossibleMovementsPlayer(sokoMap);
	HEAD = currentPathElement;
	tmpPath = currentPathElement;

	while (tmpPath != nullptr && currentPathElement->position != toPos2)
	{
		if (0 < currentPathElement->possibleMovement.size())
		{
			Position movement;
			movement = tmpPath->GetBestNextStep(sokoMap, toPos2);
			state->pathToOneCrateFreeSide.push_back(movement);
			tmpPath->ApplyBestStep(sokoMap, movement);
			tmpPath->CreateNewPathElementPlayer(currentPathElement, sokoMap);
			tmpPath = tmpPath->nextStepOfPath;
			currentPathElement = tmpPath;
		}
		else
		{
			Path* pathElementDelete;
			pathElementDelete = currentPathElement;
			tmpPath = pathElementDelete->previousStepOfPath;
			currentPathElement = pathElementDelete->previousStepOfPath;
			if (currentPathElement != nullptr)
			{
				sokoMap.SetCharAtPosTo(pathElementDelete->position, 'x');
				sokoMap.SetCharAtPosTo(currentPathElement->position, '@');
			}
			delete pathElementDelete;
			if (state->pathToOneCrateFreeSide.size())
			{
				state->pathToOneCrateFreeSide.pop_back();
			}
		}		
	}

	if (tmpPath != nullptr)
	{
		for (tmpPath; tmpPath != nullptr;)
		{
			Path* pathDelete;
			pathDelete = tmpPath;
			tmpPath = tmpPath->previousStepOfPath;
			delete pathDelete;
		}
	}
};

// Tries to find a path from the crate point of view
void FindPathCrate(SokoMap sokoMap,State* state, Crate fromCrate, Position toPos2) {
	Path* HEAD;
	Path* currentPathElement;
	Path* tmpPath;

	currentPathElement = new Path();
	currentPathElement->firstStepOfPath = currentPathElement;
	sokoMap.SetToTemplateMap();
	sokoMap.SetToMatchCurrentState(state);
	currentPathElement->position = fromCrate.cratePosition;
	state->playerAtNonPushedCrate = fromCrate.cratePosition;
	currentPathElement->MovementVectorCopy(fromCrate.possibleMovement);
	state->cratePushToNextPosition.clear();
	HEAD = currentPathElement;
	tmpPath = currentPathElement;


	while (tmpPath != nullptr && currentPathElement->position != toPos2)
	{
		if (0 < currentPathElement->possibleMovement.size())
		{
			Position movement;			
			movement = tmpPath->GetBestNextStep(sokoMap, toPos2);
			state->cratePushToNextPosition.push_back(movement);
			tmpPath->ApplyBestStep(sokoMap, movement);
			tmpPath->CreateNewPathElementCrate(currentPathElement, sokoMap);
			tmpPath = tmpPath->nextStepOfPath;
			currentPathElement = tmpPath;
		}
		else
		{
			Path* pathElementDelete;
			pathElementDelete = currentPathElement;
			tmpPath = pathElementDelete->previousStepOfPath;
			currentPathElement = pathElementDelete->previousStepOfPath;
			if (currentPathElement != nullptr)
			{
				sokoMap.SetCharAtPosTo(currentPathElement->position, '$');
				sokoMap.SetCharAtPosTo(pathElementDelete->position, 'x');
			}
			if (state->cratePushToNextPosition.size())
			{
				state->cratePushToNextPosition.pop_back();
			}
			delete pathElementDelete;
		}
	}
	if (tmpPath != nullptr)
	{
		state->playerAtNonPushedCrate -= tmpPath->firstStepOfPath->latestUsedMovement;
		for (short i = 0; i < state->cratePushToNextPosition.size(); i++)
		{
			if (state->cratePushToNextPosition[i] != state->cratePushToNextPosition[0]) {
				state->cratePushToNextPosition.erase(state->cratePushToNextPosition.begin() + i, state->cratePushToNextPosition.end());
				break;
			}
		}
		
		for (tmpPath; tmpPath != nullptr;)
		{
			Path* pathDelete;
			pathDelete = tmpPath;
			tmpPath = tmpPath->previousStepOfPath;
			delete pathDelete;
		}
	}
};
