#pragma once
#include "Enemy.h"
class SPLASH
{
private:
	int x, y;	//���W
	int w, h;	//���A����
	int image;

	ENEMY* enemy;
public:

	virtual void Draw()const;
	virtual void Move();
};

