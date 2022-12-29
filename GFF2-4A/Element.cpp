#include "Element.h"
#include "PLAYER.h"
#include "Option.h"

/// <summary>
/// コンストラクタ
/// </summary>
ELEMENT::ELEMENT(const char* stage_name) : STAGE(stage_name) {

	guid_font = CreateFontToHandle("メイリオ", 23, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	if ((door_close_se = LoadSoundMem("Resource/Sounds/SE/Stage/door_close.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/door_close.wav";
	}

	if ((press_the_button_se = LoadSoundMem("Resource/Sounds/SE/Stage/press_the_button.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/press_the_button.wav";
	}

	if ((switch_se = LoadSoundMem("Resource/Sounds/SE/Stage/switch.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/switch.wav";
	}

	if ((walk_puddle_se = LoadSoundMem("Resource/Sounds/SE/Stage/walk_puddle.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/walk_puddle.wav";
	}

	if ((manhole_opened_se = LoadSoundMem("Resource/Sounds/SE/Stage/manhole_opened.wav")) == -1) {
		throw "Resource/Sounds/SE/Stage/manhole_opened.wav";
	}

	ELEMENT_DATA data;
	for (int i = 0; i < map_data.size(); i++)
	{
		for (int j = 0; j < map_data.at(0).size(); j++)
		{
			int search_vector = 1;
			int button_num_1 = 0;
			int button_num_2 = 0;
			int door_num = 0;
			switch (map_data.at(i).at(j))
			{
				//ボタン横
			case 61:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25);
				data.y = static_cast<float>(i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;

				//ボタンとドアの連携番号を格納
				while (button_num_1 < button_info.size()) {
					if (button_info.at(button_num_1).at(0) == i && button_info.at(button_num_1).at(1) == j) {
						data.pair_num = button_info.at(button_num_1).at(2);
						break;
					}
					button_num_1++;
				}

				button.push_back(data);
				break;

				//ボタン(下)
			case 62:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 2;
				data.flg = false;
				data.animtimer = 0;

				//ボタンとドアの連携番号を格納
				while (button_num_2 < button_info.size()) {
					if (button_info.at(button_num_2).at(0) == i && button_info.at(button_num_2).at(1) == j) {
						data.pair_num = button_info.at(button_num_2).at(2);
						break;
					}
					button_num_2++;

				}

				button.push_back(data);
				break;


				//ボタン(ones)下
			case 63:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25);
				data.type = 3;
				data.flg = false;
				data.animtimer = 0;
				button.push_back(data);
				break;

				//閉まっているドアの下
			case 66:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;

				//ボタンとドアの連携番号を格納
				while (door_num < door_info.size()) {
					if (door_info.at(door_num).at(0) == i && door_info.at(door_num).at(1) == j) {
						data.pair_num = door_info.at(door_num).at(2);
						break;
					}
					door_num++;
				}

				door.push_back(data);
				break;

				//マンホールの蓋
			case 68:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.lift_init_x = j;		//配列データ
				data.lift_init_y = i;		//配列データ
				data.pair_num = 0;			//演算完了フラグ
				data.lift_wait_time = 0;	//中間地点の数カウント用
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;
				data.lift_wait_time = 0;	//暗闇エフェクト
				manhole.push_back(data);
				break;

				//マンホール(中間)
			case 69:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.lift_init_x = j;		//配列データ
				data.lift_init_y = i;		//配列データ
				data.pair_num = 0;			//演算完了フラグ
				data.type = 2;
				data.flg = false;
				data.animtimer = 0;
				manhole.push_back(data);
				break;

				//マンホール(出口)
			case 97:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.lift_init_x = j;		//配列データ
				data.lift_init_y = i;		//配列データ
				data.lift_wait_time = 0;	//中間地点の数カウント用
				data.type = 3;
				data.flg = false;
				data.animtimer = 0;
				manhole.push_back(data);
				break;

				//酸性雨の水たまり(左端)
			case 74:
			case 75:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 1;
				data.animtimer = 0;
				data.flg = false;
				acidrain_puddles.push_back(data);
				break;

				//酸性雨の水たまり(中央)
			case 76:
			case 77:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 2;
				data.animtimer = 0;
				data.flg = false;
				acidrain_puddles.push_back(data);
				break;

				//酸性雨の水たまり(右端)
			case 78:
			case 79:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 3;
				data.animtimer = 0;
				data.flg = false;
				acidrain_puddles.push_back(data);
				break;

				//フック
			case 72:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				hook.push_back(data);
				break;

				//動く床(縦移動)
			case 51:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.lift_init_x = data.x;
				data.lift_init_y = data.y;
				data.lift_vector_x = 0;
				data.lift_vector_y = 0;
				data.lift_wait_time = 0;
				//ゴール位置を格納
				for (int lift_pos = i + 1; lift_pos >= 0 && lift_pos < map_data.size(); lift_pos += search_vector) {
					if (map_data.at(lift_pos).at(j) == 53) {
						data.lift_goal_x = static_cast<float>((j * MAP_CEllSIZE));
						data.lift_goal_y = static_cast<float>((lift_pos * MAP_CEllSIZE));
						break;
					}
					else if (map_data.at(lift_pos).at(j) > 0 && (map_data.at(lift_pos).at(j) < 21 || map_data.at(lift_pos).at(j) > 24)) {
						if (search_vector < 0) { break; }
						lift_pos = i - 1;
						search_vector = -1;
						continue;
					}
				}
				data.type = 1;
				data.flg = true;
				data.animtimer = 0;
				lift.push_back(data);
				break;
				//動く床(横移動)
			case 52:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.lift_init_x = data.x;
				data.lift_init_y = data.y;
				data.lift_vector_x = 0;
				data.lift_vector_y = 0;
				data.lift_wait_time = 0;
				//ゴール位置を格納
				for (int lift_pos = j + 1; lift_pos >= 0 && lift_pos < map_data.at(0).size(); lift_pos += search_vector) {
					if (map_data.at(i).at(lift_pos) == 54) {
						data.lift_goal_x = static_cast<float>((lift_pos * MAP_CEllSIZE));
						data.lift_goal_y = static_cast<float>((i * MAP_CEllSIZE));
						break;
					}
					if (map_data.at(i).at(lift_pos) > 0 && (map_data.at(i).at(lift_pos) < 21 || map_data.at(i).at(lift_pos) > 24)) {
						if (search_vector < 0) { break; }
						lift_pos = j - 1;
						search_vector = -1;
						continue;
					}
				}
				data.type = 2;
				data.flg = true;
				data.animtimer = 0;
				lift.push_back(data);
				break;

			default:
				break;
			}


		}

	}

	player_map_x = 0;
	player_map_y = 0;
	keep_pushing = false;

	player_state = 0;
	guid_timer = 0;
	acidrain_puddles_anitimer = 0;

	hook_flg = false;

	//SE
	ChangeVolumeSoundMem(Option::GetSEVolume(), door_close_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), press_the_button_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), switch_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), walk_puddle_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), manhole_opened_se);

}

/// <summary>
/// デストラクタ
/// </summary>
ELEMENT::~ELEMENT() {
	DeleteFontToHandle(guid_font);
	DeleteSoundMem(door_close_se);
	DeleteSoundMem(press_the_button_se);
	DeleteSoundMem(switch_se);
	DeleteSoundMem(walk_puddle_se);
	DeleteSoundMem(manhole_opened_se);

	//逆に1MB程メモリ喰うのでやらない事
	/*hook.clear();
	hook.shrink_to_fit();*/

	underground_effects = 0;
}

/// <summary>
/// 描画
/// </summary>
void ELEMENT::Draw(STAGE* stage, PLAYER* player) {
	//DrawFormatString(100, 50, 0xffffff, "%2f %2f", scroll_x, scroll_y);
	//DrawFormatString(100,50,0xffffff,"map_data:%d",map_data[int(player_map_y) / MAP_CEllSIZE + 1][int(player_map_x) / MAP_CEllSIZE]);
	//static int animtimer = 0;
	//printfDx("%d", animtimer);
	//DrawFormatString(200, 100, 0xFFFFFF, "acidrain_puddles.x%f\acidrain_puddles.y%f", acidrain_puddles[1].x, acidrain_puddles[1].y);
	//DrawFormatString(200, 200, 0xFFFFFF, "x%f\ny%f", player_map_x, player_map_y);
	//デバッグ用



	//フックのガイド表示
	for (int i = 0; i < hook.size(); i++) {
		if (hook[i].flg == true) {
			if (player_state != static_cast<int>(PLAYER_MOVE_STATE::HOOK)) {
				if (guid_timer < 50) {
					DrawCircleAA(hook[i].x + stage->GetScrollX(), hook[i].y + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
					DrawStringToHandle(static_cast<int>(hook[i].x + stage->GetScrollX()) - 7, static_cast<int>(hook[i].y + stage->GetScrollY()) - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
				}
				else {
					DrawCircleAA(hook[i].x + stage->GetScrollX(), hook[i].y + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
					DrawStringToHandle(static_cast<int>(hook[i].x + stage->GetScrollX()) - 7, static_cast<int>(hook[i].y + stage->GetScrollY()) - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
				}
			}
		}
	}

	//ボタン
	for (int i = 0; i < button.size(); i++) {

		if (button[i].type == 2) {

			if (button[i].flg == false) {
				DrawOvalAA(button[i].x + stage->GetScrollX(), button[i].y + stage->GetScrollY() + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
			}
			if (button[i].flg == true && button[i].animtimer < 30) {
				SetDrawArea(static_cast<int>(button[i].x + stage->GetScrollX()) - MAP_CEllSIZE / 2, static_cast<int>( button[i].y + stage->GetScrollY()) - MAP_CEllSIZE / 2, static_cast<int>( button[i].x + stage->GetScrollX()) + MAP_CEllSIZE / 2, static_cast<int>(button[i].y + stage->GetScrollY()) + MAP_CEllSIZE / 2);
				DrawOvalAA(button[i].x + stage->GetScrollX(), button[i].y + stage->GetScrollY() + 30 + button[i].animtimer, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
				SetDrawAreaFull();
			}

			DrawGraphF(button[i].x + stage->GetScrollX() - MAP_CEllSIZE / 2, button[i].y + stage->GetScrollY() - MAP_CEllSIZE / 2, block_image1[61], TRUE);
		}
	}

	//動く床
	for (int i = 0; i < lift.size(); i++) {
		//DrawFormatString(100+i*100, 400, 0xffffff, "%d", lift[i].lift_vector_y);
		//DrawFormatString(100 + i * 100, 400, 0xffffff, "%f", lift[i].x);
		/*DrawFormatString(100+i*100, 400, 0xffffff, "%f", lift_goal_X[i].x);
		DrawBox(lift_goal_X[i].x + stage->GetScrollX(), lift_goal_X[i].y + stage->GetScrollY(), lift_goal_X[i].x + MAP_CEllSIZE * 2 + stage->GetScrollX(), lift_goal_X[i].y + MAP_CEllSIZE / 2 + stage->GetScrollY(),0xff0000,FALSE);*/
		DrawExtendGraphF(lift[i].x + stage->GetScrollX(), lift[i].y - 31 + stage->GetScrollY(), lift[i].x + LIFT_SIZE + stage->GetScrollX(), lift[i].y + 70 + stage->GetScrollY(), block_image1[51], TRUE);
	}

	//ドア
	for (int i = 0; i < door.size(); i++) {
		//if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (door[i].flg == true) {

		}
	}

	//マンホール
	for (int i = 0; i < manhole.size(); i++) {

		if (manhole[i].type == 1) {
			if (manhole[i].flg == true) {

				if (manhole[i].animtimer < 20) {
					DrawModiGraphF(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY() - manhole[i].animtimer * (288 / 20),
						manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE, manhole[i].y + stage->GetScrollY() - manhole[i].animtimer * (288 / 20),
						manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE, manhole[i].y + stage->GetScrollY() + MAP_CEllSIZE,
						manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY() + MAP_CEllSIZE,
						block_image1[67], TRUE);
				}
				else {
					DrawGraphF(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY(), block_image1[97], TRUE);
				}
			}
			else {
				DrawGraphF(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY(), block_image1[67], TRUE);

				//マンホールのガイド表示
				if (guid_timer < 50) {
					DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
					DrawStringToHandle(static_cast<int>(manhole[i].x + stage->GetScrollX()) - 7 + MAP_CEllSIZE / 2, static_cast<int>(manhole[i].y + MAP_CEllSIZE + stage->GetScrollY()) - 20 - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
				}
				else {
					DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
					DrawStringToHandle(static_cast<int>(manhole[i].x + stage->GetScrollX()) - 7 + MAP_CEllSIZE / 2, static_cast<int>(manhole[i].y + MAP_CEllSIZE + stage->GetScrollY()) - 20 - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
				}
			}
		}

		if (manhole[i].type == 3) {
			if (manhole[i].flg == true) {
				DrawGraphF(manhole[i].x + stage->GetScrollX() - MAP_CEllSIZE / 2, manhole[i].y + stage->GetScrollY() - MAP_CEllSIZE / 2, block_image1[97], TRUE);
			}
			else {
				DrawGraphF(manhole[i].x + stage->GetScrollX() - MAP_CEllSIZE / 2, manhole[i].y + stage->GetScrollY() - MAP_CEllSIZE / 2, block_image1[67], TRUE);
			}
			//マンホールのガイド表示

			int x = static_cast<int>(manhole[i].lift_init_x) * MAP_CEllSIZE + MAP_CEllSIZE / 2;
			int y = static_cast<int>(manhole[i].lift_init_y) * MAP_CEllSIZE + MAP_CEllSIZE / 2;

			if (guid_timer < 50) {
				DrawCircleAA(x + stage->GetScrollX(), y - 20 + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
				DrawStringToHandle(x + static_cast<int>(stage->GetScrollX()) - 7, y + static_cast<int>(stage->GetScrollY()) - 20 - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
			}
			else {
				DrawCircleAA(x + stage->GetScrollX(), y - 20 + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
				DrawStringToHandle(x + static_cast<int>(stage->GetScrollX()) - 7, y + static_cast<int>(stage->GetScrollY()) - 20 - 12, Option::GetInputMode() ? "B" : "A", Option::GetInputMode() ? B_COLOR : A_COLOR, guid_font, 0xFFFFFF);
			}
		}
	}


	//酸性雨の水たまり
	for (int i = 0; i < acidrain_puddles.size(); i++) {

		if (stage_name == "Stage02") { DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[7], TRUE); }
		else if (stage_name == "Stage03") { DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[11], TRUE); }
		else { DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[3], TRUE); }

		switch (acidrain_puddles[i].type)
		{
		case 1:		//左端
			if (acidrain_puddles_anitimer > 5) {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[74], TRUE);
			}
			else {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[73], TRUE);
			}
			break;

		case 2:		//中央
			if (acidrain_puddles_anitimer > 5) {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[76], TRUE);
			}
			else {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[75], TRUE);
			}
			break;

		case 3:		//右端
			if (acidrain_puddles_anitimer > 5) {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[78], TRUE);
			}
			else {
				DrawGraphF(acidrain_puddles[i].x + stage->GetScrollX(), acidrain_puddles[i].y + stage->GetScrollY(), block_image1[77], TRUE);
			}
			break;
		default:
			break;
		}
	}


	//地下エフェクト
	if (underground_effects != 0) {
		DrawCircleAA(player->GetPlayerX(), player->GetPlayerY(), 1200.0F - underground_effects * 3, 32, 0x000000, FALSE, 1200.0F);

	}

}

/// <summary>
/// 更新
/// </summary>
void ELEMENT::Update(PLAYER* player, STAGE* stage) {

	ChangeVolumeSoundMem(Option::GetSEVolume(), door_close_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), press_the_button_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), switch_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), walk_puddle_se);
	ChangeVolumeSoundMem(Option::GetSEVolume(), manhole_opened_se);

	player_state = static_cast<int>(player->GetPlayerMoveState());
	//プレイヤーのマップ内座標を設定
	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY() - stage->GetScrollY());

	Button(player);
	Door(stage);
	Lift(player, stage);
	Manhole(player, stage);
	Acidrain_puddles(player);

	if (guid_timer < 100) { guid_timer++; }
	else { guid_timer = 0; }

	Hook_Distance(player, stage);	//フックのガイド表示用距離計算
}

/// <summary>
/// 3種類のボタンの処理
/// </summary>
void ELEMENT::Button(PLAYER* player) {


	for (int i = 0; i < button.size(); i++) {
		if (button[i].flg == true)button[i].animtimer++;
		if (button[i].animtimer > 180 && keep_pushing == false) {
			button[i].animtimer = 0;
			button[i].flg = false;
		}

		if (button[i].type == 1) {		//横ボタン
			int max_ball_num = player->GetThrowCnt();
			for (int ball_num = 0; ball_num < max_ball_num; ball_num++) {
				if ((player->GetThrowSlime(ball_num).GetThrowX() >= button[i].x - MAP_CEllSIZE / 2 + 33) && (player->GetThrowSlime(ball_num).GetThrowX() <= button[i].x + MAP_CEllSIZE / 2 - 30) && (player->GetThrowSlime(ball_num).GetThrowY() >= button[i].y - MAP_CEllSIZE / 2) && (player->GetThrowSlime(ball_num).GetThrowY() <= button[i].y + MAP_CEllSIZE / 2)) {
					//デバッグ
					//printfDx("1番に入ってるよ！");
					if (CheckSoundMem(press_the_button_se) == FALSE)PlaySoundMem(press_the_button_se, DX_PLAYTYPE_BACK, TRUE);
					/*if (i < door.size() && i >= 0) {
						int j = i + 1;
						door[i].flg = true;
					}*/
					int k = 0;
					while (k < door.size()) {
						if (button[i].pair_num == door[k].pair_num) {
							door[k].flg = true;
							break;
						}
						k++;
					}

				}
			}
		}
		if (button[i].type == 2) {	//ボタン
			bool ball_flg = false;	//ボールの当たり判定フラグ
			for (int ball_num = 0; ball_num < player->GetThrowCnt(); ball_num++) {
				if ((player->GetThrowSlime(ball_num).GetThrowX() >= button[i].x - MAP_CEllSIZE / 2 + 10) && (player->GetThrowSlime(ball_num).GetThrowX() <= button[i].x + MAP_CEllSIZE / 2 - 10) && (player->GetThrowSlime(ball_num).GetThrowY() >= button[i].y - MAP_CEllSIZE / 2) && (player->GetThrowSlime(ball_num).GetThrowY() <= button[i].y + MAP_CEllSIZE / 2)) {
					ball_flg = true;
				}
				else { keep_pushing = false; }
			}

			if ((ball_flg == true) || ((player_map_x >= button[i].x - MAP_CEllSIZE + 25) && (player_map_x <= button[i].x + MAP_CEllSIZE - 25) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2))) {
				//デバッグ
				//printfDx("2番に入ってるよ！");
				// 当たり判定バグる為一時停止
				//if(ball_flg == false)player->SetPlayerY(button[i].y - 6.0f);
				if (button[i].flg == false) {
					if (CheckSoundMem(switch_se) == FALSE)PlaySoundMem(switch_se, DX_PLAYTYPE_BACK, TRUE);
				}
				keep_pushing = true; //押し続けている
				button[i].flg = true;		//ボタンを押した

				/*if (i < door.size() && i >= 0) {
					int j = i - 1;
					door[i].flg = true;
				}*/
				int l = 0;
				while (l < door.size()) {
					if (button[i].pair_num == door[l].pair_num) {
						door[l].flg = true;
						break;
					}
					l++;
				}
			}
			else { keep_pushing = false; }
		}

		//一回限り
		if (button[i].type == 3) {	//Onecボタン
			if ((player_map_x >= button[i].x - MAP_CEllSIZE / 2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
				//デバッグ
				//printfDx("3番に入ってるよ！");
			}
		}
	}
}

/// <summary>
/// ドアの処理
/// </summary>
void ELEMENT::Door(STAGE* stage) {
	for (int i = 0; i < door.size(); i++) {
		if (door[i].flg == true) {
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			stage->SetMapData(y, x, 64);
			stage->SetMapData(y - 1, x, 65);
		}

		if (door[i].flg==true&&(player_map_x >= door[i].x + MAP_CEllSIZE) && (player_map_x <= door[i].x + MAP_CEllSIZE + 5) && (player_map_y >= door[i].y - MAP_CEllSIZE *1.5) && (player_map_y <= door[i].y + MAP_CEllSIZE / 2)) {
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			stage->SetMapData(y, x, 66);
			stage->SetMapData(y - 1, x, 67);
			if (CheckSoundMem(door_close_se) == FALSE)PlaySoundMem(door_close_se, DX_PLAYTYPE_BACK, TRUE);
			door[i].flg = false;
		}
	}
}

/// <summary>
/// 動く床の処理
/// </summary>
void ELEMENT::Lift(PLAYER* player, STAGE* stage) {
	for (int i = 0; i < lift.size(); i++) {
		if (lift[i].flg) {
			//動く床(縦)の動き
			if (lift[i].type == 1) {
				if (lift[i].y < lift[i].lift_goal_y) { lift[i].lift_vector_y = 1; }
				else if (lift[i].y > lift[i].lift_goal_y) { lift[i].lift_vector_y = -1; }
				else { lift[i].lift_vector_y = 0; }
				if (lift[i].y != lift[i].lift_goal_y) {
					lift[i].y += lift[i].lift_vector_y * 4;
				}
				else {
					lift[i].lift_wait_time++;
					if (lift[i].lift_wait_time == 60) {
						float work = lift[i].lift_goal_y;
						lift[i].lift_goal_y = lift[i].lift_init_y;
						lift[i].lift_init_y = work;
						lift[i].lift_wait_time = 0;
					}
				}
			}
			//動く床(横)の動き
			else if (lift[i].type == 2) {
				if (lift[i].x < lift[i].lift_goal_x) { lift[i].lift_vector_x = 1; }
				else if (lift[i].x > lift[i].lift_goal_x) { lift[i].lift_vector_x = -1; }
				else { lift[i].lift_vector_x = 0; }

				if (lift[i].x != lift[i].lift_goal_x) {
					lift[i].x += lift[i].lift_vector_x * 4;
				}
				else {
					lift[i].lift_wait_time++;
					if (lift[i].lift_wait_time == 60) {
						float work = lift[i].lift_goal_x;
						lift[i].lift_goal_x = lift[i].lift_init_x;
						lift[i].lift_init_x = work;
						lift[i].lift_wait_time = 0;
					}
				}
			}
		}
	}

}

/// <summary>
/// 動く床の当たり判定
/// </summary>
bool ELEMENT::HitLift(PLAYER* player) {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x + player->GetPlayerScale() * 25 >= lift[i].x && player_map_x - player->GetPlayerScale() * 25 <= lift[i].x + LIFT_SIZE
			&& player_map_y >= lift[i].y - MAP_CEllSIZE && player_map_y <= lift[i].y + 10 && player->GetPlayerMoveState() != PLAYER_MOVE_STATE::JUMP
			/*&& (map_data[int(player_map_y) / MAP_CEllSIZE + 1][int(player_map_x) / MAP_CEllSIZE] == 0 || map_data[int(player_map_y) / MAP_CEllSIZE + 1][int(player_map_x) / MAP_CEllSIZE] >= 51)*/) {

			player->SetPlayerY(lift[i].y - MAP_CEllSIZE / 2);

			player->SetPlayerY(lift[i].y - MAP_CEllSIZE / 2 + lift[i].lift_vector_y * 4);
			player->SetPlayerX(player->GetPlayerX() + lift[i].lift_vector_x * 4);
			return true;
		}
	}
	return false;
}


/// <summary>
/// マンホールの処理
/// </summary>
void ELEMENT::Manhole(PLAYER* player, STAGE* stage) {
	for (int i = 0; i < manhole.size(); i++) {
		if (manhole[i].flg == true && manhole[i].animtimer < 20)manhole[i].animtimer++;
		if (manhole[i].animtimer > 20) {
			//manhole[i].animtimer = 0;
			//manhole[i].flg = false;
		}
		if (manhole[i].type == 1) {

			int mapdata_down = stage->GetMapData(manhole[i].lift_init_y + 1, manhole[i].lift_init_x);

			//中間地点を抜ける下の座標を取得する
			//中間地点の時にループ
			while (mapdata_down == 69 && manhole[i].pair_num == 0)
			{
				manhole[i].lift_init_y++;
				mapdata_down = stage->GetMapData(manhole[i].lift_init_y, manhole[i].lift_init_y);
			}

			//演算完了フラグ
			manhole[i].pair_num = 1;

			if ((player_map_x >= manhole[i].x) && (player_map_x <= manhole[i].x + MAP_CEllSIZE) && (player_map_y <= manhole[i].y + MAP_CEllSIZE) && (player_map_y >= manhole[i].y)) {
				if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) {
					stage->SetTemporary_Hit(999);
					manhole[i].flg = true;
				}

				if (manhole[i].flg == false) {
					stage->SetTemporary_Hit(69);
				}

				if (manhole[i].animtimer == 19 && !CheckSoundMem(manhole_opened_se))PlaySoundMem(manhole_opened_se, DX_PLAYTYPE_BACK, TRUE);

				if (manhole[i].animtimer >= 20) {
					int x = floor(manhole[i].x / MAP_CEllSIZE);
					int y = floor(manhole[i].y / MAP_CEllSIZE);
					stage->SetMapData(y, x, 98);
				}
			}

			else if ((manhole[i].flg == true) && (player_map_x >= manhole[i].x - MAP_CEllSIZE * 4) && (player_map_x <= manhole[i].x + MAP_CEllSIZE * 5) && (player_map_y > manhole[i].y + MAP_CEllSIZE)) {
				if (underground_effects < 120) {
					underground_effects += 2;
				}

				const int speed = manhole[i].lift_wait_time * 2;

				if ((manhole[i].flg == true) && player->GetPlayerY() + -stage->GetScrollY() < manhole[i].y) {
					player->SetGravity(false);
					stage->SetScrollY(stage->GetScrollY() - speed);
					player->SetPlayerY((player->GetPlayerY() - stage->GetScrollY()) + speed);
					//printfDx("遅くしています\n");
				}
			}

		}

		//中間地点
		if (manhole[i].type == 2) {
			if ((player_map_x >= manhole[i].x) && (player_map_x <= manhole[i].x + MAP_CEllSIZE) && (player_map_y <= manhole[i].y + MAP_CEllSIZE) && (player_map_y >= manhole[i].y)) {
				//プレイヤーの落下速度を遅くする
				//player->SetPlayerY(player->GetPlayerY() - 3.0f);
				//player->SetGravity(true);
				player->SetVisible(false);
			}
			else {
				//player->SetGravity(true);
			}


			int mapdata_down = stage->GetMapData(manhole[i].lift_init_y, manhole[i].lift_init_x);

			//中間地点を抜ける下の座標を取得する
			//中間地点の時にループ
			while (mapdata_down == 69 && manhole[i].pair_num == 0)
			{
				manhole[i].lift_init_y++;
				mapdata_down = stage->GetMapData(manhole[i].lift_init_y, manhole[i].lift_init_y);
			}

			//演算完了フラグ
			manhole[i].pair_num = 1;

			int manhole_down_y;
			manhole_down_y = manhole[i].lift_init_y * MAP_CEllSIZE + MAP_CEllSIZE;

			//中間地点の一番下に行った時
			if ((player_map_x >= manhole[i].x) && (player_map_x <= manhole[i].x + MAP_CEllSIZE) && (player_map_y <= manhole_down_y + MAP_CEllSIZE) && (player_map_y >= manhole_down_y)) {
				player->SetVisible(true);
				player->SetGravity(true);
			}
		}

		//出口
		if (manhole[i].type == 3) {

			int mapdata = stage->GetMapData(manhole[i].lift_init_y + 1, manhole[i].lift_init_x);

			//中間地点の時にループ
			while (mapdata == 69)
			{
				manhole[i].lift_init_y++;
				mapdata = stage->GetMapData(manhole[i].lift_init_y, manhole[i].lift_init_x);

				//中間の数をカウント
				manhole[i].lift_wait_time++;
			}

			//マンホールの出口の左端から右端までのx座標かつマンホールの出口よりも下にいる場合
			if ((player_map_x >= manhole[i].x - MAP_CEllSIZE / 2) && (player_map_x <= manhole[i].x + MAP_CEllSIZE / 2) && (player_map_y > manhole[i].y)) {
				if (PAD_INPUT::GetNowKey() == (Option::GetInputMode() ? XINPUT_BUTTON_B : XINPUT_BUTTON_A)) { manhole[i].flg = true; }


				//Bボタンを押してflgがtrueになった時
				if (manhole[i].flg == true) {
					//player->SetGravity(false);
					//player->SetVisible(true);
					const int speed = manhole[i].lift_wait_time * 4;

					if (player->GetPlayerY() + -stage->GetScrollY() > manhole[i].y) {
						stage->SetScrollY(stage->GetScrollY() + speed);
						player->SetPlayerY((player->GetPlayerY() - stage->GetScrollY()) - speed);
					}

					if (underground_effects > 0) {
						underground_effects -= manhole[i].lift_wait_time + 1;
					}
					//SetGravityを有効化するとGetterの値が変わらない
					//printfDx("%f\n", player->GetPlayerY());
					if ((player->GetPlayerY() + -stage->GetScrollY()) < manhole[i].y) {
						if (!CheckSoundMem(manhole_opened_se)) { PlaySoundMem(manhole_opened_se, DX_PLAYTYPE_BACK, TRUE); }
						//player->SetVisible(false);
						//一時的な当たり判定をつける。
						stage->SetTemporary_Hit(69);
						//player->SetGravity(true);
						player->SetVisible(true);
						manhole[i].flg = false;
					}
				}
			}
		}
	}
}

/// <summary>
/// 酸性雨の水たまりの処理
/// </summary>
void ELEMENT::Acidrain_puddles(PLAYER* player) {
	if (acidrain_puddles_anitimer < 10) { acidrain_puddles_anitimer++; }
	else { acidrain_puddles_anitimer = 0; }
	for (int i = 0; i < acidrain_puddles.size(); i++) {

		if (acidrain_puddles[i].flg == false)acidrain_puddles[0].animtimer++;
		if (acidrain_puddles[0].animtimer > 120) {
			acidrain_puddles[0].animtimer = 0;
			acidrain_puddles[i].flg = true;
		}
		//酸性雨の水たまり
		if ((player_map_x >= acidrain_puddles[i].x) && (player_map_x <= acidrain_puddles[i].x + MAP_CEllSIZE) && (player_map_y >= acidrain_puddles[i].y - MAP_CEllSIZE / 2) && (player_map_y <= acidrain_puddles[i].y)) {
			if (CheckSoundMem(walk_puddle_se) == FALSE && acidrain_puddles[0].animtimer % 90 == 0)PlaySoundMem(walk_puddle_se, DX_PLAYTYPE_BACK, TRUE);
			if (acidrain_puddles[i].flg == true) {
				player->SetLife(player->GetLife() - 1);
				acidrain_puddles[i].flg = false;
			}
		}
	}
}

/// <summary>
/// フックのガイド表示用距離計算
/// </summary>
void ELEMENT::Hook_Distance(PLAYER* player, STAGE* stage) {
	float min_distance = HOOK_MAX_DISTANCE + 80;
	//フックのガイド表示用
	//フックまでの距離計算
	for (int i = 0; i < hook.size(); i++) {
		float diff_x = hook[i].x - (player->GetPlayerX() - stage->GetScrollX());
		float diff_y = hook[i].y - (player->GetPlayerY() - stage->GetScrollY());
		float distance = sqrtf(diff_x * diff_x + diff_y * diff_y);
		//距離が最短距離より近いとき
		if (distance <= min_distance) { min_distance = distance; hook[i].flg = true; }
		else { hook[i].flg = false; }
	}
}