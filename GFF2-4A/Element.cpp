
#include "Element.h"
#include "PLAYER.h"

ELEMENT::ELEMENT() {

	ELEMENT_DATA data;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map_data[i][j])
			{
				//ボタン横
			case 61:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25;
				data.y = i * MAP_CEllSIZE + MAP_CEllSIZE / 2 ;
				data.type = 1;
				button.push_back(data);
				break;
					
				//ボタン(下)
			case 62:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 2;
				button.push_back(data);
				break;


				//ボタン(ones)下
			case 63:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25;
				data.type = 3;
				button.push_back(data);
				break;

				//ドア
			case 64:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				door.push_back(data);
				break;

				//トンネル(入口)
			case 65:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				tunnel.push_back(data);
				break;

				//トンネル(中間)
			case 66:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 2;
				tunnel.push_back(data);
				break;

				//トンネル(出口)
			case 67:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 3;
				tunnel.push_back(data);
				break;

				//酸
			case 68:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				acid.push_back(data);
				break;

				//フック
			case 75:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = i * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				hook.push_back(data);
				break;

				//動く床
			case 95:
				data.x = (j * MAP_CEllSIZE) + MAP_CEllSIZE/2;
				data.y = (i * MAP_CEllSIZE);
				data.type = 1;
				lift.push_back(data);
				break;

				//動く床(fast)
			case 96:
				data.x = (j * MAP_CEllSIZE);
				data.y = (i * MAP_CEllSIZE);
				data.type = 2;
				lift.push_back(data);
				break;

		
			default:
				break;
			}

			
		}
			
	}

	player_map_x = 0;
	player_map_y = 0;
	lift_speed = 1.0f;
}

void ELEMENT::Draw() const {
	//for (int i = 0; i < 9; i++) {
	//	DrawLine(0, i * 80, 1280, i * 80, 0xffffff);
	//}
	//for (int j = 0; j < 16; j++) {
	//	DrawLine(j * MAP_CEllSIZE, 0, j * MAP_CEllSIZE, 720, 0xffffff);
	//}

	
	static int animtimer = 0;
	//printfDx("%d", animtimer);
	printfDx("%f",lift[0].x);
	printfDx("%f", lift[0].y);
	//DrawFormatString(200, 100, 0xFFFFFF, "button.x%f\nbutton.y%f", button[1].x, button[1].y);
	DrawFormatString(200, 200, 0xFFFFFF, "x%f\ny%f", player_map_x, player_map_y);
	//デバッグ用
	//DrawFormatString(200, 250, 0xFFFFFF, "door.x%f\ndoor.y%f", door[0].x, door[0].y);
	//DrawFormatString(200, 300, 0xFFFFFF, "flg:%d", door[0].flg);
	//DrawFormatString(200, 350, 0xFFFFFF, ":%d", static_cast<int>((door[0].x / MAP_CEllSIZE)));
	//DrawBox(button[1].x + scroll_x, button[1].y + scroll_y, button[1].x + scroll_x + MAP_CEllSIZE, button[1].y + scroll_y + MAP_CEllSIZE,0xff0000,TRUE);
	for (int i = 0; i < button.size(); i++) {
		if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (button[i].type == 2 && button[i].flg == true) { 
			DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30 + button[i].animtimer, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		}
	}

	for (int i = 0; i < lift.size(); i++) {
		DrawGraph(lift[i].x + scroll_x-40, lift[i].y +scroll_y-25, block_image1[94+i], TRUE);
	}

	for (int i = 0; i < door.size(); i++) {
		//if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (door[i].flg == true) {
			DrawOvalAA(door[i].x + scroll_x, door[i].y + scroll_y + 30 + door[i].animtimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
		}
	}
}

void ELEMENT::Update(PLAYER* player) {
	player_map_x = roundf(player->GetPlayerX() - scroll_x);
	player_map_y = floorf((player->GetPlayerY() + MAP_CEllSIZE / 2));
	Button();
	Door();
	Lift();
	
}

/// <summary>
/// ボタンの処理
/// </summary>
void ELEMENT::Button() {
	for (int i = 0; i < button.size(); i++) {
		if(button[i].flg == true)button[i].animtimer++;
		if (button[i].animtimer > 180) {
			button[i].animtimer = 0;
			button[i].flg = false;
		}

		if (button[i].type == 1) {
			if ((player_map_x >= button[i].x - MAP_CEllSIZE / 2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
				printfDx("1番に入ってるよ！");
			}
		}
			if (button[i].type == 2) {
				if ((player_map_x >= button[i].x - MAP_CEllSIZE + 25) && (player_map_x <= button[i].x + MAP_CEllSIZE-25 ) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2 + 50) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
					printfDx("2番に入ってるよ！");
					button[i].flg = true;		//ボタンを押した
					door[i - 1].flg = true;
				}
			}

			//一回限り
			if (button[i].type == 3) {
				if ((player_map_x >= button[i].x-MAP_CEllSIZE/2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2)&& (player_map_y >= button[i].y - MAP_CEllSIZE / 2)&& (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
					printfDx("3番に入ってるよ！");
				}
			}
	}
}

/// <summary>
/// ドアの処理
/// </summary>
void ELEMENT::Door() {
	for (int i = 0; i < door.size(); i++) {
		if (door[i].flg == true) {
			door[i].animtimer++;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			map_data[y][x] = 0;
			map_data[y + 1][x] = 0;
		}
		map_data[0][0] = 0;
		//if (door[i].animtimer > 180) {
		//	door[i].animtimer = 0;
		//	door[i].flg = false;
		//}
		if ((player_map_x >= door[i].x + 25) && (player_map_x <= door[i].x + MAP_CEllSIZE + 25) && (player_map_y >= door[i].y - MAP_CEllSIZE / 2) && (player_map_y <= door[i].y + MAP_CEllSIZE / 2)) {
			door[i].animtimer = 0;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			map_data[y][x] = 1;
			map_data[y + 1][x] = 1;
			door[i].flg = false;
			
		}
	}
}

/// <summary>
/// 動く床の処理
/// </summary>
void ELEMENT::Lift() {
	for (int i = 0; i < lift.size(); i++) {
		//if (-player_map_x<=scroll_x+MAP_CEllSIZE*3&&-player_map_x>=scroll_x-MAP_CEllSIZE*3) {
		if (map_data[int(lift[i].y / MAP_CEllSIZE)][int(((lift[i].x -lift_speed*40) / MAP_CEllSIZE) + lift_speed)] == 0) {
			lift[i].x += lift_speed;
		}
		else lift_speed *= -1;
		if (!fmodf(lift[i].x, MAP_CEllSIZE)) 
		{
			if(map_data[int(lift[i].y / MAP_CEllSIZE)][int(lift[i].x / MAP_CEllSIZE - lift_speed)] == lift[i].type+94)
			map_data[int(lift[i].y / MAP_CEllSIZE)][int(lift[i].x / MAP_CEllSIZE - lift_speed)] = 0;
			//map_data[int(lift[i].y / MAP_CEllSIZE)][int(lift[i].x / MAP_CEllSIZE)] = lift[i].type+94;
		}
	}
}

/// <summary>
/// プレイヤーと動く床の当たり判定
/// </summary>
bool ELEMENT::HitLift() {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x+30 >= lift[i].x-40 && player_map_x-30 <= lift[i].x + 40
			&& player_map_y<=lift[i].y&&player_map_y>=lift[i].y-MAP_CEllSIZE) {
			return true;
		}
	}
	return false;
}