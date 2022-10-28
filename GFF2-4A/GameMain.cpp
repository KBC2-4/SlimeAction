#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = new TOMATO(player);
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
	delete element;
}

AbstractScene* GAMEMAIN::Update()
{
	element->Update(player);
	player->Update(element);
	if (player->IsDeath()) {
		return new GAMEMAIN();
	}

	return this;
}

void GAMEMAIN::Draw() const
{
	//�X�e�[�W�̕`��
	stage->Draw();
	//�v���C���[�̕`��
	player->Draw();

	element->Draw();
	
}