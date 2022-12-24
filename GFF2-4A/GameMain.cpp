#include "GameMain.h"
#include "GAMEMAIN_Restart.h"
#include "Title.h"
#include <vector>
#include "Option.h"

GAMEMAIN::GAMEMAIN(bool restart, int halfway_time, const char* stage_name)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	hp_img = LoadGraph("Resource/Images/Player/hp.png");

	//���̔w�i�摜
	if (stage_name != "Stage02") {
		if ((background_image[0] = LoadGraph("Resource/Images/Stage/BackImage1.png")) == -1) {
			throw "Resource/Images/Stage/BackImage1.png";
		}
	}

	if (stage_name == "Stage01") {

		if ((background_image[0] = LoadGraph("Resource/Images/Stage/BackImage1.png")) == -1) {
			throw "Resource/Images/Stage/BackImage1.png";
		}

		if ((background_music[0] = LoadSoundMem("Resource/Sounds/BGM/stage1.wav")) == -1) {
			throw "Resource/Sounds/BGM/stage1.wav";
		}
	}
	else if (stage_name == "Stage02") {

		if ((background_image[1] = LoadGraph("Resource/Images/Stage/BackImage2.png")) == -1) {
			throw "Resource/Images/Stage/BackImage2.png";
		}

		if ((background_music[1] = LoadSoundMem("Resource/Sounds/BGM/stage2.wav")) == -1) {
			throw "Resource/Sounds/BGM/stage2.wav";
		}
	}
	else if (stage_name == "Stage03") {
		if ((background_music[2] = LoadSoundMem("Resource/Sounds/BGM/stage3.wav")) == -1) {
			throw "Resource/Sounds/BGM/stage3.wav";
		}
	}

	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) {
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}

	now_graph = 0;

	start_time_font = CreateFontToHandle("���C���I", 160, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	time_font = LoadFontDataToHandle("Resource/Fonts/TimeAttack_HUD.dft", 2);
	this->stage_name = stage_name;
	elapsed_time = halfway_time;
	lemoner_count = 0;
	tomaton_count = 0;
	item_count = 0;
	item_num = 0;
	item_rand = 0;

	start_time = 180;
	start_effect_timer = 120;

	this->restart = restart;


	stage = new STAGE(stage_name, this->restart);
	player = new PLAYER(stage);
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
	element = new ELEMENT(stage_name);



	if (restart == true) {
		int scrollx = -(stage->GetHalfwayPoint().x - 500);
		stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
		stage->SetScrollY(-(stage->GetHalfwayPoint().y - MAP_CEllSIZE - 400));
		POINT buf = { stage->GetHalfwayPoint().y, stage->GetHalfwayPoint().x };
		player->SetPlayer_Screen(buf);

	}
	else {
		//�X�|�[���n�_���Z�b�g
		stage->SetScrollX(-(stage->GetSpawnPoint().y - MAP_CEllSIZE));
		stage->SetScrollY(-(stage->GetSpawnPoint().x - MAP_CEllSIZE - 400/* - ((stage->GetMapSize().x - 14) * MAP_CEllSIZE))*/));
		//stage->SetScrollY(-((stage->GetMapSize().x - 14) * MAP_CEllSIZE));
		player->SetPlayer_Screen(stage->GetSpawnPoint());
	}

	//BGM
	if (stage_name == "Stage01") {
		PlaySoundMem(background_music[0], DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[0]);
	}
	else if (stage_name == "Stage02") {
		PlaySoundMem(background_music[1], DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[1]);
	}
	else if (stage_name == "Stage03") {
		PlaySoundMem(background_music[2], DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[2]);
	}

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.5, cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume() * 1.5, ok_se);


	//PV����p�i�������摦���ɏ����j
	input_margin = 0;
	scroll_speed = 4;
	player_visible = true;
	
}

GAMEMAIN::~GAMEMAIN()
{
	DeleteGraph(hp_img);

	//���̔w�i�摜
	if (stage_name != "Stage02") {
		DeleteGraph(background_image[0]);
	}

	if (stage_name == "Stage01") {
		StopSoundMem(background_music[0]);
		DeleteSoundMem(background_music[0]);
		DeleteGraph(background_image[0]);
	}
	else if (stage_name == "Stage02") {
		StopSoundMem(background_music[1]);
		DeleteSoundMem(background_music[1]);
		DeleteGraph(background_image[1]);
	}
	else if (stage_name == "Stage03") {
		StopSoundMem(background_music[2]);
		DeleteSoundMem(background_music[2]);
	}

	DeleteFontToHandle(start_time_font);
	DeleteFontToHandle(time_font);

	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	delete player;
	delete stage;
	delete pause;
	delete element;

	//�����i�[�̍폜
	for (int i = 0; i < lemoner_count; i++)
	{
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
}

AbstractScene* GAMEMAIN::Update()
{

	if (start_time > 0) {

		//�J�E���g���Đ�
		if (start_time % 60 == 0) {
			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
		}

		start_time--;

		char dis_start_time[2];	//�����񍇐��o�b�t�@�[

		sprintf_s(dis_start_time, sizeof(dis_start_time), "%d", start_time / 60);

		//�v���C���[��X���W�̓������~�߂�
		int player_x = player->GetPlayerX();
		player->Update(element, stage, tomaton, tomaton_count);
		player->SetPlayerX(player_x);

		//START���Đ�
		if (start_time == 0) {
			PlaySoundMem(ok_se, DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else if (start_effect_timer > 0) {

		start_effect_timer--;
	}


	if (start_time <= 0) {

		pause->Update();

		if (pause->IsPause() == false) {

			//�o�ߎ��Ԃ̉��Z
			elapsed_time += 1000 / 60;

			player->Update(element, stage, tomaton, tomaton_count);
			stage->Update(player, element);	//�X�e�[�W�N���A�p
			element->Update(player, stage);
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
							item[item_num++] = new ITEMBALL(lemoner[i]->GetX(), lemoner[i]->GetY(), lemoner[i]->GetMapX(), lemoner[i]->GetMapY(), player, stage, stage->GetScrollX(), stage->GetScrollY());
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
						item[item_num++] = new ITEMBALL(gurepon[i]->GetX(), gurepon[i]->GetY(), gurepon[i]->GetSpawnMapX(), gurepon[i]->GetSpawnMapY(), player, stage, stage->GetScrollX(), stage->GetScrollY());
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
						now_graph = MakeGraph(1280, 720);
						GetDrawScreenGraph(0, 0, 1280, 720, now_graph);
						return new GAMEMAIN_RESTART(true, elapsed_time, stage_name,now_graph);
					}
					return new GameOver(stage_name);
				}

				//�X�e�[�W�N���A
				if (stage->GetClearFlg())
				{
					return new RESULT(true, elapsed_time, stage_name);
				}
			}
		}
		else {	//�|�[�Y��ʂ̃Z���N�^�[

			if (static_cast<PAUSE::MENU>(pause->GetSelectMenu()) == PAUSE::MENU::TITLE) { return new Title(); }
			else if (static_cast<PAUSE::MENU>(pause->GetSelectMenu()) == PAUSE::MENU::RESTART) {
				now_graph = MakeGraph(1280, 720);
				GetDrawScreenGraph(0, 0, 1280, 720, now_graph);
				return new GAMEMAIN_RESTART(false, 0, stage_name,now_graph); 
			}
			else if (static_cast<PAUSE::MENU>(pause->GetSelectMenu()) == PAUSE::MENU::OPTION) {
				//BGM
				if (stage_name == "Stage01") {
					ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[0]);
				}
				else if (stage_name == "Stage02") {
					ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[1]);
				}
				else if (stage_name == "Stage03") {
					ChangeVolumeSoundMem(Option::GetBGMVolume(), background_music[2]);
				}

				//SE
				ChangeVolumeSoundMem(Option::GetSEVolume(), cursor_move_se);
				ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);
			}
		}

		//�f�o�b�O
		if (CheckHitKey(KEY_INPUT_F)) {
			int scrollx = -(7800 - 500);
			stage->SetScrollX(scrollx);	//�X�|�[���n�_���Z�b�g
			player->SetPlayerX(500); //�v���C���[�̉�ʓ����W���Z�b�g
		}
	}

	if (input_margin < 10) {
		input_margin++;
	}
	else {


		//PV����p�i�������摦���ɏ����j

		//�v���C���[�\���E��\��
		if (CheckHitKey(KEY_INPUT_N)) {
			player_visible = !player_visible;

			if (player_visible) {
				player->SetVisible(true);
			}
			else {
				player->SetVisible(false);
			}
		}

		//�X�N���[���X�s�[�h�_�E��
		else if (CheckHitKey(KEY_INPUT_M)) {
			if (scroll_speed > 0) { scroll_speed--; }
		}

		//�X�N���[���X�s�[�h�A�b�v
		else if (CheckHitKey(KEY_INPUT_L)) {
			scroll_speed++;
		}
		input_margin = 0;
	}

	//�X�N���[���ړ�
	if (CheckHitKey(KEY_INPUT_UP)) {
		stage->SetScrollY(stage->GetScrollY() + scroll_speed);
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		stage->SetScrollY(stage->GetScrollY() - scroll_speed);
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		stage->SetScrollX(stage->GetScrollX() + scroll_speed * 3);
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (stage->GetScrollX() > 0 || stage->GetScrollX() <= -(80 * static_cast<int>(stage->GetMapSize().x - 1280))) {
			stage->SetScrollX(stage->GetScrollX() - scroll_speed * 3);
		}
	}


	return this;
}

void GAMEMAIN::Draw() const
{

	//�X�e�[�W�w�i
	if (stage_name != "Stage02") {
		DrawGraph(int(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[0], FALSE);
		DrawGraph(int(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[0], FALSE);
	}
	else if (stage_name == "Stage02") {
		DrawGraph(int(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[1], FALSE);
		DrawGraph(int(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[1], FALSE);
	}


	//�n���w�i�`��
	if (stage_name == "Stage01") {
		//�X�e�[�W�P
		DrawBox(stage->GetScrollX() + 6880, stage->GetScrollY() + 1380, stage->GetScrollX() + 10640, stage->GetScrollY() + 1900, 0x20251F, TRUE);
	}
	else if (stage_name == "Stage03") {
		//�X�e�[�W3
		DrawBox(0, stage->GetScrollY() + 1380, stage->GetScrollX() + 5120, stage->GetScrollY() + 4800, 0x20251F, TRUE);
	}

	/*if (stage_name == "Stage03" && stage->GetScrollY() < -960) {
		DrawBox(0, 0, 25600, 1280, 0x20251F, TRUE);
	}*/

	for (int i = 0; i < player->GetLife(); i++) {
		DrawRotaGraph(30 + 50 * i, 20, 1, 0, hp_img, TRUE);
	}

	//�X�e�[�W�̕`��
	stage->Draw(element);
	element->Draw(stage, player);



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

	//HUD

	//�v���C���[�̃��C�t�̕`��
	for (int i = 0; i < player->GetLife(); i++) {
		DrawRotaGraph(30 + 50 * i, 20, 1, 0, hp_img, TRUE);
	}

	//�o�ߎ��Ԃ̕`��
	char dis_clear_time[20];	//�����񍇐��o�b�t�@�[

	//�����񍇐�
	if (elapsed_time / 1000 >= 60)
	{

		sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%02d.%.3d",
			(elapsed_time / 1000) / 60, (elapsed_time / 1000) % 60, elapsed_time % 1000);
	}
	else
	{

		sprintf_s(dis_clear_time, sizeof(dis_clear_time),
			"%5d.%.3d", elapsed_time / 1000, elapsed_time % 1000);
	}

	int str_width = GetDrawFormatStringWidthToHandle(time_font, dis_clear_time);

	DrawStringToHandle(1260 - str_width, 10, dis_clear_time, 0x1aff00, time_font, 0xFFFFFF);


	//�f�o�b�O
	if (CheckHitKey(KEY_INPUT_A)) {
		DrawFormatString(100, 150, 0xF77D0A, "ScrollX:%f", stage->GetScrollX());
		DrawFormatString(100, 200, 0xF77D0A, "ScrollY:%f", stage->GetScrollY());
		DrawFormatString(100, 250, 0xE04D02, "MapData:%d", stage->GetMapData((player->GetPlayerY() / MAP_CEllSIZE) + 1, player->GetPlayerX() / MAP_CEllSIZE));
		DrawFormatString(100, 300, 0x02F896, "PlayerX%f", player->GetPlayerX());
		DrawFormatString(100, 350, 0x02F896, "PlayerY%f", player->GetPlayerY());
		DrawFormatString(100, 400, 0x02F896, "SpawnPointY:%d", stage->GetSpawnPoint().y);
		DrawFormatString(100, 450, 0x02F896, "Jump:%f", player->GetJumpVelocity());
	}

	if (start_time > 0) {

		char dis_start_time[2];	//�����񍇐��o�b�t�@�[

		sprintf_s(dis_start_time, sizeof(dis_start_time), "%d", start_time / 60 + 1);

		DrawStringToHandle(GetDrawCenterX(dis_start_time, start_time_font), 300, dis_start_time, 0xEBA05E, start_time_font, 0xFFFFFF);
	}
	else if (start_effect_timer > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0 + start_effect_timer * 3 - 5 % 255);

		if (restart == false) {
			DrawStringToHandle(GetDrawCenterX("START", start_time_font), 300, "START", 0xF5E03D, start_time_font, 0xFFFFFF);
		}
		else {
			DrawStringToHandle(GetDrawCenterX("RESTART", start_time_font), 300, "RESTART", 0xE66500, start_time_font, 0xFFFFFF);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}



	//��ɍőO��
	if (pause->IsPause() == true) { //�|�[�Y��ʂ�

		pause->Draw();
	}
}
