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
	/*bool throw_fall;*/
	bool throw_del;
	float throw_bottom;

	int move_type;
	float move_x, move_y;

public:
	ThrowSlime() {};
	ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y, STAGE* stage);
	void Update(STAGE* stage);
	void Draw(STAGE* stage) const;


	bool checkdel() { return throw_del; }
	bool Get_throwend() { return throw_end; }
	/*bool Get_throwfall() { return throw_fall; }*/
	int HitBlock(STAGE* stage);

	/*int HitBlock(STAGE* stage);
master*/
	float GetThrowX() { return throw_x[0]; }
	float GetThrowY() { return throw_y[0]; }
};

