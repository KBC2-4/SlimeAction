
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
				data.y = (i * MAP_CEllSIZE + MAP_CEllSIZE / 2) + 25;
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
			case 70:
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

void ELEMENT::Update(PLAYER* player) {
	Button(player->GetPlayerX(),player->GetPlayerY());
}

void ELEMENT::Button(float player_x, float player_y) {
	DrawFormatString(200, 300, 0xFFFFFF, "x:%lf", player_x);
	for (int i = 0; i < button.size(); i++) {
		printfDx("button[i].x%d", button[i].x);
		if (button[i].type == 1) {
			if ((player_x == button[i].x) && (player_y == button[i].y)) {
				DrawFormatString(100, 300, 0xFFFFFF, "bx:%lf\nby:lf", button[i].x, button[i].y);
				DxLib_End();
			}
			if (button[i].type == 2) {
				if ((player_x  == button[i].x) && (player_y == button[i].y)) {
					DrawFormatString(100, 300, 0xFFFFFF, "bx:%lf\nby:lf", button[i].x, button[i].y);
					DxLib_End();
				}
			}


			if (button[i].type == 3) {
				//if (button[i].flg == false) {
					if ((player_x == button[i].x) && (player_y == button[i].y)) {
						DrawFormatString(100, 300, 0xFFFFFF, "bx:%lf\nby:lf", button[i].x, button[i].y);
						DxLib_End();
				//}	

				}
			}
		}
	}
}