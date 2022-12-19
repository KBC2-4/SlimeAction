#include "GameMain.h"
#include "Title.h"
#include <vector>
#include "Option.h"

GAMEMAIN::GAMEMAIN(bool restert, int halfway_time, const char* stage_name)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	hp_img = LoadGraph("Resource/Images/Player/hp.png");

	for (int i = 0; i < 2; i++) {
		char dis_background_image[38];
		sprintf_s(dis_background_image, sizeof(dis_background_image), "Resource/Images/Stage/BackImage%d.png", i + 1);

		if ((background_image[i] = LoadGraph(dis_background_image)) == -1) {
			throw dis_background_image;
		}
	}

	for (int i = 0; i < 3; i++) {
		char dis_stage_bgm[36];
		sprintf_s(dis_stage_bgm, sizeof(dis_stage_bgm), "Resource/Sounds/BGM/stage%d.wav", i + 1);

		if ((background_music[i] = LoadSoundMem(dis_stage_bgm)) == -1) {
			throw dis_stage_bgm;
		}
	}

	if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.wav")) == -1) {
		throw "Resource/Sounds/SE/cursor_move.wav";
	}

	if ((ok_se = LoadSoundMem("Resource/Sounds/SE/ok.wav")) == -1) {
		throw "Resource/Sounds/SE/ok.wav";
	}
	time_font = LoadFontDataToHandle("Resource/Fonts/TimeAttack_HUD.dft", 2);
	time = GetNowCount();
	this->halfway_time = halfway_time;
	this->stage_name = stage_name;
	elapsed_time = halfway_time;
	lemoner_count = 0;
	tomaton_count = 0;
	item_count = 0;
	item_num = 0;
	item_rand = 0;




	stage = new STAGE(stage_name);
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

	this->restart = restert;

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
	ChangeVolumeSoundMem(Option::GetSEVolume(), cursor_move_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), ok_se);
}

GAMEMAIN::~GAMEMAIN()
{
	DeleteGraph(background_image[0]);
	DeleteGraph(background_image[1]);
	DeleteGraph(hp_img);

	if (stage_name == "Stage01") {
		StopSoundMem(background_music[0]);
	}
	else if (stage_name == "Stage02") {
		StopSoundMem(background_music[1]);
	}
	else if (stage_name == "Stage03") {
		StopSoundMem(background_music[2]);
	}

	for (int i = 0; i < 3; i++) {
		DeleteSoundMem(background_music[i]);
	}

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

	//START�{�^���Ń|�[�Y
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) { pause->SetPause(); }

	if (pause->IsPause() == false) {

		//�o�ߎ��Ԃ̉��Z
		elapsed_time += 1000 / 60;

		player->Update(element, stage);
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
					halfway_time = time - GetNowCount();
					return new GAMEMAIN(true, halfway_time, stage_name);
				}
				return new GameOver(stage_name);
			}

			//�X�e�[�W�N���A
			if (stage->GetClearFlg())
			{
				return new RESULT(true, time + halfway_time, stage_name);
			}
		}
	}
	else {	//�|�[�Y��ʂ̃Z���N�^�[
		pause->Update();
		if (pause->GetSelectMenu() == 3) { return new Title(); }
		else if (pause->GetSelectMenu() == 1) { return new GAMEMAIN(false, 0, stage_name); }
		else if (pause->GetSelectMenu() == 4) { pause->SetPause(); }
		else if (pause->GetSelectMenu() == 2) {
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
	element->Draw(stage);



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

		sprintf_s(dis_clear_time, sizeof(dis_clear_time), "%4d:%2d.%.3d",
			(elapsed_time / 1000) / 60, (elapsed_time / 1000) % 60, elapsed_time % 1000);
	}
	else
	{

		sprintf_s(dis_clear_time, sizeof(dis_clear_time),
			"%5d.%.3d", elapsed_time / 1000, elapsed_time % 1000);
	}

	DrawStringToHandle(1110, 10, dis_clear_time, 0x1aff00, time_font, 0xFFFFFF);


	if (pause->IsPause() == true) { //�|�[�Y��ʂ�
		int pause_graph = MakeGraph(1280, 720);
		GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);

		pause->Draw(pause_graph);
	}

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
}
