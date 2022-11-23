#include "GameMain.h"
#include "Title.h"
#include <vector>

GAMEMAIN::GAMEMAIN(bool restert, int halfway_time, const char* stage_name)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) {
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}
	menu_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	title_font = CreateFontToHandle("UD �f�W�^�� ���ȏ��� N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	time = GetNowCount();
	this->halfway_time = halfway_time;
	lemoner_count = 0;
	tomaton_count = 0;
	item_count = 0;
	item_num = 0;
	item_rand = 0;

	player = new PLAYER;
	stage = new STAGE(stage_name);
	pause = new PAUSE;
	lemoner = nullptr;
	gurepon = nullptr;
	tomaton = nullptr;

	//�Ƃ܃g���������鐔�𐔂���
	for (int i = 0, point = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			if (stage->GetMapData(i, j) == 93)
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
		tomaton = new TOMATO * [tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//�X�|�[���|�C���g���폜
	spawn_point.clear();

	//�O���|���𐶐����鐔�𐔂���
	for (int i = 0, point = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			if (stage->GetMapData(i, j) == 92)
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
	for (int i = 0, point = 0; i < stage->GetMapSize().x; i++)
	{
		for (int j = 0; j < stage->GetMapSize().y; j++)
		{
			if (stage->GetMapData(i, j) == 91)
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

	this->restart = restert;

	if (restart == true) {
		int scrollx = -(stage->GetHalfwayPoint().x - 500);
		stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
		player->SetPlayerX(500); //�v���C���[�̉�ʓ����W���Z�b�g
	}
}

GAMEMAIN::~GAMEMAIN()
{
	DeleteGraph(background_image[0]);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
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
	//START�{�^���Ń|�[�Y
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) { pause->SetPause(); }

	if (pause->IsPause() == false) {
		player->Update(element, stage);
		stage->Update(player, element);	//�X�e�[�W�N���A�p
		element->Update(player,stage);
		for (int i = 0; i < lemoner_count; i++)
		{
			if (lemoner[i] != nullptr)
			{
				lemoner[i]->Update();
				if (lemoner[i]->GetDeleteFlag())
				{
					item_rand = GetRand(5);
					//�A�C�e���𐶐�
					if (item_rand == 0)
					{
						item[item_num++] = new ITEMBALL(lemoner[i]->GetX(), lemoner[i]->GetY(), lemoner[i]->GetMapX(), lemoner[i]->GetMapY(), player, stage, stage->GetScrollX());
					}
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
				item_rand = GetRand(5);
				//�A�C�e���𐶐�
				if (item_rand == 0)
				{
					item[item_num++] = new ITEMBALL(gurepon[i]->GetX(), gurepon[i]->GetY(), gurepon[i]->GetSpawnMapX(), gurepon[i]->GetSpawnMapY(), player, stage, stage->GetScrollX());
				}
				delete gurepon[i];
				gurepon[i] = nullptr;
			}
			else if (gurepon[i] != nullptr && !gurepon[i]->GetDeleteFlg())
			{
				gurepon[i]->Update();
			}
			else
			{
			}
		}
		//�A�C�e���̃A�b�v�f�[�g
		for (int i = 0; i < item_count; i++)
		{
			if (item[i] != nullptr)
			{
				if (item[i]->GetDeleteFlag()) 
				{
					delete item[i];
					item[i] = nullptr;
				}
				else 
				{
					if ((item[i]->GetItemX() + stage->GetScrollX()) > 0 && (item[i]->GetItemX() + stage->GetScrollX()) < 1280)
					{
						item[i]->Update();
					}
				}
			}

			

			//�Q�[���I�[�o�[
			if (player->IsDeath()) {
				if (!restart && stage->GetHalfwayPointFlg()) { 
					halfway_time =  time - GetNowCount();
					return new GAMEMAIN(true,halfway_time); 
				}
				return new GameOver();
			}

			//�X�e�[�W�N���A
			if (stage->GetClearFlg()) { 
				return new RESULT(true, time + halfway_time); 
			};
		}
	}
	else {	//�|�[�Y��ʂ̃Z���N�^�[
		pause->Update();
		if (pause->GetSelectMenu() == 2) { return new Title(); }
		else if (pause->GetSelectMenu() == 1) { return new GAMEMAIN(); }
		else if (pause->GetSelectMenu() == 3) { pause->SetPause(); }
	}

	//�f�o�b�O
	if (CheckHitKey(KEY_INPUT_F)) {
		int scrollx = -(7800 - 500);
		stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
		player->SetPlayerX(500); //�v���C���[�̉�ʓ����W���Z�b�g
	}

	return this;
}
void GAMEMAIN::Draw() const
{

	//�X�e�[�W�w�i
	DrawGraph(int(stage->GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(stage->GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//�X�e�[�W�̕`��
	element->Draw();
	stage->Draw();

	//�v���C���[�̕`��
	player->Draw(stage);

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
			if ((item[i]->GetItemX() + stage->GetScrollX()) > 0 && (item[i]->GetItemX() + stage->GetScrollX()) < 1280)
			{
				item[i]->Draw();
			}
		}
	}

	if (pause->IsPause() == true) { //�|�[�Y��ʂ�
		int pause_graph = MakeGraph(1280, 720);
		GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);

		pause->Draw(pause_graph);
	}

	//�f�o�b�O
	//DrawFormatString(100, 200, 0x000000, "X%f", stage->GetScrollX());
}
