#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = new TOMATO(player);
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
}

AbstractScene* GAMEMAIN::Update()
{
	//�v���C���[�̕\��
	int old_playerx = player->GetPlayerX();
	player->Update();
	stage->Update(player->GetPlayerX() - old_playerx, player->GetPlayerY() - 40);
	tomaton->Updata();
	return this;
}

void GAMEMAIN::Draw() const
{
	//�v���C���[�̕`��
	player->Draw();
	//�Ƃ܂Ƃ�̕`��
	tomaton->Draw();
	//�X�e�[�W�̕`��
	stage->Draw();
}