
#include "crate.h"

// If 2 opposite sides of a crate are free
// (non-wall -> #, non-crate -> $, and non-pathelement -> x) then,
// these 2 sides are added as free sides
// 
// Further filters will be applied later
// 
// Note to the "non-pathelement". 
// During path finding the used fields of the map are set to X. 
// Including this X here helps to exclude reduundancy for comparison,
// so no extra comparison method necessary for the path finding algorithm
void Crate::GetPushableSides(SokoMap sokoMap)
{
	FreeSideQuality tmpFreeSideQuality;
	if (sokoMap.sokobanMap[this->cratePosition.x - 1][this->cratePosition.y] != '#'
		&& sokoMap.sokobanMap[this->cratePosition.x - 1][this->cratePosition.y] != '$'
		&& sokoMap.sokobanMap[this->cratePosition.x - 1][this->cratePosition.y] != 'x'
		&& sokoMap.sokobanMap[this->cratePosition.x + 1][this->cratePosition.y] != '#'
		&& sokoMap.sokobanMap[this->cratePosition.x + 1][this->cratePosition.y] != '$'
		&& sokoMap.sokobanMap[this->cratePosition.x + 1][this->cratePosition.y] != 'x')
	{
		tmpFreeSideQuality.freeSidePos = this->cratePosition;
		tmpFreeSideQuality.freeSidePos.x -= 1;
		this->freeSides.push_back(tmpFreeSideQuality);
		tmpFreeSideQuality.freeSidePos = this->cratePosition;
		tmpFreeSideQuality.freeSidePos.x += 1;
		this->freeSides.push_back(tmpFreeSideQuality);
		Position movement;
		movement.SetPos(1, 0);
		this->possibleMovement.push_back(movement);
		movement.SetPos(-1, 0);
		this->possibleMovement.push_back(movement);
	};
	if (sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y - 1] != '#'
		&& sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y - 1] != '$'
		&& sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y - 1] != 'x'
		&& sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y + 1] != '#'
		&& sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y + 1] != '$'
		&& sokoMap.sokobanMap[this->cratePosition.x][this->cratePosition.y + 1] != 'x')
	{
		tmpFreeSideQuality.freeSidePos = this->cratePosition;
		tmpFreeSideQuality.freeSidePos.y -= 1;
		this->freeSides.push_back(tmpFreeSideQuality);
		tmpFreeSideQuality.freeSidePos = this->cratePosition;
		tmpFreeSideQuality.freeSidePos.y += 1;
		this->freeSides.push_back(tmpFreeSideQuality);
		Position movement;
		movement.SetPos(0, 1);
		this->possibleMovement.push_back(movement);
		movement.SetPos(0, -1);
		this->possibleMovement.push_back(movement);

	};
};

// Return if the given crate is at a target position
bool Crate::IsAtTarget(SokoMap sokoMap) {
	for (short i = 0; i < sokoMap.targetPosition.size(); i++)
	{
		if (this->cratePosition==sokoMap.targetPosition[i])
		{
			return true;
		}
	}
	return false;
};
