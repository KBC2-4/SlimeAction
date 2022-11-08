#pragma once

#include <vector>

class ThrowSlime
{
private:
	int image;
	int throw_index;
	int throw_cnt;
	bool throw_end;
	std::vector<float>throw_x;
	std::vector<float>throw_y;

public:
	ThrowSlime(std::vector<float>_throw_x, std::vector<float>_throw_y);
	void Update();
	void Draw() const;

};

