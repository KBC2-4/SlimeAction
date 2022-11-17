#pragma once
#include<math.h>
#include"DxLib.h"
#include"STAGE.h"
#include"PLAYER.h"
#define _BALL_RADIUS 20

class ITEMBALL
{
private:
	int map_x, map_y;
	float item_x, item_y;
	int item;
	bool delete_flg;
	PLAYER* player;
	STAGE* stage;
	float scrool_x;
	int test1, test2, test3, test4;
	int test5, test6, test7, test8;

public:
	ITEMBALL();
	ITEMBALL(float, float,int,int, PLAYER*,STAGE* ,float);
	~ITEMBALL();

	void Draw()const;
	void Update();
	void PlayerHit();
	float GetDrawX() const;
	bool GetDeleteFlag() { return delete_flg; }
	float GetItemX() { return item_x; }
};

