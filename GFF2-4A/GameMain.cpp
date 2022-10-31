#include "GameMain.h"


GAMEMAIN::GAMEMAIN()
{
	tomaton_count = 0;
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
				tomaton_count++;
			}
		}
	}
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO*[tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player);
		}

	}
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;

	//�Ƃ܂Ƃ�̍폜
	for (int i = 0; i < tomaton_count; i++)
	{
		delete tomaton[i];
	}
	delete[] tomaton;
}

AbstractScene* GAMEMAIN::Update()
{
	stage->Update();
	player->Update(element);
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Update();
	}
	
	return this;
}

void GAMEMAIN::Draw() const
{
	//�X�e�[�W�̕`��
	stage->Draw();
	//�v���C���[�̕`��
	player->Draw();
	//�Ƃ܂Ƃ�̕`��
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Draw();
	}
	
}