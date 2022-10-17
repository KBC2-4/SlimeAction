#include "PLAYER.h"
#include"DxLib.h"


/*コンストラクタ*/
PLAYER::PLAYER() {
	player_x = 0;
	player_y = 0;
	map_x = 0;
	map_y = 0;
	life = 5;
	*image = { 0 };
}

void PLAYER::Draw()const {
	DrawBox(map_x, map_y, map_x + 40, map_y + 40, 0xffffff, TRUE);
}

void PLAYER::Move() {

}

void PLAYER::HookMove() {

}

void PLAYER::JumpMove() {

}

void PLAYER::Throw() {

}

void PLAYER::MoveAnimation() {

}

