
#include "Element.h"
#include "PLAYER.h"

ELEMENT::ELEMENT(const char* stage_name) : STAGE(stage_name){

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

	ELEMENT_DATA data;
	DEFAULT_POS default_data;
	for (int i = 0; i < map_data.size(); i++)
	{
		for (int j = 0; j < map_data.at(0).size(); j++)
		{
			switch (map_data.at(i).at(j))
			{
				//ボタン横
			case 61:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25);
				data.y = static_cast<float>(i * MAP_CEllSIZE + MAP_CEllSIZE / 2) ;
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;
				button.push_back(data);
				break;
					
				//ボタン(下)
			case 62:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 2;
				data.flg = false;
				data.animtimer = 0;
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
				door.push_back(data);
				break;

				//マンホールの蓋
			case 68:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;
				manhole.push_back(data);
				break;

				//マンホール(中間)
			case 69:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 2;
				data.flg = false;
				data.animtimer = 0;
				manhole.push_back(data);
				break;

				//マンホール(出口)
			case 97:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 3;
				data.flg = false;
				data.animtimer = 0;
				manhole.push_back(data);
				break;

				//酸性雨の水たまり
			case 74:
			case 75:
			case 76:
			case 77:
			case 78:
			case 79:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 1;
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
				default_data.x = data.x;
				default_data.y = data.y;
				data.type = 1;
				data.flg = false;
				data.animtimer = 0;
				lift.push_back(data);
				lift_default_pos.push_back(default_data);
				break;
				//動く床(横移動)
			case 52:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				default_data.x = data.x;
				default_data.y = data.y;
				data.type = 2;
				data.flg = false;
				data.animtimer = 0;
				lift.push_back(data);
				lift_default_pos.push_back(default_data);
				break;

				//動く床(ゴール)
			case 53:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 0;
				data.flg = false;
				data.animtimer = 0;
				lift_goal.push_back(data);
				break;

		
			default:
				break;
			}

			
		}
			
	}

	player_map_x = 0;
	player_map_y = 0;
	lift_vector = 1;
	lift_speedY = 1;
	lift_speedX = 3;
	keep_pushing = false;

	player_state = 0;
	guid_timer = 0;
	
}

ELEMENT::~ELEMENT() {
	hook.clear();
	hook.shrink_to_fit();
}

void ELEMENT::Draw(STAGE* stage)  {
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
					DrawStringToHandle(hook[i].x + stage->GetScrollX() - 7, hook[i].y + stage->GetScrollY() - 12, "B", 0xEB7415, guid_font, 0xFFFFFF);
				}
				else {
					DrawCircleAA(hook[i].x + stage->GetScrollX(), hook[i].y + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
					DrawStringToHandle(hook[i].x + stage->GetScrollX() - 7, hook[i].y + stage->GetScrollY() - 12, "B", 0xFF6638, guid_font, 0xFFFFFF);
				}
			}
		}
	}

	//ボタン
	for (int i = 0; i < button.size(); i++) {
		if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + stage->GetScrollX(), button[i].y + stage->GetScrollY() + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (button[i].type == 2 && button[i].flg == true) { 
			DrawOvalAA(button[i].x + stage->GetScrollX(), button[i].y + stage->GetScrollY() + 30 + button[i].animtimer, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		}
	}

	//動く床
	for (int i = 0; i < lift.size(); i++) {
		DrawExtendGraph(lift[i].x + stage->GetScrollX(), lift[i].y - 31 + stage->GetScrollY(), lift[i].x + LIFT_SIZE + stage->GetScrollX(), lift[i].y + 70 + stage->GetScrollY(), block_image1[51], TRUE);		
	}

	//ドア
	for (int i = 0; i < door.size(); i++) {
		//if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (door[i].flg == true) {
			//エフェクト
			DrawOvalAA(door[i].x + stage->GetScrollX(), door[i].y + stage->GetScrollY() + 30 + door[i].animtimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
		}
	}

	//マンホール
	for (int i = 0; i < manhole.size(); i++) {
		if (manhole[i].type != 2) {
			if (manhole[i].flg == true) {
				if (manhole[i].type == 1) {

					if (manhole[i].animtimer < 240) {
						DrawModiGraph(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY() - manhole[i].animtimer * 1.2,
							manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE, manhole[i].y + stage->GetScrollY() - manhole[i].animtimer * 1.2,
							manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE, manhole[i].y + stage->GetScrollY() + MAP_CEllSIZE,
							manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY() + MAP_CEllSIZE,
							block_image1[67], TRUE);
					}
					else {
						DrawGraph(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY(), block_image1[97], TRUE);
					}
				}
				//DrawOvalAA(manhole[i].x + scroll_x, manhole[i].y + scroll_y + 30 + manhole[i].animtimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);

			}
			else {
				DrawGraph(manhole[i].x + stage->GetScrollX(), manhole[i].y + stage->GetScrollY(), block_image1[67], TRUE);

				//マンホールのガイド表示
				if (guid_timer < 50) {
					DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
					DrawStringToHandle(manhole[i].x + stage->GetScrollX() - 7 + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE + stage->GetScrollY() - 20 - 12, "B", 0xEB7415, guid_font, 0xFFFFFF);
				}
				else {
					DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
					DrawStringToHandle(manhole[i].x + stage->GetScrollX() - 7 + MAP_CEllSIZE / 2, manhole[i].y + MAP_CEllSIZE + stage->GetScrollY() - 20 - 12, "B", 0xFF6638, guid_font, 0xFFFFFF);
				}
			}

			if (manhole[i].type == 3) {
				//int map_x = manhole[i].x / MAP_CEllSIZE - MAP_CEllSIZE / 2;
				//int map_y = manhole[i].y / MAP_CEllSIZE - MAP_CEllSIZE / 2;
				////printfDx("%d\t\t\t%d", map_x, map_y);
				////int manhole_y;
				//for (int y = 0; manhole.size(); i++) { 
				//	//manhole_y = manhole[i].y + y;
				//	map_y = manhole[y].y / MAP_CEllSIZE - MAP_CEllSIZE / 2;
				//	if (map_data.at(map_y).at(map_x) != 69) { map_y++; }
				//	else { map_y = map_y * MAP_CEllSIZE + MAP_CEllSIZE / 2; }

				//}
				//if (guid_timer < 50) {
				//	DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, map_y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFFFFF, 1);
				//	DrawStringToHandle(manhole[i].x + stage->GetScrollX() - 7 + MAP_CEllSIZE / 2, map_y + MAP_CEllSIZE + stage->GetScrollY() - 20 - 12, "B", 0xEB7415, guid_font, 0xFFFFFF);
				//}
				//else {
				//	DrawCircleAA(manhole[i].x + stage->GetScrollX() + MAP_CEllSIZE / 2, map_y + MAP_CEllSIZE - 20 + stage->GetScrollY(), 15, 20, 0xFFCB33, 1);
				//	DrawStringToHandle(manhole[i].x + stage->GetScrollX() - 7 + MAP_CEllSIZE / 2, map_y + MAP_CEllSIZE + stage->GetScrollY() - 20 - 12, "B", 0xFF6638, guid_font, 0xFFFFFF);
				//}
			}
		}
	}
}

void ELEMENT::Update(PLAYER* player,STAGE*stage) {

	player_state = static_cast<int>(player->GetPlayerMoveState());
	//プレイヤーのマップ内座標を設定
	player_map_x = roundf(player->GetPlayerX() - stage->GetScrollX());
	player_map_y = floorf(player->GetPlayerY()- stage->GetScrollY());

	Button(player);
	Door(stage);
	Lift(player,stage);
	Manhole(player,stage);
	Acidrain_puddles(player);
	
	if (guid_timer < 100) { guid_timer++; }
	else { guid_timer = 0; }

	Hook_Distance(player,stage);	//フックのガイド表示用距離計算
}

/// <summary>
/// ボタンの処理
/// </summary>
void ELEMENT::Button(PLAYER* player) {


	for (int i = 0; i < button.size(); i++) {
		if(button[i].flg == true)button[i].animtimer++;
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
					if(i < door.size() && i >= 0){
						int j = i + 1;
						door[j].flg = true;
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

				if ((ball_flg == true) || ((player_map_x >= button[i].x - MAP_CEllSIZE + 25) && (player_map_x <= button[i].x + MAP_CEllSIZE-25 ) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2 ) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2))) {
					//デバッグ
					//printfDx("2番に入ってるよ！");
					// 当たり判定バグる為一時停止
					//if(ball_flg == false)player->SetPlayerY(button[i].y - 6.0f);
					if (button[i].flg == false) {
						if (CheckSoundMem(switch_se) == FALSE)PlaySoundMem(switch_se, DX_PLAYTYPE_BACK, TRUE);
					}
					keep_pushing = true; //押し続けている
					button[i].flg = true;		//ボタンを押した
					
					if (i < door.size() && i >= 0) {
						int j = i - 1;
						door[j].flg = true;
					}
					
				}else{ keep_pushing = false; }
			}

			//一回限り
			if (button[i].type == 3) {	//Onecボタン
				if ((player_map_x >= button[i].x-MAP_CEllSIZE/2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2)&& (player_map_y >= button[i].y - MAP_CEllSIZE / 2)&& (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
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
			door[i].animtimer++;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			stage->SetMapData(y, x, 64);
			stage->SetMapData(y - 1, x, 65);
		}
		//if (door[i].animtimer > 180) {
		//	door[i].animtimer = 0;
		//	door[i].flg = false;
		//}
		if ((player_map_x >= door[i].x +MAP_CEllSIZE) && (player_map_x <= door[i].x + MAP_CEllSIZE+5) && (player_map_y >= door[i].y - MAP_CEllSIZE / 2) && (player_map_y <= door[i].y + MAP_CEllSIZE / 2)) {
			door[i].animtimer = 0;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			stage->SetMapData(y, x, 66);
			stage->SetMapData(y - 1, x, 67);
			door[i].flg = false;
			if (CheckSoundMem(door_close_se) == FALSE)PlaySoundMem(door_close_se, DX_PLAYTYPE_BACK, TRUE);
			
		}
	}
}

/// <summary>
/// 動く床の処理
/// </summary>
void ELEMENT::Lift(PLAYER* player, STAGE* stage) {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x > lift[i].x - 1280 && player_map_x < lift[i].x + 1280) {
			lift[i].flg = true;
		}
		else { false; }
		if (lift[i].flg) {
			//動く床(縦)の動き
			if (lift[i].type == 1) {
				if (lift[i].y < lift_goal[i].y) { lift_vector = 1; }
				else { lift_vector = -1; }
				if (lift[i].y != lift_goal[i].y) {
					lift[i].y += lift_vector * lift_speedY;
				}
				else {
					float work = lift_goal[i].y;
					lift_goal[i].y = lift_default_pos[i].y;
					lift_default_pos[i].y = work;
				}
			}
			//動く床(横)の動き
			else if (lift[i].type == 2) {
				if (lift[i].x < lift_goal[i].x) { lift_vector = 1; }
				else if(lift[i].x > lift_goal[i].x) { lift_vector = -1; }

				if (lift[i].x != lift_goal[i].x) {
					lift[i].x += lift_vector * lift_speedX;
					if (HitLift(player)) {
						player->SetPlayerX(player->GetPlayerX() + lift_vector * lift_speedX);
					}
				}
				else {
					float work = lift_goal[i].x;
					lift_goal[i].x = lift_default_pos[i].x;
					lift_default_pos[i].x = work;
				}
			}
		}
	}

}

/// <summary>
/// プレイヤーと動く床の当たり判定
/// </summary>
bool ELEMENT::HitLift(PLAYER* player) {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x + player->GetPlayerScale() * 25 >= lift[i].x && player_map_x - player->GetPlayerScale() * 25 <= lift[i].x + LIFT_SIZE && player_map_y + MAP_CEllSIZE / 2 >= lift[i].y &&player_map_y<=lift[i].y+10
			/*&& (map_data[int(player_map_y) / MAP_CEllSIZE + 1][int(player_map_x) / MAP_CEllSIZE] == 0 || map_data[int(player_map_y) / MAP_CEllSIZE + 1][int(player_map_x) / MAP_CEllSIZE] >= 51)*/) {
			if (player->GetPlayerMoveState() != PLAYER_MOVE_STATE::JUMP) {
				player->SetPlayerY(lift[i].y - MAP_CEllSIZE / 2+1);
			}
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
		if (manhole[i].flg == true && manhole[i].animtimer < 240)manhole[i].animtimer++;
		if (manhole[i].animtimer > 240) {
			//manhole[i].animtimer = 0;
			//manhole[i].flg = false;
		}
		if (manhole[i].type == 1) {
			if ((player_map_x >= manhole[i].x) && (player_map_x <= manhole[i].x + MAP_CEllSIZE) && (player_map_y <= manhole[i].y + MAP_CEllSIZE) && (player_map_y >= manhole[i].y)) {
				if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { manhole[i].flg = true; }
				
				if (manhole[i].flg == false) {
					//player->SetPlayerY(player->GetPlayerY() - 2.0f);
				}

				if (manhole[i].animtimer >= 240) {
					int x = floor(manhole[i].x / MAP_CEllSIZE);
					int y = floor(manhole[i].y / MAP_CEllSIZE);
					stage->SetMapData(y, x, 98);
				}
			}
		}

		//中間地点
		if (manhole[i].type == 2) {
			if ((player_map_x >= manhole[i].x - MAP_CEllSIZE / 2) && (player_map_x <= manhole[i].x + MAP_CEllSIZE /2) && (player_map_y >= manhole[i].y - MAP_CEllSIZE / 2) && (player_map_y <= manhole[i].y + MAP_CEllSIZE / 2)) {
				//プレイヤーの落下速度を遅くする
				//player->SetPlayerY(player->GetPlayerY() - 3.0f);
			}
		}

		//出口
		if (manhole[i].type == 3) {
			if((player_map_x >= manhole[i].x - MAP_CEllSIZE /2) && (player_map_x <= manhole[i].x + MAP_CEllSIZE /2)/* && (player_map_y <= manhole[i].y)*/){
				if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_B) { manhole[i].flg = true; }
			if (manhole[i].flg == true) {

				if (player->GetPlayerY() <= manhole[i].y) {
					manhole[i].flg = false;
				}

				//if (manhole[i].animtimer == 180) {
					//player->SetPlayerX(manhole[i].x);
					player->SetPlayerY(manhole[i].y);
				//}
				//player->SetPlayerY(player->GetPlayerY() - 10.0f);
				//printfDx("%f",player->GetPlayerY());
			}
			//デバッグ
			//printfDx("入っています。");
			}
		}
	}
}

void ELEMENT::Acidrain_puddles(PLAYER* player) {

	for (int i = 0; i < acidrain_puddles.size(); i++) {

		if (acidrain_puddles[i].flg == false)acidrain_puddles[i].animtimer++;
		if (acidrain_puddles[i].animtimer > 120) {
			acidrain_puddles[i].animtimer = 0;
			acidrain_puddles[i].flg = true;
		}

		if (acidrain_puddles[i].type == 1) {	//酸性雨の水たまり
			if ((player_map_x >= acidrain_puddles[i].x - MAP_CEllSIZE / 2) && (player_map_x <= acidrain_puddles[i].x + MAP_CEllSIZE / 2) && (player_map_y >= acidrain_puddles[i].y - MAP_CEllSIZE) && (player_map_y <= acidrain_puddles[i].y + MAP_CEllSIZE)) {
				//デバッグ
				//printfDx("入ってるよ！");
				if (CheckSoundMem(walk_puddle_se) == FALSE && acidrain_puddles[i].animtimer % 90 == 0)PlaySoundMem(walk_puddle_se, DX_PLAYTYPE_BACK, TRUE);
				//player->SetPlayerY(acidrain_puddles[i].y + 1.5f);
				if (acidrain_puddles[i].flg == true) {
					player->SetLife(player->GetLife() - 1);
					//printfDx("残りライフ：%d",player->GetLife());		//デバッグ
					acidrain_puddles[i].flg = false;
				}
			}else{ acidrain_puddles[i].animtimer = 0; }
		}
	}
}

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