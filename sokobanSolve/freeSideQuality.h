//#pragma once
#ifndef FREESIDEQUALITY_H
#define FREESIDEQUALITY_H

#include "position.h"

class FreeSideQuality
{
public:
	friend class Crate;
	Position freeSidePos;
	short quality = -2;

private:

};


#endif // !FREESIDEQUALITY_H
