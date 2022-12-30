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
#include "Option.h"

//#define _DEBUG

/// <summary>
/// コンストラクタ
/// </summary>
STAGE::STAGE(const char* stage_name, bool restert) {
	//**map_data = 0;
	*block_image1 = 0;
	*stage_image = 0;
	scroll_x = 0;
	scroll_y = 0;
	scroll_speed_x = 5;
	scroll_speed_y = 5;
	count_timer = 0;

	player_x_old = 0;
	player_y_old = 0;
	player_vector_x = 0;
	player_vector_y = 0;


	if (LoadDivGraph("Resource/Images/Stage/map_chips.png", 110, 10, 11, 80, 80, block_image1) == -1) {
		throw "Resource/Images/Stage/map_chips.png";
	}

	if ((halfwaypoint_se = LoadSoundMem("Resource/Sounds/SE/Stage/halfwaypoint.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/halfwaypoint.wav";
	}

	//map_data.resize(MAP_HEIGHT);

	//InitStage();

	LoadMapData(stage_name);
	temporary_hit = 999;
	clearflg = false;
	clearbox = { 0,0 };
	clear_count = 3000;
	halfwaypointbox = { 0,0 };
	halfwaypoint = restert;
	halfway_timer = 0;
	spawn_point = { 0,0 };
	this->stage_name = stage_name;


	for (int i = 0; i < map_data.size(); i++) {
		for (int j = 0; j < map_data.at(0).size(); j++) {
			//クリア座標を代入
			if (map_data.at(i).at(j) == 88) { clearbox.x = j * MAP_CEllSIZE; clearbox.y = i * MAP_CEllSIZE; }
			//中間地点座標を代入
			if (map_data.at(i).at(j) == 90) { halfwaypointbox.x = j * MAP_CEllSIZE; halfwaypointbox.y = i * MAP_CEllSIZE; }

			//スポーン地点座標を代入
			if (map_data.at(i).at(j) == 777) { spawn_point.x = i * MAP_CEllSIZE; spawn_point.y = j * MAP_CEllSIZE; }
		}
	}
	//スポーン地点をセット
	if (spawn_point.x == 0 && spawn_point.y == 0) {
		MessageBox(NULL, "スポーン地点がセットされていません。", "マップ読み込みエラー", MB_OK | MB_ICONERROR);
		spawn_point.x = 0;
		spawn_point.y = 0;
	}

	ChangeVolumeSoundMem(Option::GetSEVolume(), halfwaypoint_se);
}
/// <summary>
/// デストラクタ
/// </summary>
STAGE::~STAGE() {
	for (int i = 0; i < 110; i++) {
		DeleteGraph(block_image1[i]);
	}
	DeleteSoundMem(halfwaypoint_se);
}

/// <summary>
/// ステージの更新
/// </summary>
void STAGE::Update(PLAYER* player, ELEMENT* element) {

	//デバッグ
	//if (CheckHitKey(KEY_INPUT_C))clearflg = true;
	ChangeVolumeSoundMem(Option::GetSEVolume(), halfwaypoint_se);

	StageClear(player);
	HalfwayPoint(player);
	CameraWork(player, element);
}
/// <summary>
/// ステージの描画
/// </summary>
void STAGE::Draw(ELEMENT* element)const {

	for (int i = 0; i < map_data.size(); i++) {
		for (int j = 0; j < map_data.at(0).size(); j++) {
			//if (map_data.at(i).at(j) == 72)DrawFormatString(100 + j * 20, 50, 0xffffff, "%d %d", i, j);
			//画面外は描画しない
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280 && i * MAP_CEllSIZE + scroll_y >= -80 && i * MAP_CEllSIZE + scroll_y <= 720) {
				if (
					map_data.at(i).at(j) != 68		//マンホール(上)
					&& map_data.at(i).at(j) != 62	 //ボタン
					&& map_data.at(i).at(j) != 74	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 75	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 76	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 77	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 78	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 79	//酸性雨の水たまり
					&& map_data.at(i).at(j) != 101		//戻る看板下で別途描画している為
					&& map_data.at(i).at(j) != 102	//ステージ1ゲート(上)
					&& map_data.at(i).at(j) != 103	//ステージ1ゲート(下)
					&& map_data.at(i).at(j) != 104	//ステージ2ゲート(上)
					&& map_data.at(i).at(j) != 105	//ステージ2ゲート(下)
					&& map_data.at(i).at(j) != 106	//ステージ3ゲート(上)
					&& map_data.at(i).at(j) != 107	//ステージ3ゲート(下)
					&& map_data.at(i).at(j) != 51	//動く床
					&& map_data.at(i).at(j) != 52	//動く床
					&& map_data.at(i).at(j) != 53	//動く床
					&& map_data.at(i).at(j) != 54	//動く床
					&& (map_data.at(i).at(j) <= 88		//クリア門等
						////89～90番台を描画しない
						|| map_data.at(i).at(j) >= 100 && map_data.at(i).at(j) != 777)
					) {
					DrawGraphF(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE);
				}
			}
			//レモナーとグレポンはツルだけ描画する
			if (map_data.at(i).at(j) == 91 || map_data.at(i).at(j) == 92) { DrawGraphF(j * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE); }
			if (map_data.at(i).at(j) == 101) { DrawExtendGraphF((j - 1) * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE + scroll_y, (j + 1) * MAP_CEllSIZE + scroll_x, (i + 1) * MAP_CEllSIZE + scroll_y, block_image1[100], TRUE); }
		}
	}

	//中間地点　描画
	//中間地点がない場合は描画しない。
	if (halfwaypointbox.x != 0) {
		if (halfwaypoint == false) { DrawGraphF(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[88], TRUE); }
		else { DrawGraphF(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[89], TRUE); }
	}

}

/// <summary>
/// マップデータの読み込み
/// </summary>
void STAGE::LoadMapData(const char* stage_name) {

	char buf[37];
	sprintf_s(buf, sizeof(buf), "Resource/Map_Data/%s.csv", stage_name);
	//std::ifstream ifs(buf);

	//map_data.clear();
	//map_data.shrink_to_fit();
	////std::string str = "";

	//int i = 0, j = 0;

	//while (std::getline(ifs, str))
	//{
	//	std::string tmp = "";
	//	std::istringstream stream(str);
	//	map_data.push_back(std::vector<int>());

	//	while (std::getline(stream,tmp,','))
	//	{
	//		//map_data.at(i).at(j) = std::stoi(tmp);
	//		map_data[i].push_back(std::stoi(tmp));
	//		j++;
	//	}
	//	j = 0;
	//	i++;
	//}



	//アーカイブ対応版


	int FileHandle;
	if ((FileHandle = FileRead_open(buf)) == 0) {
		exit(1);
	}

	char str[642];		//一行の長さ
	char* context;
	int i = 0, j = 0;

	while (FileRead_gets(str, sizeof(str), FileHandle) != -1) {

		char* tmp = strtok_s(str, ",", &context);

		map_data.push_back(std::vector<int>());
		while (tmp != NULL) {
			//map_data[i][j] = atoi(tmp);

			std::string info[2];
			std::istringstream streamtmp(tmp);
			int k = 0;
			while (std::getline(streamtmp, info[k], ':')) {
				k++;
			}

			map_data[i].push_back(std::stoi(tmp));

			//ボタンとドアの連携番号を格納
			if ((map_data[i][j] == 61 || map_data[i][j] == 62) && info[1] != "") {
				button_info.push_back(std::vector<int>());
				button_info.at(button_info.size() - 1).push_back(i);
				button_info.at(button_info.size() - 1).push_back(j);
				button_info.at(button_info.size() - 1).push_back(std::stoi(info[1]));
			}
			if (map_data[i][j] == 66 && info[1] != "") {
				door_info.push_back(std::vector<int>());
				door_info.at(door_info.size() - 1).push_back(i);
				door_info.at(door_info.size() - 1).push_back(j);
				door_info.at(door_info.size() - 1).push_back(std::stoi(info[1]));

			}

			tmp = strtok_s(NULL, ",", &context);
			j++;
		}
		j = 0;
		i++;
	}

	FileRead_close(FileHandle);

}

/// <summary>
/// マップ配列のGetter
/// </summary>
int STAGE::GetMapData(int y, int x) {
	if (y < 0 || y >= map_data.size()) { return -999; }
	if (x < 0 || x >= map_data[y].size()) { return -999; }
	return map_data.at(y).at(x);
}

/// <summary>
/// ステージスクロール関数
/// </summary>
void STAGE::CameraWork(PLAYER* player, ELEMENT* element) {
	int scroll_speedY = 7;
	//プレイヤーxベクトルの判定
	if (player->GetPlayerX() > player_x_old) {
		player_vector_x = 1;
	}
	else if (player->GetPlayerX() < player_x_old) {
		player_vector_x = -1;
	}

	//プレイヤーyベクトルの判定
	if (player->GetPlayerY() < player_y_old) {
		player_vector_y = 1;
	}
	else if (player->GetPlayerY() > player_y_old) {
		player_vector_y = -1;
		//scroll_speedY = 10;
	}
	scroll_speed_x = player->GetPlayerSpeed();
	if (player->GetPlayerMoveState() == PLAYER_MOVE_STATE::HOOK) {
		scroll_speed_x = fabsf(player->GetPlayerHookSpeed());
	}
	//x軸スクロール
	//if (element->HitLift(player)) { scroll_speed_x = element->GetLift_SpeedX(); }
	if ((player_vector_x > 0 && player->GetPlayerX() >= 620 || player_vector_x < 0 && player->GetPlayerX() <= 660) && player_x_old != player->GetPlayerX()) {
		scroll_x -= scroll_speed_x * player_vector_x;
		if (scroll_x > 0 || scroll_x <= -(80 * static_cast<int>(map_data.at(0).size()) - 1280)) {
			scroll_x += scroll_speed_x * player_vector_x;
		}
	}

	//y軸スクロール
	//if ((player_vector_y > 0 && player->GetPlayerY() <= 240 || player_vector_y < 0 && (scroll_y > 0 && map_data.size() <= 14) || (scroll_y > -720 && map_data.size() > 14)) && player_y_old != player->GetPlayerY()) {
	//	scroll_y += scroll_speedY * player_vector_y;
	//	if (scroll_y > 0/* || scroll_x <= -(80 * static_cast<int>(map_data.size()) - 720)*/) {
	//		scroll_y -= scroll_speedY * player_vector_y;
	//	}
	//}


	//x軸スクロールを元にy座標バージョンを作成
	//if ((player_vector_y > 0 && player->GetPlayerY() >= 620 || player_vector_y < 0 && player->GetPlayerY() <= 300)) {
	//	scroll_y -= 5 * player_vector_y;
	//	//if (scroll_y > 0 || scroll_y <= -(80 * static_cast<int>(map_data.size()) - 720)) {
	//	//	scroll_y += 5 * player_vector_y;
	//	//}
	//}

	if (++count_timer % 60 == 0)player_longold = player->GetPlayerY();

	//スポーン地点を基準に上げる位置を決める
	//if (scroll_y + player->GetPlayerY() < 0 && player->GetPlayerY() <= spawn_point.y - player->GetPlayerY() + 400 && player->GetPlayerMoveState() != PLAYER_MOVE_STATE::HOOK) { scroll_y += scroll_speed_y; }
	//else if (scroll_y + player->GetPlayerY() < player->GetPlayerY()) {
	//	if (scroll_y >= (-MAP_CEllSIZE * static_cast<int>(map_data.size()) + 721) && (player->GetPlayerY() > GetSpawnPoint().y + 400)) {
	//		//プレイヤーの落下速度に応じてスクロールYを下げる
	//		if (player->GetJumpVelocity() > 0)scroll_y -= player->GetJumpVelocity();
	//	}
	//	if ((player->GetPlayerMoveState() == PLAYER_MOVE_STATE::HOOK || player->GetPlayerMoveState() == PLAYER_MOVE_STATE::GROW_HOOK) && player->GetPlayerY() > 500.0f) {
	//		scroll_y -= 5;
	//	}
	//}


	//マンホールの下にいった時	
	//if (-scroll_y + player->GetPlayerY() > player->GetPlayerY())scroll_y--;
	//for(unsigned int i=scroll_y )

	//スクロールY-720とプレイヤーY520の誤差が200になるまで



	if (player->GetPlayerY() >= 560 &&player->GetPlayerY()-scroll_y<=map_data.size()*MAP_CEllSIZE&& GetMapData((player->GetPlayerY() - scroll_y) / MAP_CEllSIZE + 3, (player->GetPlayerX() - scroll_x) / MAP_CEllSIZE) != -1) {
		if (player->GetPlayerMoveState() == PLAYER_MOVE_STATE::FALL) {
			//プレイヤーの落下速度に応じてスクロールYを下げる
			if (player->GetJumpVelocity() > 0)scroll_y -= player->GetJumpVelocity();
		}
		else {
			scroll_y -= 5;
		}
	}
	else if (player->GetPlayerY() <= 320) {
		scroll_y += 5;
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

/// <summary>
/// 画面スクロール座標XのSetter
/// </summary>
bool STAGE::SetScrollPos(int move_x) {
	scroll_x -= 5 * move_x;
	if (scroll_x >= 0 || scroll_x <= -(80 * static_cast<int>(map_data.at(0).size()) - 640)) {
		scroll_x += 5 * move_x;
		return true;
	}
	return false;
}

/// <summary>
/// プレイヤーとブロックの当たり判定
/// </summary>
bool STAGE::HitMapDat(int y, int x) {
#ifdef _DEBUG
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_Y || CheckHitKey(KEY_INPUT_Z))return false;		//デバッグ用
#endif
	int block_type = GetMapData(y, x);
	if (block_type == temporary_hit) { return true; }
	if (
		block_type == -1 //範囲外
		|| block_type == 0	//水玉草
		|| block_type == 21 //フロー木
		|| block_type == 22 //アカシア木
		|| block_type == 23 //オーク木
		|| block_type == 24 //先生作木
		|| block_type == 31 //葉っぱ
		|| block_type == 51	//動く床(縦)
		|| block_type == 52	//動く床(横)
		|| block_type == 53	//動く床(ゴール縦)
		|| block_type == 54	//動く床(ゴール横)
		|| block_type == 64	//ドア 
		|| block_type == 65	//ドア 
		|| block_type == 62	//ボタン(感圧式)
		|| block_type == 68	//マンホールの蓋
		|| block_type == 69	//マンホールの中
		|| block_type == 71	//ツル中間
		|| block_type == 72	//ツル
		|| block_type == 73	//ゴール
		|| block_type == 85	//クリア門
		|| block_type == 86	//クリア門
		|| block_type == 87	//クリア門
		|| block_type == 88	//クリア門
		|| block_type == 90 //中間地点
		|| block_type == 91 //レモナー
		|| block_type == 92 //グレポン
		|| block_type == 93	//トマトン
		|| block_type == 97	//マンホールの蓋(出口)
		|| block_type == 98	//マンホールの開いている蓋
		|| block_type == 101//戻るブロック
		|| block_type == 102//ステージ1ブロック
		|| block_type == 103//ステージ2ブロック
		|| block_type == 104//ステージ3ブロック
		|| block_type == 105//ステージ3ブロック
		|| block_type == 106//ステージ3ブロック
		|| block_type == 107//ステージ3ブロック
		|| block_type == 777//スポーン地点ブロック
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
		|| block_type == 31 //葉っぱ
		|| block_type == 61	//壁ボタン(感圧式)
		|| block_type == 62	//ボタン(感圧式)
		|| block_type == 68	//マンホールの蓋
		|| block_type == 69	//マンホールの中
		|| block_type == 71	//ツタ
		|| block_type == 72	//ツタ(捕まる部分)
		|| block_type == 73	//ゴール
		|| block_type == 86	//クリア門
		|| block_type == 87	//クリア門
		|| block_type == 88	//クリア門
		|| block_type == 89	//クリア門
		|| block_type == 97	//マンホールの蓋End
		|| block_type == 98	//マンホールの開いている蓋
		|| block_type == 101//戻るブロック
		|| block_type == 102//ステージ1ブロック
		|| block_type == 103//ステージ2ブロック
		|| block_type == 104//ステージ3ブロック
		|| block_type == 777//スポーン地点ブロック
		) {
		return false;
	}
	return true;
}


/// <summary>
/// ステージクリア判定処理
/// </summary>
void STAGE::StageClear(PLAYER* player) {

	int player_map_x = static_cast<int>(roundf(player->GetPlayerX() - scroll_x));
	int player_map_y = static_cast<int>(floorf(player->GetPlayerY()) - scroll_y);

	//旗に触れるとゲームクリア
	if ((player_map_x >= clearbox.x - MAP_CEllSIZE / 2 + 50) && (player_map_x <= clearbox.x + MAP_CEllSIZE + 30) && (player_map_y >= clearbox.y - MAP_CEllSIZE * 8) && (player_map_y <= clearbox.y + MAP_CEllSIZE / 2)) {
		clearflg = true;
	}

	if (clearflg == true) {

		if (--clear_count <= 0) {
			clearflg = false;
			clear_count = 3000;
		}
		/*if (GetNowCount() % 30 == 0)printfDx("%d:::::%d\n", count, GetNowCount());*/
	}

}
/// <summary>
/// 中間地点判定処理
/// </summary>
void STAGE::HalfwayPoint(PLAYER* player) {
	int player_map_x = roundf(player->GetPlayerX() - STAGE::GetScrollX());
	int player_map_y = floorf(player->GetPlayerY());
	if ((player_map_x >= halfwaypointbox.x - MAP_CEllSIZE / 2) && (player_map_x <= halfwaypointbox.x + MAP_CEllSIZE / 2)/* && (player_map_y >= halfwaypointbox.y - MAP_CEllSIZE) && (player_map_y <= halfwaypointbox.y + MAP_CEllSIZE)*/) {

		if (halfwaypoint == false) {
			PlaySoundMem(halfwaypoint_se, DX_PLAYTYPE_BACK, TRUE);

			if (++halfway_timer < 180) {
				DrawOvalAA(halfwaypointbox.x + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
				DrawOvalAA(halfwaypointbox.x + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
				DrawOvalAA(halfwaypointbox.x + scroll_x + anitimer % 3, halfwaypointbox.y + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			}
			else if (180 <= halfway_timer)halfway_timer = 0;
		}
		halfwaypoint = true;
	}
}