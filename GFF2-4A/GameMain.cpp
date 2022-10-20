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
	stage->Update();
	player->Update();
	

	return this;
}

void GAMEMAIN::Draw() const
{
	//�X�e�[�W�̕`��
	stage->Draw();
	//�v���C���[�̕`��
	player->Draw();
	
}