#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	//�Ƃ܂Ƃ�̐����ꏊ�̐��p�̕ϐ�
	int spawn_tomaton_count = 0;
	player = new PLAYER;
	stage = new STAGE;
	lemonner = new LEMON(player);
	gurepon = new GRAPEFRUIT(player);
	tomaton = nullptr;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 93)
			{
				spawn_tomaton_count++;
			}
		}
	}
	if (spawn_tomaton_count > 0)
	{
		tomaton = new TOMATO[spawn_tomaton_count];
	}
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;
	delete tomaton;
}

AbstractScene* GAMEMAIN::Update()
{
	stage->Update();
	player->Update(element);
	tomaton->Update();
	return this;
}

void GAMEMAIN::Draw() const
{
	//�X�e�[�W�̕`��
	stage->Draw();
	//�v���C���[�̕`��
	player->Draw();
	//�Ƃ܂Ƃ�̕`��
	tomaton->Draw();
}