#include "GameMain.h"
#include "Title.h"
#include <vector>
#include "Option.h"
#include "Ranking.h"

GAMEMAIN::GAMEMAIN(bool restert, int halfway_time, const char* stage_name)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage1.png");
	background_image[1] = LoadGraph("Resource/Images/Stage/BackImage2.png");

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
	menu_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 80, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	title_font = CreateFontToHandle("UD デジタル 教科書体 N-B", 140, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);
	time = GetNowCount();
	this->halfway_time = halfway_time;
	this->stage_name = stage_name;
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
	DeleteGraph(background_image[0]);
	DeleteGraph(background_image[1]);

	if (stage_name == "Stage01") {
		StopSoundMem(background_music[0]);
		DeleteSoundMem(background_music[0]);
	}
	else if (stage_name == "Stage02") {
		StopSoundMem(background_music[1]);
		DeleteSoundMem(background_music[1]);
	}
	else if (stage_name == "Stage03") {
		StopSoundMem(background_music[2]);
		DeleteSoundMem(background_music[2]);
	}
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
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

	//STARTボタンでポーズ
	if ((PAD_INPUT::GetNowKey() == XINPUT_BUTTON_START) && (PAD_INPUT::GetPadState() == PAD_STATE::ON)) { pause->SetPause(); }

	if (pause->IsPause() == false) {
		player->Update(element, stage);
		stage->Update(player, element);	//ステージクリア用
		element->Update(player,stage);
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
						item[item_num++] = new ITEMBALL(lemoner[i]->GetX(), lemoner[i]->GetY(), lemoner[i]->GetMapX(), lemoner[i]->GetMapY(), player, stage, stage->GetScrollX(),stage->GetScrollY());
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
					item[item_num++] = new ITEMBALL(gurepon[i]->GetX(), gurepon[i]->GetY(), gurepon[i]->GetSpawnMapX(), gurepon[i]->GetSpawnMapY(), player, stage, stage->GetScrollX(),stage->GetScrollY());
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
					halfway_time =  time - GetNowCount();
					return new GAMEMAIN(true,halfway_time,stage_name); 
				}
				return new GameOver(stage_name);
			}

			//ステージクリア
			if (stage->GetClearFlg())
			{ 
				if (stage_name == "Stage01")
				{
					RANKING::Insert(GetNowCount() - (time + halfway_time), 1);
				}
				else if (stage_name == "Stage02")
				{
					RANKING::Insert(GetNowCount() - (time + halfway_time), 2);
				}
				else if (stage_name == "Stage03")
				{
					RANKING::Insert(GetNowCount() - (time + halfway_time), 3);
				}
				else{}
				return new RESULT(true, time + halfway_time); 
			}
		}
	}
	else {	//ポーズ画面のセレクター
		pause->Update();
		if (pause->GetSelectMenu() == 3) { return new Title(); }
		else if (pause->GetSelectMenu() == 1) { return new GAMEMAIN(false,0,stage_name); }
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
	else if(stage_name == "Stage02"){
		DrawGraph(int(stage->GetScrollX()) % 2560 + 2560, /*scroll_y*/0, background_image[1], FALSE);
		DrawGraph(int(stage->GetScrollX()) % 2560, /*scroll_y*/0, background_image[1], FALSE);
	}

	if (stage_name == "Stage03" && stage->GetScrollY() < -960) {
		DrawBox(0, 0, 25600, 1280, 0x20251F, TRUE);
	}



	//ステージの描画
	element->Draw(stage);
	stage->Draw(element);
	
	

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

	if (pause->IsPause() == true) { //ポーズ画面へ
		int pause_graph = MakeGraph(1280, 720);
		GetDrawScreenGraph(0, 0, 1280, 720, pause_graph);

		pause->Draw(pause_graph);
	}

	//デバッグ
	if (CheckHitKey(KEY_INPUT_A)) {
		DrawFormatString(100, 150, 0xF77D0A, "ScrollX:%f", stage->GetScrollX());
		DrawFormatString(100, 200, 0xF77D0A, "ScrollY:%f", stage->GetScrollY());
		DrawFormatString(100, 250, 0xE04D02, "MapData:%d", stage->GetMapData((player->GetPlayerY() / MAP_CEllSIZE) +1, player->GetPlayerX()/ MAP_CEllSIZE));
		DrawFormatString(100, 300, 0x02F896, "PlayerX%f", player->GetPlayerX());
		DrawFormatString(100, 350, 0x02F896, "PlayerY%f", player->GetPlayerY());
		DrawFormatString(100, 400, 0x02F896, "SpawnPointY:%d", stage->GetSpawnPoint().y);
		DrawFormatString(100, 450, 0x02F896, "Jump:%f", player->GetJumpVelocity());
	}
}
