#include "sokoMap.h"


void SokoMap::GatherTargetPositions() {
	for (unsigned short i = 0; i < this->row; i++)
	{
		for (unsigned short j = 0; j < this->column; j++)
		{
			if (this->sokobanMap[i][j] == '.' || this->sokobanMap[i][j] == '+' || this->sokobanMap[i][j] == '*' )
			{
				Position tmpPos;
				tmpPos.SetPos(i, j);
				this->targetPosition.push_back(tmpPos);
			}
		}
	}
}

// template map contains only walls and target positions
void SokoMap::SetToTemplateMap() {
	for (unsigned short i = 0; i < this->row; i++)
	{
		for (unsigned short j = 0; j < this->column; j++)
		{
			if (this->sokobanMap[i][j]!='#')
			{
				this->sokobanMap[i][j] =' ';
			}
		}
	}
	for (unsigned short i = 0; i < this->targetPosition.size(); i++)
	{
		this->sokobanMap[this->targetPosition[i].x][this->targetPosition[i].y] = '.';
	}
};

void SokoMap::SetToMatchCurrentState(State* state) {
	this->SetToTemplateMap();
	for (unsigned short i = 0; i < state->crate.size(); i++)
	{
		Position tmpPos = state->crate[i].cratePosition;
		this->sokobanMap[tmpPos.x][tmpPos.y] = '$';
	}
	this->sokobanMap[state->playerInitial.x][state->playerInitial.y] = '@';
};

void SokoMap::WriteOutMap() {
	std::cout << "\n";
	for (unsigned short i = 0; i < this->row; i++)
	{
		for (unsigned short j = 0; j < this->column; j++)
		{
			std::cout << this->sokobanMap[i][j]<<" ";
		}
		std::cout << "\n";
	}
};

// On the sokomap change the character to a given one at the given position
void SokoMap::SetCharAtPosTo(Position pos, char toChar) {
	this->sokobanMap[pos.x][pos.y] = toChar;
}

// Return if the giveb position is match a crate position
bool SokoMap::IsOccupied(State* state, Position targetPos) {

	for (short j = 0; j < state->crate.size(); j++)
	{
		if (targetPos == state->crate[j].cratePosition)
		{
			return true;
		}
	}
	return false;
};