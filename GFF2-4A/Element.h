#pragma once
#include "STAGE.h"
#include <vector>

class Element :
    public STAGE
{
public:
	struct ELEMENT_DATA
	{
		float x, y;
	};
private:
	std::vector<ELEMENT_DATA> hook;
	ELEMENT_DATA button;
	ELEMENT_DATA door;
	ELEMENT_DATA lift;
	ELEMENT_DATA tunnel;

public:
	Element();
	std::vector<ELEMENT_DATA> GetHookPos() { return hook; }
};

