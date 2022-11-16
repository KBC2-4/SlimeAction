#include "GameMain.h"
#include "Title.h"
#include <vector>

GAMEMAIN::GAMEMAIN(bool restert)
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
	selectmenu = 0;
	time = GetNowCount();
	if(restart == false)halfway_time = 0;
	lemoner_count = 0;
	tomaton_count = 0;

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

	element = new ELEMENT();

	this->restart = restert;

	if (restart == true) {
		int scrollx = -(stage->GetHalfwayPoint(0) - 500);
		player->SetPlayerX(500); //�v���C���[�̉�ʓ����W���Z�b�g
		stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
	}

	pause_flg = false;
}

GAMEMAIN::~GAMEMAIN()
{
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
	
	delete element;
}

AbstractScene* GAMEMAIN::Update()
{
	//START�{�^���Ń|�[�Y
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) { pause_flg = !pause_flg; }

	if (pause_flg == false) {
		player->Update(element, stage);
		stage->Update(player);	//�X�e�[�W�N���A�p
		element->Update(player);
		for (int i = 0; i < lemoner_count; i++)
		{
			if (lemoner[i] != nullptr)
			{
				lemoner[i]->Update();
				if (lemoner[i]->GetDeleteFlag())
				{
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

		//�Q�[���I�[�o�[
		if (player->IsDeath()) {
			if (restart == false && stage->HalfwayPoint(player) == true) { return new GAMEMAIN(true); halfway_time = GetNowCount() - time; }
			return new RESULT(false);
		}

		//�X�e�[�W�N���A
		if (stage->GetClearFlg()) { return new RESULT(true, time + halfway_time); };
	}
	else {	//�|�[�Y��ʂ̃Z���N�^�[
		static int input_margin;
		input_margin++;
		if (PAD_INPUT::GetPadThumbLY() > 1000 && input_margin > 20) { selectmenu = (selectmenu + 2) % 3;  input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }
		if (PAD_INPUT::GetPadThumbLY() < -1000 && input_margin > 20) { selectmenu = (selectmenu + 1) % 3; input_margin = 0; PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE); StartJoypadVibration(DX_INPUT_PAD1, 100, 160, -1); }

		if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) {
			if (selectmenu == 0) { pause_flg = !pause_flg; }
			else if (selectmenu == 1) { pause_flg = !pause_flg; return new Title(); }
		}
	}
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

	if (pause_flg == true) { //�|�[�Y��� �`��
		SaveDrawScreen(0, 0, 1280, 720, "Resource/Images/Stage/BackImpause_cash.bmp");
		int drawgraph = LoadGraph("Resource/Images/Stage/BackImpause_cash.bmp");
		GraphFilter(drawgraph,DX_GRAPH_FILTER_GAUSS, 16, 1000);
		DrawGraph(0, 0, drawgraph, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawFillBox(0, 0, 1280, 720,0x000000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		DrawStringToHandle(380, 100, "�|�[�Y", 0x56F590, title_font, 0xFFFFFF);
		//�I�����j���[
		DrawStringToHandle(400, 360, "�Q�[���֖߂�", selectmenu == 0 ? 0xB3E0F5 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(362, 450, "�^�C�g���֖߂�", selectmenu == 1 ? 0xF5E6B3 : 0xEB8F63, menu_font, 0xFFFFFF);
		DrawStringToHandle(560, 540, "�I��", selectmenu == 2 ? 0xEBABDC : 0xEB8F63, menu_font, 0xFFFFFF);
	}
	else{  }

	//�f�o�b�O
	//DrawFormatString(200, 300, 0xffffff, "GetPlayerY:%f", player->GetPlayerY());
}