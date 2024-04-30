#include "position.h"

Position Position::operator+(Position pos) {
	Position tmpPos;
	tmpPos.x = this->x + pos.x;
	tmpPos.y = this->y + pos.y;
	return tmpPos;
}

Position& Position::operator+=(Position pos) {
	Position tmpPos;
	this->x += pos.x;
	this->y += pos.y;
	return *this;
}


Position Position::operator-(Position pos) {
	Position tmpPos;
	tmpPos.x = this->x - pos.x;
	tmpPos.y = this->y - pos.y;
	return tmpPos;
}

Position& Position::operator-=(Position pos) {
	Position tmpPos;
	this->x -= pos.x;
	this->y -= pos.y;
	return *this;
}

void Position::SetPos( short xPos,  short yPos) {
	this->x = xPos;
	this->y = yPos;
};

void Position::SetPos(Position pos) {
	this->x = pos.x;
	this->y = pos.y;
}

Position& Position::operator=(Position tmpPos) {
	this->x = tmpPos.x;
	this->y = tmpPos.y;
	return *this;
};

bool Position::operator==(Position tmpPos) {
	return (this->x == tmpPos.x && this->y == tmpPos.y);
};

bool Position::operator!=(Position tmpPos) {
	return !(this->x == tmpPos.x && this->y == tmpPos.y);
};