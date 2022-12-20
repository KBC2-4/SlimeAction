#pragma once

#define BULLETRADIUS 5

#include "STAGE.h"
class TOMATO;

class ThrowSlime
{
private:
	int image;
	bool throw_del;

	float ve = 110.0f;
	float dt = 0.15f;
	float g = 9.8f;

	float vx0;
	float vy0;

	float x0;
	float y0;

	float vx;
	float vy;

	float time;

	float maxY;
public:
	ThrowSlime() {}
	ThrowSlime(float player_x, float player_y, float throw_rad, STAGE* stage);
	void Finalize();
	void Update(STAGE* stage, ELEMENT* element, TOMATO** tomaton, int tomaton_count);
	void Draw(STAGE* stage) const;


	bool checkdel() { return throw_del; }
	void Hit(STAGE* stage, ELEMENT* element, TOMATO** tomaton, int tomaton_count);

	float GetThrowX() { return x0; }
	float GetThrowY() { return y0; }
};

