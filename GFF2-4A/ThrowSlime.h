#pragma once

#include <vector>

#define BULLETRADIUS 5

#include "STAGE.h"


class ThrowSlime
{
private:
	int image;
	int throw_index;
	int throw_cnt;
	bool throw_end;
	std::vector<float>throw_x;
	std::vector<float>throw_y;
	bool throw_fall;
	float throw_bottom;
public:
	ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y);
	void Update(STAGE* stage);
	void Draw() const;



	bool Get_throwend() { return throw_end; }
	bool Get_throwfall() { return throw_fall; }
	int HitBlock(STAGE* stage);

	/*int HitBlock(STAGE* stage);
master*/
	float GetThrowX() { return throw_x[0]; }
	float GetThrowY() { return throw_y[0]; }
};

