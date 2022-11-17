#pragma once
#include<math.h>
#include"DxLib.h"

class ITEMBALL
{
private:
	float item_x, item_y;
	int item;

public:
	ITEMBALL();
	ITEMBALL(float, float);
	~ITEMBALL();

	void Draw()const;
	void Update();
	void PlayerHit();
};

