#pragma once
#include "Enemy.h"
class SPLASH
{
private:
	int x, y;	//À•W
	int w, h;	//•A‚‚³
	int image;

	ENEMY* enemy;
public:

	virtual void Draw()const;
	virtual void Move();
};

