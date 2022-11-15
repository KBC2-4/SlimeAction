
#include "Element.h"
#include "PLAYER.h"


ELEMENT::ELEMENT() {

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
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map_data[i][j])
			{
				//�{�^����
			case 61:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25);
				data.y = static_cast<float>(i * MAP_CEllSIZE + MAP_CEllSIZE / 2) ;
				data.type = 1;
				button.push_back(data);
				break;
					
				//�{�^��(��)
			case 62:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 2;
				button.push_back(data);
				break;


				//�{�^��(ones)��
			case 63:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25);
				data.type = 3;
				button.push_back(data);
				break;

				//�܂��Ă���h�A�̉�
			case 66:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 1;
				door.push_back(data);
				break;

				//�}���z�[���̊W
			case 68:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 1;
				manhole.push_back(data);
				break;

				//�}���z�[��(����)
			case 69:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.type = 2;
				manhole.push_back(data);
				break;

				//�}���z�[��(�o��)
			//case 70:
			//	data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
			//	data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
			//	data.type = 3;
			//	manhole.push_back(data);
			//	break;

				//�_���J�̐����܂�
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

				//�t�b�N
			case 72:
				data.x = static_cast<float>((j * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				data.y = static_cast<float>((i * MAP_CEllSIZE + MAP_CEllSIZE / 2));
				hook.push_back(data);
				break;

				//������
			case 95:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 2;
				lift.push_back(data);
				break;

				//������(�S�[��)
			case 96:
				data.x = static_cast<float>((j * MAP_CEllSIZE));
				data.y = static_cast<float>((i * MAP_CEllSIZE));
				data.type = 0;
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
	
}

void ELEMENT::Draw() const {
	//static int animtimer = 0;
	//printfDx("%d", animtimer);
	//DrawFormatString(200, 100, 0xFFFFFF, "acidrain_puddles.x%f\acidrain_puddles.y%f", acidrain_puddles[1].x, acidrain_puddles[1].y);
	//DrawFormatString(200, 200, 0xFFFFFF, "x%f\ny%f", player_map_x, player_map_y);
	//�f�o�b�O�p

	//�{�^��
	for (int i = 0; i < button.size(); i++) {
		if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (button[i].type == 2 && button[i].flg == true) { 
			DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30 + button[i].animtimer, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		}
	}

	//������
	for (int i = 0; i < lift.size(); i++) {
		DrawGraph(lift[i].x + scroll_x, lift[i].y - 25 + scroll_y, block_image1[94], TRUE);
		
	}

	//�h�A
	for (int i = 0; i < door.size(); i++) {
		//if (button[i].type == 2 && button[i].flg == false)DrawOvalAA(button[i].x + scroll_x, button[i].y + scroll_y + 30, 25, 10, 20, 0xbfcb4e, TRUE, 1.0f);
		if (door[i].flg == true) {
			//�G�t�F�N�g
			DrawOvalAA(door[i].x + scroll_x, door[i].y + scroll_y + 30 + door[i].animtimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
		}
	}

	//�}���z�[��
	for (int i = 0; i < manhole.size(); i++) {
		if (manhole[i].flg == true) {
			//DrawOvalAA(manhole[i].x + scroll_x, manhole[i].y + scroll_y + 30 + manhole[i].animtimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			//DrawGraph(manhole[i].x + scroll_x + manhole[i].animtimer, manhole[i].y + scroll_y, block_image1[67], TRUE);
		}
	}
}

void ELEMENT::Update(PLAYER* player) {
	//�v���C���[�̃}�b�v�����W��ݒ�
	player_map_x = roundf(player->GetPlayerX() - STAGE::GetScrollX());
	player_map_y = floorf(player->GetPlayerY());

	Button(player);
	Door();
	Lift(player);
	Manhole(player);
	Acidrain_puddles(player);
	
}

/// <summary>
/// �{�^���̏���
/// </summary>
void ELEMENT::Button(PLAYER* player) {

	static bool keep_pushing = false;	//���������Ă��邩�t���O

	for (int i = 0; i < button.size(); i++) {
		if(button[i].flg == true)button[i].animtimer++;
		if (button[i].animtimer > 180 && keep_pushing == false) {
			button[i].animtimer = 0;
			button[i].flg = false;
		}	

		if (button[i].type == 1) {		//���{�^��
			int max_ball_num = player->GetThrowCnt();
			for (int ball_num = 0; ball_num < max_ball_num; ball_num++) {
				if ((player->GetThrowSlime(ball_num).GetThrowX() >= button[i].x - MAP_CEllSIZE / 2 + 33) && (player->GetThrowSlime(ball_num).GetThrowX() <= button[i].x + MAP_CEllSIZE / 2 - 30) && (player->GetThrowSlime(ball_num).GetThrowY() >= button[i].y - MAP_CEllSIZE / 2) && (player->GetThrowSlime(ball_num).GetThrowY() <= button[i].y + MAP_CEllSIZE / 2)) {
					//�f�o�b�O
					//printfDx("1�Ԃɓ����Ă��I");
					if (CheckSoundMem(press_the_button_se) == FALSE)PlaySoundMem(press_the_button_se, DX_PLAYTYPE_BACK, TRUE);
					if(i < door.size() && i >= 0){
						int j = i + 1;
						door[j].flg = true;
					}
					
				}
			}
		}
			if (button[i].type == 2) {	//�{�^��
				bool ball_flg = false;	//�{�[���̓����蔻��t���O
				for (int ball_num = 0; ball_num < player->GetThrowCnt(); ball_num++) {
					if ((player->GetThrowSlime(ball_num).GetThrowX() >= button[i].x - MAP_CEllSIZE / 2 + 10) && (player->GetThrowSlime(ball_num).GetThrowX() <= button[i].x + MAP_CEllSIZE / 2 - 10) && (player->GetThrowSlime(ball_num).GetThrowY() >= button[i].y - MAP_CEllSIZE / 2) && (player->GetThrowSlime(ball_num).GetThrowY() <= button[i].y + MAP_CEllSIZE / 2)) {
						ball_flg = true;
					}
					else { keep_pushing = false; }
				}

				if ((ball_flg == true) || ((player_map_x >= button[i].x - MAP_CEllSIZE + 25) && (player_map_x <= button[i].x + MAP_CEllSIZE-25 ) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2 ) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2))) {
					//�f�o�b�O
					//printfDx("2�Ԃɓ����Ă��I");
					if(ball_flg == false)player->SetPlayerY(button[i].y - 6.5f);
					if (button[i].flg == false) {
						if (CheckSoundMem(switch_se) == FALSE)PlaySoundMem(switch_se, DX_PLAYTYPE_BACK, TRUE);
					}
					keep_pushing = true; //���������Ă���
					button[i].flg = true;		//�{�^����������
					
					if (i < door.size() && i >= 0) {
						int j = i - 1;
						door[j].flg = true;
					}
					
				}else{ keep_pushing = false; }
			}

			//������
			if (button[i].type == 3) {	//Onec�{�^��
				if ((player_map_x >= button[i].x-MAP_CEllSIZE/2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2)&& (player_map_y >= button[i].y - MAP_CEllSIZE / 2)&& (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
					//�f�o�b�O
					//printfDx("3�Ԃɓ����Ă��I");
				}
			}
	}
}

/// <summary>
/// �h�A�̏���
/// </summary>
void ELEMENT::Door() {
	for (int i = 0; i < door.size(); i++) {
		if (door[i].flg == true) {
			door[i].animtimer++;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			map_data[y][x] = 64;
			map_data[y - 1][x] = 65;
		}
		//if (door[i].animtimer > 180) {
		//	door[i].animtimer = 0;
		//	door[i].flg = false;
		//}
		if ((player_map_x >= door[i].x + 25) && (player_map_x <= door[i].x + MAP_CEllSIZE + 25) && (player_map_y >= door[i].y - MAP_CEllSIZE / 2) && (player_map_y <= door[i].y + MAP_CEllSIZE / 2)) {
			door[i].animtimer = 0;
			int x = floor(door[i].x / MAP_CEllSIZE);
			int y = floor(door[i].y / MAP_CEllSIZE);
			map_data[y][x] = 66;
			map_data[y - 1][x] = 67;
			door[i].flg = false;
			if (CheckSoundMem(door_close_se) == FALSE)PlaySoundMem(door_close_se, DX_PLAYTYPE_BACK, TRUE);
			
		}
	}
}

/// <summary>
/// �������̏���
/// </summary>
void ELEMENT::Lift(PLAYER* player) {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x>lift[i].x - 1280 && player_map_x<lift[i].x + 1280) {
			lift[i].flg = true;
		}
		if (lift[i].flg) {
			if (lift[i].x != lift_goal[i].x) {
				lift[i].x += lift_vector * 2.0;
				if (HitLift()) {
					player->SetPlayerX(player->GetPlayerX() + lift_vector * 2.0);
				}

			}
			else if (lift[i].type == 2) {
				for (int lift_pos = lift[i].x - MAP_CEllSIZE * lift_vector; i >= 0; lift_pos -= lift_vector * MAP_CEllSIZE) {
					if (map_data[int(lift[i].y) / MAP_CEllSIZE][lift_pos / MAP_CEllSIZE] == 95) {
						lift_goal[i].x = lift_pos;
						break;
					}
				}
				map_data[int(lift[i].y) / MAP_CEllSIZE][int(lift[i].x) / MAP_CEllSIZE] = 95;
				lift_vector *= -1;
			}

		}
		
	}
	
}

/// <summary>
/// �v���C���[�Ɠ������̓����蔻��
/// </summary>
bool ELEMENT::HitLift() {
	for (int i = 0; i < lift.size(); i++) {
		if (player_map_x >= lift[i].x && player_map_x <= lift[i].x +MAP_CEllSIZE
			&& player_map_y+MAP_CEllSIZE/2==lift[i].y) {
			return true;
		}
	}
	return false;
}


/// <summary>
/// �}���z�[���̏���
/// </summary>
void ELEMENT::Manhole(PLAYER* player) {
	for (int i = 0; i < manhole.size(); i++) {
		if (manhole[i].flg == true)manhole[i].animtimer++;
		if (manhole[i].animtimer > 180) {
			manhole[i].animtimer = 0;
			manhole[i].flg = false;
		}
		if (manhole[i].type == 1) {
			if ((player_map_x >= manhole[i].x - MAP_CEllSIZE + 25) && (player_map_x <= manhole[i].x + MAP_CEllSIZE - 25) && (player_map_y >= manhole[i].y - MAP_CEllSIZE / 2) && (player_map_y <= manhole[i].y + MAP_CEllSIZE / 2)) {
				player->SetPlayerY(player->GetPlayerY() - 10.5f);
				manhole[i].flg = true;

			}
		}
	}
}

void ELEMENT::Acidrain_puddles(PLAYER* player) {

	for (int i = 0; i < acidrain_puddles.size(); i++) {

		if (acidrain_puddles[i].flg == false)acidrain_puddles[i].animtimer++;
		if (acidrain_puddles[i].animtimer > 180) {
			acidrain_puddles[i].animtimer = 0;
			acidrain_puddles[i].flg = true;
		}

		if (acidrain_puddles[i].type == 1) {	//�_���J�̐����܂�
			if ((player_map_x >= acidrain_puddles[i].x - MAP_CEllSIZE / 2) && (player_map_x <= acidrain_puddles[i].x + MAP_CEllSIZE / 2) && (player_map_y >= acidrain_puddles[i].y - MAP_CEllSIZE) && (player_map_y <= acidrain_puddles[i].y + MAP_CEllSIZE)) {
				//�f�o�b�O
				//printfDx("�����Ă��I");
				if (CheckSoundMem(walk_puddle_se) == FALSE)PlaySoundMem(walk_puddle_se, DX_PLAYTYPE_BACK, TRUE);
				//player->SetPlayerY(acidrain_puddles[i].y + 1.5f);
				if (acidrain_puddles[i].flg == true) {
					player->SetLife(player->GetLife() - 1);
					printfDx("�c�胉�C�t�F%d",player->GetLife());		//�f�o�b�O
					acidrain_puddles[i].flg = false;
				}
			}else{ acidrain_puddles[i].animtimer = 0; }
		}
	}
}
