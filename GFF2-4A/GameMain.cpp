#include "GameMain.h"
#include <vector>

GAMEMAIN::GAMEMAIN()
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	time = GetNowCount();
	lemoner_count = 0;
	tomaton_count = 0;
	item_count = 0;
	item_num = 0;

	player = new PLAYER;
	stage = new STAGE;
	lemoner = nullptr;
	gurepon = nullptr;
	tomaton = nullptr;

	//�Ƃ܃g���������鐔�𐔂���
	for (int i = 0,point = 0 ; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 93)
			{
				tomaton_count++;
				item_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}
	//�Ƃ܃g���̐���
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO*[tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player,stage, spawn_point[i][0],spawn_point[i][1]);
		}
	}

	//�X�|�[���|�C���g���폜
	spawn_point.clear();

	//�O���|���𐶐����鐔�𐔂���
	for (int i = 0, point = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 92)
			{
				gurepon_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}

	//�O���|���̐���
	if (gurepon_count > 0)
	{
		gurepon = new GRAPEFRUIT * [gurepon_count];
		for (int i = 0; i < gurepon_count; i++)
		{
			gurepon[i] = new GRAPEFRUIT(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//�X�|�[���|�C���g���폜
	spawn_point.clear();

	//�����i�[�������鐔�𐔂���
	for (int i = 0, point = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (stage->GetMapDat(i, j) == 91)
			{
				lemoner_count++;
				spawn_point.push_back(std::vector<int>(2));
				spawn_point[point][0] = i;
				spawn_point[point][1] = j;
				point++;
			}
		}
	}
	//�����i�[�̐���
	if (lemoner_count > 0)
	{
		lemoner = new LEMON * [lemoner_count];
		for (int i = 0; i < lemoner_count; i++)
		{
			lemoner[i] = new LEMON(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//�A�C�e���̃J�E���g������
	item_count = gurepon_count + lemoner_count;
	if (item_count > 0)
	{
		item = new ITEMBALL * [item_count];
		for (int i = 0; i < item_count; i++) {
			item[i] = nullptr;
		}
	}
	element = new ELEMENT();
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;

	//�����i�[�̍폜
	for (int i = 0; i < lemoner_count; i++) {
		delete lemoner[i];
	}
	delete[] lemoner;

	//�Ƃ܃g���̍폜
	for (int i = 0; i < tomaton_count; i++)
	{
		delete tomaton[i];
	}
	delete[] tomaton;
	//�O���|���̍폜
	for (int i = 0; i < gurepon_count; i++) {
			delete gurepon[i];
		
	}
	delete[] gurepon;

	for (int i = 0; i < item_count; i++) 
	{
		if (item[i] != nullptr) 
		{
			delete item[i];
		}
	}
	
	delete[] item;
	delete element;
}

AbstractScene* GAMEMAIN::Update()
{
	player->Update(element,stage);
	
	element->Update(player);
	for (int i = 0; i < lemoner_count; i++)
	{
		if (lemoner[i] != nullptr)
		{
			lemoner[i]->Update();
			if (lemoner[i]->GetDeleteFlag())
			{
				//�A�C�e���𐶐�
				item[item_num++] = new ITEMBALL(lemoner[i]->GetX(),lemoner[i]->GetY(),lemoner[i]->GetMapX(),lemoner[i]->GetMapY(),player,stage);
				delete lemoner[i];
				lemoner[i] = nullptr;
			}
		}
	}
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Update();
	}
	for (int i = 0; i < gurepon_count; i++)
	{
		if (gurepon[i] != nullptr && gurepon[i]->GetDeleteFlg())
		{
			//�A�C�e���𐶐�
			item[item_num++] = new ITEMBALL(gurepon[i]->GetX(),gurepon[i]->GetY(),gurepon[i]->GetSpawnMapX(),gurepon[i]->GetSpawnMapY(),player,stage);

			//�O���|�����폜��null����
			delete gurepon[i];
			gurepon[i] = nullptr;
		}
		else if(gurepon[i] != nullptr && !gurepon[i]->GetDeleteFlg())
		{
			gurepon[i]->Update();
		}
		else
		{}
	}
	//�A�C�e���̃A�b�v�f�[�g
	for (int i = 0; i < item_count; i++)
	{
		if (gurepon[i] == nullptr || lemoner[i] == nullptr)
		{
			if (item[i] != nullptr)
			{
				item[i]->Update();
			}
		}
	}

	stage->Update(player);	//�X�e�[�W�N���A�p
	element->Update(player);

	//�Q�[���I�[�o�[
	if (player->IsDeath()) {
		return new RESULT(false);
	}

	//�X�e�[�W�N���A
	if (stage->GetClearFlg()) { return new RESULT(true,time); };

	return this;
}

void GAMEMAIN::Draw() const
{

	//�X�e�[�W�w�i
	DrawGraph(int(STAGE::GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(STAGE::GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw();
	stage->Draw();
	
	//�v���C���[�̕`��
	player->Draw();

	//�����i�[�̕`��
	for (int i = 0; i < lemoner_count; i++)
	{
		if (lemoner[i] != nullptr)
		{
			lemoner[i]->Draw();

		}
	}
	//�Ƃ܃g���̕`��
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Draw();
	}
	//�O���|���̕`��
	for (int i = 0; i < gurepon_count; i++)
	{
		if (gurepon[i] != nullptr && gurepon[i]->GetDeleteFlg() == false)
		{
			gurepon[i]->Draw();
		}
	}

	//�A�C�e���̕`��
	for (int i = 0; i < item_count; i++)
	{
		if (item[i] != nullptr)
		{
			item[i]->Draw();
		}
	}
}