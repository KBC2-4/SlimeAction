#pragma once

#include <vector>
#define BULLETRADIUS 5

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
	void Update();
	void Draw() const;

	bool HitBullet(int x, int y, int radius);	//エネミー中心座標とその半径渡してね

	int HitBlock();
	float GetThrowX() { return throw_x[0]; }
	float GetThrowY() { return throw_y[0]; }
};

