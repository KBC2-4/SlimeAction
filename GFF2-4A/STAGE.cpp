#include "STAGE.h"
#include "Element.h"
#include"DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#include "PLAYER.h"
#include "RESULT.h"

float STAGE::scroll_x = 0;
float STAGE::scroll_y = 0;

STAGE::STAGE(const char* stage_name) {
	//**map_data = 0;
	*block_image1 = 0;
	*stage_image = 0;
	//scroll_x = -8640;
	scroll_x = 0;
	scroll_y = 0;
	player_x_old = 20.f;
	player_y_old = 500.f;
	player_vector_x = 0;
	player_vector_y = 0;

	if (LoadDivGraph("Resource/Images/Stage/map_chips.png", 100, 10, 10, 80, 80, block_image1) == -1) {
		throw "Resource/Images/Stage/map_chips.png";
	}

	if ((halfwaypoint_se = LoadSoundMem("Resource/Sounds/SE/Stage/halfwaypoint.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/halfwaypoint.wav";
	}

	//map_data.resize(MAP_HEIGHT);

	//InitStage();

	LoadMapData(stage_name);
	clearflg = false;
	clearbox = {0,0};
	halfwaypointbox = {0,0};
	halfwaypoint = false;

	int iy = 0;
	int yx = 0;
	iy = map_data.size();
	yx = map_data.at(0).size();

	for (int i = 0; i < map_data.size(); i++) {
		for (int j = 0; j < map_data.at(0).size(); j++) {
			//クリア座標を代入
			if (map_data.at(i).at(j) == 73) { clearbox.x  = j * MAP_CEllSIZE; clearbox.y = i * MAP_CEllSIZE; }
			//中間地点座標を代入
			if (map_data.at(i).at(j) == 90) { halfwaypointbox.x = j * MAP_CEllSIZE; halfwaypointbox.y = i * MAP_CEllSIZE; }
		}
	}
}
	

void STAGE::Update(PLAYER* player, ELEMENT* element) {
	StageClear(player);
	HalfwayPoint(player);
	if (player->GetPlayerMoveState() != PLAYER_MOVE_STATE::HOOK && !element->HitLift(player->GetPlayerScale())) {
		CameraWork(player);
	}
	
}

void STAGE::Draw()const {
	//デバッグ
	//DrawFormatString(200, 100, 0xffffff, "oldx:%f", player_x_old);
	//DrawFormatString(350, 100, 0xffffff, "vectorx:%f", player_vector_x);
	//DrawFormatString(100, 200, 0xffffff, "scroll_x:%f", scroll_x);
	//DrawFormatString(200, 200, 0xffffff, "scroll_y:%f", scroll_y);
	//ゲームクリア時
	if (clearflg == true) {DrawExtendString(30, 200, 5.5f, 5.5f, "ゲームクリアおめでとう！！！", 0xE2FE47);}
	
	//printfDx("%f",scroll_x);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			
			//画面外は描画しない
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280 && j * MAP_CEllSIZE + scroll_y >= -300) {
				if (map_data.at(i).at(j) < 89 && map_data.at(i).at(j) != 68
					|| (map_data.at(i).at(j) <= 74	//酸性雨の水たまりを描画しない
												////マンホールの開いている蓋を描画しない
					&& map_data.at(i).at(j) >= 79)
					) { DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE); }
			}
			//レモナーとグレポンはツルだけ描画する
			if (map_data.at(i).at(j) == 91 || map_data.at(i).at(j) == 92) { DrawGraph(j * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE); }
			
		}
	}

	//中間地点　描画
	if(halfwaypoint == false){ DrawGraph(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[88], TRUE); }
	else{ DrawGraph(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[89], TRUE); }
	
}

/// <summary>
/// ステージスクロール関数
/// </summary>
void STAGE::CameraWork(PLAYER* player) {
	//プレイヤーxベクトルの判定
		if (player->GetPlayerX() - player_x_old > 0) {
			player_vector_x = 1;
		}
		else if (player->GetPlayerX() - player_x_old < 0) {
			player_vector_x = -1;
		}
	
	


	if ((player_vector_x > 0 && player->GetPlayerX() >= 620 || player_vector_x < 0 && player->GetPlayerX() <= 660) && player_x_old != player->GetPlayerX()) {
		scroll_x -= 5 * player_vector_x;
		if (scroll_x > 0 || scroll_x <= -(80 * MAP_WIDTH - 640)) {
			scroll_x += 5 * player_vector_x;
		}
	}

	
	if (player->GetPlayerY()>=720) {
		scroll_y = -320;
	}
	else if (player->GetPlayerY() < 640) {
		scroll_y = 0;
	}

	if (player_x_old != player->GetPlayerX()) {
		player_x_old = player->GetPlayerX();
	}
	else {
		player_vector_x = 0;
	}
	if (player_y_old != player->GetPlayerY()) {
		player_y_old = player->GetPlayerY();
	}
	else player_vector_y = 0;
}



void STAGE::HookProcess() {

}

void STAGE::PuddleProcess(){

}

/// <summary>
/// ステージのスクロール
/// </summary>
bool STAGE::SetScrollPos(int move_x) {
	scroll_x -= 5 * move_x;
	if (scroll_x >= 0 || scroll_x <= -(80 * MAP_WIDTH - 640)) {
	scroll_x += 5 * move_x;
		return true;
	}
	return false;
}

int STAGE::GetMapData(int y, int x) {
	if (y < 0 || y >= map_data.size())
		return 0;
	if (x < 0 || x >= map_data[y].size())
		return 0;
	return map_data.at(y).at(x);
}

/// <summary>
/// プレイヤーとブロックの当たり判定
/// </summary>

bool STAGE::HitMapDat(int y, int x) {
	if (CheckHitKey(KEY_INPUT_Z))return false;		//デバッグ用
	int block_type = GetMapData(y, x);
	if (
		block_type == -1 //範囲外
		|| block_type == 0	//水玉草
		|| block_type == 21 //フロー木
		|| block_type == 22 //アカシア木
		|| block_type == 23 //オーク木
		|| block_type == 64	//ドア 
		|| block_type == 65	//ドア 
		|| block_type == 62	//ボタン(感圧式)
		|| block_type == 68	//マンホールの蓋
		|| block_type == 69	//マンホールの中
		|| block_type == 71	//ゴール
		|| block_type == 73	//ゴール
		|| block_type == 90 //中間地点
		|| block_type == 91 //レモナー
		|| block_type == 92 //グレポン
		|| block_type == 93	//トマトン
		|| block_type == 95	//動く床
		|| block_type == 96 //動く床(ゴール)
		|| block_type == 97	//マンホールの蓋(出口)
		|| block_type == 98	//マンホールの開いている蓋
		) {
		return false;
	}
	return true;
}
/// <summary>
/// スライムのかけらの当たり判定
/// </summary>
bool STAGE::HitThrowSlime(int y, int x) {
	int block_type = GetMapData(y, x);
	if (
		block_type == -1 //範囲外
		|| block_type == 0	//水玉草
		|| block_type == 61	//壁ボタン(感圧式)
		|| block_type == 62	//ボタン(感圧式)
		|| block_type == 68	//マンホールの蓋
		|| block_type == 69	//マンホールの中
		|| block_type == 71	//ツタ
		|| block_type == 72	//ツタ(捕まる部分)
		|| block_type == 73	//ゴール
		|| block_type == 97	//マンホールの蓋End
		|| block_type == 98	//マンホールの開いている蓋
		) {
		return false;
	}
		return true;
}

/// <summary>
/// マップデータの読み込み
/// </summary>
void STAGE::LoadMapData(const char* stage_name) {

		char buf[37];
		sprintf_s(buf, sizeof(buf), "Resource/Map_Data/%s.csv", stage_name);
		std::ifstream ifs(buf);

		std::string str = "";
		int i = 0, j = 0;
		while (std::getline(ifs,str))
		{
			std::string tmp = "";
			std::istringstream stream(str);
			map_data.push_back(std::vector<int>());

			while (std::getline(stream,tmp,','))
			{
				//map_data.at(i).at(j) = std::stoi(tmp);
				map_data[i].push_back(std::stoi(tmp));
				j++;
			}
			j = 0;
			i++;
		}
}


/// <summary>
/// ステージクリア時
/// </summary>
void STAGE::StageClear(PLAYER *player) {
	int player_map_x = static_cast<int>(roundf(player->GetPlayerX() - STAGE::GetScrollX()));
	int player_map_y = static_cast<int>(floorf(player->GetPlayerY()));
	DrawFormatString(100, 200, 0xffffff, "x:%dy:%d", clearbox.x , clearbox.y);

	//旗に触れるとゲームクリア
	if ((player_map_x >= clearbox.x  - MAP_CEllSIZE / 2 + 50) && (player_map_x <= clearbox.x  + MAP_CEllSIZE + 30) && (player_map_y >= clearbox.y - MAP_CEllSIZE / 2) && (player_map_y <= clearbox.y + MAP_CEllSIZE / 2)) {
		clearflg = true;
	}

	if (clearflg == true) {
		static int count = GetNowCount();
		if ((GetNowCount() - count) > 3000) {
			clearflg = false;
			count = GetNowCount();
		}
		/*if (GetNowCount() % 30 == 0)printfDx("%d:::::%d\n", count, GetNowCount());*/
	}
	
}

void STAGE::HalfwayPoint(PLAYER *player) {
	int player_map_x = roundf(player->GetPlayerX() - STAGE::GetScrollX());
	int player_map_y = floorf(player->GetPlayerY());
	if ((player_map_x >= halfwaypointbox.x - MAP_CEllSIZE / 2) && (player_map_x <= halfwaypointbox.x + MAP_CEllSIZE / 2) && (player_map_y >= halfwaypointbox.y - MAP_CEllSIZE) && (player_map_y <= halfwaypointbox.y + MAP_CEllSIZE)) {
		//デバッグ
		//printfDx("aaa");
		if (halfwaypoint == false) { PlaySoundMem(halfwaypoint_se, DX_PLAYTYPE_BACK, TRUE); 
		static int anitimer = 0;
		if (++anitimer < 180) {
			DrawOvalAA(halfwaypointbox.x + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			DrawOvalAA(halfwaypointbox.x + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			DrawOvalAA(halfwaypointbox.x + scroll_x + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
		}
		else if (180 <= anitimer)anitimer = 0;
		}
		halfwaypoint = true;
	}
}