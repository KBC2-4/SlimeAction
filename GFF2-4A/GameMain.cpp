#include "GameMain.h"
#include "Title.h"
#include <vector>
#include "Option.h"

GAMEMAIN::GAMEMAIN(bool restert, int halfway_time, const char* stage_name)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	hp_img = LoadGraph("Resource/Images/Player/hp.png");

	//仮の背景画像
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


	//とまトン生成する数を数える
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
	//とまトンの生成
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO * [tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//スポーンポイントを削除
	spawn_point.clear();

	//グレポンを生成する数を数える
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

	//グレポンの生成
	if (gurepon_count > 0)
	{
		gurepon = new GRAPEFRUIT * [gurepon_count];
		for (int i = 0; i < gurepon_count; i++)
		{
			gurepon[i] = new GRAPEFRUIT(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//スポーンポイントを削除
	spawn_point.clear();

	//レモナー生成する数を数える
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
	//レモナーの生成
	if (lemoner_count > 0)
	{
		lemoner = new LEMON * [lemoner_count];
		for (int i = 0; i < lemoner_count; i++)
		{
			lemoner[i] = new LEMON(player, stage, spawn_point[i][0], spawn_point[i][1]);
		}
	}

	//アイテムのカウント＆生成
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
		stage->SetScrollX(scrollx);	//スポーン地点をセット
		stage->SetScrollY(-(stage->GetHalfwayPoint().y - MAP_CEllSIZE - 400));
		POINT buf = { stage->GetHalfwayPoint().y, stage->GetHalfwayPoint().x };
		player->SetPlayer_Screen(buf);

	}
	else {
		//スポーン地点をセット
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

	DeleteGraph(hp_img);

	//仮の背景画像
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

	DeleteFontToHandle(time_font);
	DeleteSoundMem(cursor_move_se);
	DeleteSoundMem(ok_se);
	delete player;
	delete stage;
	delete pause;
	delete element;

	//レモナーの削除
	for (int i = 0; i < lemoner_count; i++)
	{
		delete lemoner[i];
	}
	delete[] lemoner;

	//とまトンの削除
	for (int i = 0; i < tomaton_count; i++)
	{
		delete tomaton[i];
	}
	delete[] tomaton;
	//グレポンの削除
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

	pause->Update();

	if (pause->IsPause() == false) {

		//経過時間の加算
		elapsed_time += 1000 / 60;

		player->Update(element, stage, tomaton, tomaton_count);
		stage->Update(player, element);	//ステージクリア用
		element->Update(player, stage);
		for (int i = 0; i < lemoner_count; i++)
		{
			if (lemoner[i] != nullptr)
			{
				lemoner[i]->Update();
				if (lemoner[i]->GetDeleteFlag())
				{
					item_rand = GetRand(5);
					//アイテムを生成
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
				//アイテムを生成
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
		//アイテムのアップデート
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



			//ゲームオーバー
			if (player->IsDeath()) {
				if (!restart && stage->GetHalfwayPointFlg()) {
					halfway_time = time - GetNowCount();
					elapsed_time = GetNowCount() - time;
					return new GAMEMAIN(true, elapsed_time, stage_name);
				}
				return new GameOver(stage_name);
			}

			//ステージクリア
			if (stage->GetClearFlg())
			{
				const int clear_time = GetNowCount() - time + halfway_time;
				return new RESULT(true, clear_time, stage_name);
			}
		}
	}
	else {	//ポーズ画面のセレクター

		if (static_cast<PAUSE::MENU>(pause->GetSelectMenu()) == PAUSE::MENU::TITLE) { return new Title(); }
		else if (static_cast<PAUSE::MENU>(pause->GetSelectMenu()) == PAUSE::MENU::RESTART) { return new GAMEMAIN(false, 0, stage_name); }
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

	//デバッグ
	if (CheckHitKey(KEY_INPUT_F)) {
		int scrollx = -(7800 - 500);
		stage->SetScrollX(scrollx);	//スポーン地点をセット
		player->SetPlayerX(500); //プレイヤーの画面内座標をセット
	}
	return this;
}

void GAMEMAIN::Draw() const
{

	//ステージ背景
	if (stage_name != "Stage02") {
		DrawGraph(int(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[0], FALSE);
		DrawGraph(int(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[0], FALSE);
	}
	else if (stage_name == "Stage02") {
		DrawGraph(int(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[1], FALSE);
		DrawGraph(int(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[1], FALSE);
	}


	//地下背景描画
	if (stage_name == "Stage01") {
		//ステージ１
		DrawBox(stage->GetScrollX() + 6880, stage->GetScrollY() + 1380, stage->GetScrollX() + 10640, stage->GetScrollY() + 1900, 0x20251F, TRUE);
	}
	else if (stage_name == "Stage03") {
		//ステージ3
		DrawBox(0, stage->GetScrollY() + 1380, stage->GetScrollX() + 5120, stage->GetScrollY() + 4800, 0x20251F, TRUE);
	}

	/*if (stage_name == "Stage03" && stage->GetScrollY() < -960) {
		DrawBox(0, 0, 25600, 1280, 0x20251F, TRUE);
	}*/

	for (int i = 0; i < player->GetLife(); i++) {
		DrawRotaGraph(30 + 50 * i, 20, 1, 0, hp_img, TRUE);
	}

	//ステージの描画
	stage->Draw(element);
	element->Draw(stage, player);



	//プレイヤーの描画
	player->Draw(stage);

	//レモナーの描画
	for (int i = 0; i < lemoner_count; i++)
	{
		if (lemoner[i] != nullptr)
		{
			lemoner[i]->Draw();

		}
	}
	//とまトンの描画
	for (int i = 0; i < tomaton_count; i++)
	{
		tomaton[i]->Draw();
	}
	//グレポンの描画
	for (int i = 0; i < gurepon_count; i++)
	{
		if (gurepon[i] != nullptr && gurepon[i]->GetDeleteFlg() == false)
		{
			gurepon[i]->Draw();
		}
	}
	//アイテムの描画
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

	//プレイヤーのライフの描画
	for (int i = 0; i < player->GetLife(); i++) {
		DrawRotaGraph(30 + 50 * i, 20, 1, 0, hp_img, TRUE);
	}

	//経過時間の描画
	char dis_clear_time[20];	//文字列合成バッファー

	//文字列合成
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


	if (pause->IsPause() == true) { //ポーズ画面へ

		pause->Draw();
	}

	//デバッグ
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
