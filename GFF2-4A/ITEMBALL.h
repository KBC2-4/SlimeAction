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
	float scrool_y;

public:
	ITEMBALL();
	ITEMBALL(float, float,int,int, PLAYER*,STAGE* ,float,float);
	~ITEMBALL();

	void Draw()const;
	void Update();
	void PlayerHit();
	float GetDrawX() const;
	float GetDrawY() const;
	bool GetDeleteFlag() { return delete_flg; }
	float GetItemX() { return item_x; }

};

