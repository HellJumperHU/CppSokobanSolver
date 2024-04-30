//#pragma once
#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
	short x;
	short y;

	Position operator+(Position pos);
	Position& operator+=(Position pos);
	Position operator-(Position pos);
	Position& operator-=(Position pos);
	void SetPos( short xPos,  short yPos);
	void SetPos(Position pos);
	Position& operator=(Position tmpPos);
	bool operator==(Position tmpPos);
	bool operator!=(Position tmpPos);

private:

};


#endif // !POSITION_H

