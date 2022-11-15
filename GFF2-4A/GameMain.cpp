#include "GameMain.h"
#include <vector>

GAMEMAIN::GAMEMAIN(bool restert)
{
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
	std::vector<std::vector<int>> spawn_point;
	background_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	time = GetNowCount();
	lemoner_count = 0;
	tomaton_count = 0;

	player = new PLAYER;
	stage = new STAGE;
	lemoner = nullptr;
	gurepon = nullptr;
	tomaton = nullptr;

	//とまトン生成する数を数える
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
	//とまトンの生成
	if (tomaton_count > 0)
	{
		tomaton = new TOMATO*[tomaton_count];
		for (int i = 0; i < tomaton_count; i++)
		{
			tomaton[i] = new TOMATO(player,stage, spawn_point[i][0],spawn_point[i][1]);
		}
	}

	//スポーンポイントを削除
	spawn_point.clear();

	//グレポンを生成する数を数える
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
	//レモナーの生成
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
}

GAMEMAIN::~GAMEMAIN()
{
	delete player;
	delete stage;

	//レモナーの削除
	for (int i = 0; i < lemoner_count; i++) {
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
	
	delete element;
}

AbstractScene* GAMEMAIN::Update()
{
	
	player->Update(element,stage);
	stage->Update(player);	//ステージクリア用
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
		else if(gurepon[i] != nullptr && !gurepon[i]->GetDeleteFlg())
		{
			gurepon[i]->Update();
		}
		else
		{}
	}

	//ゲームオーバー
	if (player->IsDeath()) {
		if (restart == false) {return new GAMEMAIN(true); }
		else if(restart == true)return new RESULT(false);
	}

	//ステージクリア
	if (stage->GetClearFlg()) { return new RESULT(true,time); };

	return this;
}

void GAMEMAIN::Draw() const
{

	//ステージ背景
	DrawGraph(int(STAGE::GetScrollX()) % 1280 + 1280, /*scroll_y*/0, background_image[0], FALSE);
	DrawTurnGraph(int(STAGE::GetScrollX()) % 1280, /*scroll_y*/0, background_image[0], FALSE);


	//ステージの描画
	element->Draw();
	stage->Draw();
	
	//プレイヤーの描画
	player->Draw();

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

	//デバッグ
	//DrawFormatString(200, 300, 0xffffff, "GetPlayerY:%f", player->GetPlayerY());
}