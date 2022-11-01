
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
				//�{�^����
			case 61:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25;
				data.y = i * MAP_CEllSIZE + MAP_CEllSIZE / 2 ;
				data.type = 1;
				button.push_back(data);
				break;
				
				//�{�^��(��)
			case 62:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 2;
				button.push_back(data);
				break;


				//�{�^��(ones)��
			case 63:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25;
				data.type = 3;
				button.push_back(data);
				break;

				//�h�A
			case 64:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				door.push_back(data);
				break;

				//�g���l��(����)
			case 65:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				tunnel.push_back(data);
				break;

				//�g���l��(����)
			case 66:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 2;
				tunnel.push_back(data);
				break;

				//�g���l��(�o��)
			case 67:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 3;
				tunnel.push_back(data);
				break;

				//�_
			case 68:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.type = 1;
				acid.push_back(data);
				break;

				//�t�b�N
			case 71:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = i * MAP_CEllSIZE + MAP_CEllSIZE / 2;
				hook.push_back(data);
				break;

				//������
			case 95:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 10;
				data.type = 1;
				lift.push_back(data);
				break;

				//������(fast)
			case 96:
				data.x = (j * MAP_CEllSIZE + MAP_CEllSIZE / 2);
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 10;
				data.type = 2;
				lift.push_back(data);
				break;

		
			default:
				break;
			}

			
		}
			
	}
}

void ELEMENT::Draw() const {
	DrawFormatString(200, 100, 0xFFFFFF, "button.x%f\nbutton.y%f", button[1].x, button[1].y);
	DrawFormatString(200, 200, 0xFFFFFF, "x%f\ny%f", player_map_x, player_map_y);
	//DrawBox(button[1].x + scroll_x, button[1].y + scroll_y, button[1].x + scroll_x + MAP_CEllSIZE, button[1].y + scroll_y + MAP_CEllSIZE,0xff0000,TRUE);
}

void ELEMENT::Update(PLAYER* player) {
	player_map_x = roundf((player->GetPlayerX() - STAGE::GetScrollX()));
	player_map_y = floorf((player->GetPlayerY() + MAP_CEllSIZE / 2));
	Button();
}

void ELEMENT::Button() {
	for (int i = 0; i < button.size(); i++) {
		if (button[i].type == 1) {
			if ((player_map_x >= button[i].x - MAP_CEllSIZE / 2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
				printfDx("1�Ԃɓ����Ă��I");
			}
		}
			if (button[i].type == 2) {
				if ((player_map_x >= button[i].x - MAP_CEllSIZE + 25) && (player_map_x <= button[i].x + MAP_CEllSIZE-25 ) && (player_map_y >= button[i].y - MAP_CEllSIZE / 2) && (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
					printfDx("2�Ԃɓ����Ă��I");
					//DrawOvalAA(button[i].x, button[i].y, MAP_CEllSIZE + 25, MAP_CEllSIZE / 2,)
				}
			}

			//������
			if (button[i].type == 3) {
				if ((player_map_x >= button[i].x-MAP_CEllSIZE/2) && (player_map_x <= button[i].x + MAP_CEllSIZE / 2)&& (player_map_y >= button[i].y - MAP_CEllSIZE / 2)&& (player_map_y <= button[i].y + MAP_CEllSIZE / 2)) {
					printfDx("3�Ԃɓ����Ă��I");
				}
			}
		
	}
}