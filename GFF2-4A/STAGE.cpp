#include "STAGE.h"
#include "Element.h"
#include"DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "PLAYER.h"
#include "RESULT.h"

int STAGE::map_data[MAP_HEIGHT][MAP_WIDTH];
float STAGE::scroll_x = 0;
float STAGE::scroll_y = 0;

STAGE::STAGE() {
	**map_data = 0;
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
	//InitStage();
	LoadMapData();
	clearflg = false;
	*clearbox = 0;
	*halfwaypointbox = 0;
	halfwaypoint = false;

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//�N���A���W����
			if (map_data[i][j] == 73) { clearbox[0] = j * MAP_CEllSIZE; clearbox[1] = i * MAP_CEllSIZE; }
			//���Ԓn�_���W����
			if (map_data[i][j] == 90) { halfwaypointbox[0] = j * MAP_CEllSIZE; halfwaypointbox[1] = i * MAP_CEllSIZE; }
		}
	}
}
	

void STAGE::Update(PLAYER* player) {
	StageClear(player);
	HalfwayPoint(player);
	if (player->GetPlayerMoveState() != PLAYER_MOVE_STATE::HOOK) {
		CameraWork(player);
	}
}

void STAGE::Draw()const {
	//�f�o�b�O
	//DrawFormatString(200, 100, 0xffffff, "oldx:%f", player_x_old);
	//DrawFormatString(350, 100, 0xffffff, "vectorx:%f", player_vector_x);
	//DrawFormatString(100, 200, 0xffffff, "scroll_x:%f", scroll_x);
	//�Q�[���N���A��
	if (clearflg == true) {DrawExtendString(30, 200, 5.5f, 5.5f, "�Q�[���N���A���߂łƂ��I�I�I", 0xE2FE47);}
	
	//printfDx("%f",scroll_x);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//��ʊO�͕`�悵�Ȃ�
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280 && j * MAP_CEllSIZE + scroll_y >= -300) {
				if (map_data[i][j] < 89 
					|| (map_data[i][j] <= 74	//�_���J�̐����܂��`�悵�Ȃ�
					&& map_data[i][j] >= 79)
					) { DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE + scroll_y, block_image1[map_data[i][j] - 1], TRUE); }
			}
			//�����i�[�ƃO���|���̓c�������`�悷��
			if(map_data[i][j] == 91 || map_data[i][j] == 92){ DrawGraph(j * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE, block_image1[map_data[i][j] - 1], TRUE); }
			
		}
	}

	//���Ԓn�_�@�`��
	if(halfwaypoint == false){ DrawGraph(halfwaypointbox[0] + scroll_x, halfwaypointbox[1] + scroll_y, block_image1[88], TRUE); }
	else{ DrawGraph(halfwaypointbox[0] + scroll_x, halfwaypointbox[1] + scroll_y, block_image1[89], TRUE); }
	
}

void STAGE::CameraWork(PLAYER* player) {
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

	
	/*if ((player_vector_y > 0 && player->GetPlayerY() >= 720) || (player_vector_y < 0 && player->GetPlayerY() <= 0)) {

		scroll_y -= 5 * player_vector_y;

		if (scroll_y >= 0 || scroll_y <= -1120) {
			scroll_y += 5 * player_vector_y;
		}
	}*/

	if (player_x_old != player->GetPlayerX()) {
		player_x_old = player->GetPlayerX();
	}
	else {
		player_vector_x = 0;
	}
	if (player_y_old != player->GetPlayerY()) {
		player_y_old = player->GetPlayerY();
	}
}



void STAGE::HookProcess() {

}

void STAGE::PuddleProcess(){

}

/// <summary>
/// �X�e�[�W�̃X�N���[��
/// </summary>
bool STAGE::SetScrollPos(int move_x) {
	scroll_x -= 5 * move_x;
	if (scroll_x >= 0 || scroll_x <= -(80 * MAP_WIDTH - 640)) {
	scroll_x += 5 * move_x;
		return true;
	}
	return false;
}

/// <summary>
/// �v���C���[�ƃu���b�N�̓����蔻��
/// </summary>

bool STAGE::HitMapDat(int y, int x) {
	if (CheckHitKey(KEY_INPUT_Z))return false;		//�f�o�b�O�p
	int block_type = GetMapDat(y, x);
	if (
		block_type == -1 //�͈͊O
		|| block_type == 0	//���ʑ�
		|| block_type == 21 //�t���[��
		|| block_type == 22 //�A�J�V�A��
		|| block_type == 23 //�I�[�N��
		|| block_type == 64	//�h�A 
		|| block_type == 65	//�h�A 
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 73	//�S�[��
		|| block_type == 90 //���Ԓn�_
		|| block_type == 91 //�����i�[
		|| block_type == 92 //�O���|��
		|| block_type == 93	//�g�}�g��
		|| block_type == 95	//������
		|| block_type == 97	//�}���z�[���̊W(�o��)
		) {
		return false;
	}
	return true;
}
/// <summary>
/// �X���C���̂�����̓����蔻��
/// </summary>
bool STAGE::HitThrowSlime(int y, int x) {
	int block_type = GetMapDat(y, x);
	if (
		block_type == -1 //�͈͊O
		|| block_type == 0	//���ʑ�
		|| block_type == 61	//�ǃ{�^��(������)
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 73	//�S�[��
		|| block_type == 97	//�}���z�[���̊WEnd
		) {
	return false;
	}
		return true;
}

/// <summary>
/// �}�b�v�f�[�^�̓ǂݍ���
/// </summary>
void STAGE::LoadMapData(void) {

		std::ifstream ifs("Resource/Map_Data/MapData1.csv");

		std::string str = "";
		int i = 0, j = 0;
		while (std::getline(ifs,str))
		{
			std::string tmp = "";
			std::istringstream stream(str);

			while (std::getline(stream,tmp,','))
			{
				map_data[i][j] = std::stoi(tmp);
				j++;
			}
			j = 0;
			i++;
		}
}


/// <summary>
/// �X�e�[�W�N���A��
/// </summary>
void STAGE::StageClear(PLAYER *player) {
	int player_map_x = static_cast<int>(roundf(player->GetPlayerX() - STAGE::GetScrollX()));
	int player_map_y = static_cast<int>(floorf(player->GetPlayerY()));
	DrawFormatString(100, 200, 0xffffff, "x:%dy:%d", clearbox[0], clearbox[1]);

	//���ɐG���ƃQ�[���N���A
	if ((player_map_x >= clearbox[0] - MAP_CEllSIZE / 2 + 50) && (player_map_x <= clearbox[0] + MAP_CEllSIZE + 30) && (player_map_y >= clearbox[1] - MAP_CEllSIZE / 2) && (player_map_y <= clearbox[1] + MAP_CEllSIZE / 2)) {
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

bool STAGE::HalfwayPoint(PLAYER *player) {
	int player_map_x = roundf(player->GetPlayerX() - STAGE::GetScrollX());
	int player_map_y = floorf(player->GetPlayerY());
	if ((player_map_x >= halfwaypointbox[0] - MAP_CEllSIZE / 2) && (player_map_x <= halfwaypointbox[0] + MAP_CEllSIZE / 2) && (player_map_y >= halfwaypointbox[1] - MAP_CEllSIZE) && (player_map_y <= halfwaypointbox[1] + MAP_CEllSIZE)) {
		//�f�o�b�O
		//printfDx("aaa");
		if (halfwaypoint == false) { PlaySoundMem(halfwaypoint_se, DX_PLAYTYPE_BACK, TRUE); 
		static int anitimer = 0;
		if (++anitimer < 180) {
			DrawOvalAA(halfwaypointbox[0] + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox[1] + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			DrawOvalAA(halfwaypointbox[0] + scroll_x + MAP_CEllSIZE + anitimer % 3, halfwaypointbox[1] + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
			DrawOvalAA(halfwaypointbox[0] + scroll_x + anitimer % 3, halfwaypointbox[1] + scroll_y + 30 + anitimer, 25, 10, 4, 0xbfcb4e, TRUE, 1.0f);
		}
		else if (180 <= anitimer)anitimer = 0;
		}
		halfwaypoint = true;
	}
	return halfwaypoint;
}