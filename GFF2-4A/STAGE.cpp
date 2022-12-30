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
/// �R���X�g���N�^
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
			//�N���A���W����
			if (map_data.at(i).at(j) == 88) { clearbox.x = j * MAP_CEllSIZE; clearbox.y = i * MAP_CEllSIZE; }
			//���Ԓn�_���W����
			if (map_data.at(i).at(j) == 90) { halfwaypointbox.x = j * MAP_CEllSIZE; halfwaypointbox.y = i * MAP_CEllSIZE; }

			//�X�|�[���n�_���W����
			if (map_data.at(i).at(j) == 777) { spawn_point.x = i * MAP_CEllSIZE; spawn_point.y = j * MAP_CEllSIZE; }
		}
	}
	//�X�|�[���n�_���Z�b�g
	if (spawn_point.x == 0 && spawn_point.y == 0) {
		MessageBox(NULL, "�X�|�[���n�_���Z�b�g����Ă��܂���B", "�}�b�v�ǂݍ��݃G���[", MB_OK | MB_ICONERROR);
		spawn_point.x = 0;
		spawn_point.y = 0;
	}

	ChangeVolumeSoundMem(Option::GetSEVolume(), halfwaypoint_se);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
STAGE::~STAGE() {
	for (int i = 0; i < 110; i++) {
		DeleteGraph(block_image1[i]);
	}
	DeleteSoundMem(halfwaypoint_se);
}

/// <summary>
/// �X�e�[�W�̍X�V
/// </summary>
void STAGE::Update(PLAYER* player, ELEMENT* element) {

	//�f�o�b�O
	//if (CheckHitKey(KEY_INPUT_C))clearflg = true;
	ChangeVolumeSoundMem(Option::GetSEVolume(), halfwaypoint_se);

	StageClear(player);
	HalfwayPoint(player);
	CameraWork(player, element);
}
/// <summary>
/// �X�e�[�W�̕`��
/// </summary>
void STAGE::Draw(ELEMENT* element)const {

	for (int i = 0; i < map_data.size(); i++) {
		for (int j = 0; j < map_data.at(0).size(); j++) {
			//if (map_data.at(i).at(j) == 72)DrawFormatString(100 + j * 20, 50, 0xffffff, "%d %d", i, j);
			//��ʊO�͕`�悵�Ȃ�
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280 && i * MAP_CEllSIZE + scroll_y >= -80 && i * MAP_CEllSIZE + scroll_y <= 720) {
				if (
					map_data.at(i).at(j) != 68		//�}���z�[��(��)
					&& map_data.at(i).at(j) != 62	 //�{�^��
					&& map_data.at(i).at(j) != 74	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 75	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 76	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 77	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 78	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 79	//�_���J�̐����܂�
					&& map_data.at(i).at(j) != 101		//�߂�Ŕ��ŕʓr�`�悵�Ă����
					&& map_data.at(i).at(j) != 102	//�X�e�[�W1�Q�[�g(��)
					&& map_data.at(i).at(j) != 103	//�X�e�[�W1�Q�[�g(��)
					&& map_data.at(i).at(j) != 104	//�X�e�[�W2�Q�[�g(��)
					&& map_data.at(i).at(j) != 105	//�X�e�[�W2�Q�[�g(��)
					&& map_data.at(i).at(j) != 106	//�X�e�[�W3�Q�[�g(��)
					&& map_data.at(i).at(j) != 107	//�X�e�[�W3�Q�[�g(��)
					&& map_data.at(i).at(j) != 51	//������
					&& map_data.at(i).at(j) != 52	//������
					&& map_data.at(i).at(j) != 53	//������
					&& map_data.at(i).at(j) != 54	//������
					&& (map_data.at(i).at(j) <= 88		//�N���A�哙
						////89�`90�ԑ��`�悵�Ȃ�
						|| map_data.at(i).at(j) >= 100 && map_data.at(i).at(j) != 777)
					) {
					DrawGraphF(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE);
				}
			}
			//�����i�[�ƃO���|���̓c�������`�悷��
			if (map_data.at(i).at(j) == 91 || map_data.at(i).at(j) == 92) { DrawGraphF(j * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE + scroll_y, block_image1[map_data.at(i).at(j) - 1], TRUE); }
			if (map_data.at(i).at(j) == 101) { DrawExtendGraphF((j - 1) * MAP_CEllSIZE + scroll_x, (i - 1) * MAP_CEllSIZE + scroll_y, (j + 1) * MAP_CEllSIZE + scroll_x, (i + 1) * MAP_CEllSIZE + scroll_y, block_image1[100], TRUE); }
		}
	}

	//���Ԓn�_�@�`��
	//���Ԓn�_���Ȃ��ꍇ�͕`�悵�Ȃ��B
	if (halfwaypointbox.x != 0) {
		if (halfwaypoint == false) { DrawGraphF(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[88], TRUE); }
		else { DrawGraphF(halfwaypointbox.x + scroll_x, halfwaypointbox.y + scroll_y, block_image1[89], TRUE); }
	}

}

/// <summary>
/// �}�b�v�f�[�^�̓ǂݍ���
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



	//�A�[�J�C�u�Ή���


	int FileHandle;
	if ((FileHandle = FileRead_open(buf)) == 0) {
		exit(1);
	}

	char str[642];		//��s�̒���
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

			//�{�^���ƃh�A�̘A�g�ԍ����i�[
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
/// �}�b�v�z���Getter
/// </summary>
int STAGE::GetMapData(int y, int x) {
	if (y < 0 || y >= map_data.size()) { return -999; }
	if (x < 0 || x >= map_data[y].size()) { return -999; }
	return map_data.at(y).at(x);
}

/// <summary>
/// �X�e�[�W�X�N���[���֐�
/// </summary>
void STAGE::CameraWork(PLAYER* player, ELEMENT* element) {
	int scroll_speedY = 7;
	//�v���C���[x�x�N�g���̔���
	if (player->GetPlayerX() > player_x_old) {
		player_vector_x = 1;
	}
	else if (player->GetPlayerX() < player_x_old) {
		player_vector_x = -1;
	}

	//�v���C���[y�x�N�g���̔���
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
	//x���X�N���[��
	//if (element->HitLift(player)) { scroll_speed_x = element->GetLift_SpeedX(); }
	if ((player_vector_x > 0 && player->GetPlayerX() >= 620 || player_vector_x < 0 && player->GetPlayerX() <= 660) && player_x_old != player->GetPlayerX()) {
		scroll_x -= scroll_speed_x * player_vector_x;
		if (scroll_x > 0 || scroll_x <= -(80 * static_cast<int>(map_data.at(0).size()) - 1280)) {
			scroll_x += scroll_speed_x * player_vector_x;
		}
	}

	//y���X�N���[��
	//if ((player_vector_y > 0 && player->GetPlayerY() <= 240 || player_vector_y < 0 && (scroll_y > 0 && map_data.size() <= 14) || (scroll_y > -720 && map_data.size() > 14)) && player_y_old != player->GetPlayerY()) {
	//	scroll_y += scroll_speedY * player_vector_y;
	//	if (scroll_y > 0/* || scroll_x <= -(80 * static_cast<int>(map_data.size()) - 720)*/) {
	//		scroll_y -= scroll_speedY * player_vector_y;
	//	}
	//}


	//x���X�N���[��������y���W�o�[�W�������쐬
	//if ((player_vector_y > 0 && player->GetPlayerY() >= 620 || player_vector_y < 0 && player->GetPlayerY() <= 300)) {
	//	scroll_y -= 5 * player_vector_y;
	//	//if (scroll_y > 0 || scroll_y <= -(80 * static_cast<int>(map_data.size()) - 720)) {
	//	//	scroll_y += 5 * player_vector_y;
	//	//}
	//}

	if (++count_timer % 60 == 0)player_longold = player->GetPlayerY();

	//�X�|�[���n�_����ɏグ��ʒu�����߂�
	//if (scroll_y + player->GetPlayerY() < 0 && player->GetPlayerY() <= spawn_point.y - player->GetPlayerY() + 400 && player->GetPlayerMoveState() != PLAYER_MOVE_STATE::HOOK) { scroll_y += scroll_speed_y; }
	//else if (scroll_y + player->GetPlayerY() < player->GetPlayerY()) {
	//	if (scroll_y >= (-MAP_CEllSIZE * static_cast<int>(map_data.size()) + 721) && (player->GetPlayerY() > GetSpawnPoint().y + 400)) {
	//		//�v���C���[�̗������x�ɉ����ăX�N���[��Y��������
	//		if (player->GetJumpVelocity() > 0)scroll_y -= player->GetJumpVelocity();
	//	}
	//	if ((player->GetPlayerMoveState() == PLAYER_MOVE_STATE::HOOK || player->GetPlayerMoveState() == PLAYER_MOVE_STATE::GROW_HOOK) && player->GetPlayerY() > 500.0f) {
	//		scroll_y -= 5;
	//	}
	//}


	//�}���z�[���̉��ɂ�������	
	//if (-scroll_y + player->GetPlayerY() > player->GetPlayerY())scroll_y--;
	//for(unsigned int i=scroll_y )

	//�X�N���[��Y-720�ƃv���C���[Y520�̌덷��200�ɂȂ�܂�



	if (player->GetPlayerY() >= 560 &&player->GetPlayerY()-scroll_y<=map_data.size()*MAP_CEllSIZE&& GetMapData((player->GetPlayerY() - scroll_y) / MAP_CEllSIZE + 3, (player->GetPlayerX() - scroll_x) / MAP_CEllSIZE) != -1) {
		if (player->GetPlayerMoveState() == PLAYER_MOVE_STATE::FALL) {
			//�v���C���[�̗������x�ɉ����ăX�N���[��Y��������
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
/// ��ʃX�N���[�����WX��Setter
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
/// �v���C���[�ƃu���b�N�̓����蔻��
/// </summary>
bool STAGE::HitMapDat(int y, int x) {
#ifdef _DEBUG
	if (PAD_INPUT::GetNowKey() == XINPUT_BUTTON_Y || CheckHitKey(KEY_INPUT_Z))return false;		//�f�o�b�O�p
#endif
	int block_type = GetMapData(y, x);
	if (block_type == temporary_hit) { return true; }
	if (
		block_type == -1 //�͈͊O
		|| block_type == 0	//���ʑ�
		|| block_type == 21 //�t���[��
		|| block_type == 22 //�A�J�V�A��
		|| block_type == 23 //�I�[�N��
		|| block_type == 24 //�搶���
		|| block_type == 31 //�t����
		|| block_type == 51	//������(�c)
		|| block_type == 52	//������(��)
		|| block_type == 53	//������(�S�[���c)
		|| block_type == 54	//������(�S�[����)
		|| block_type == 64	//�h�A 
		|| block_type == 65	//�h�A 
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 71	//�c������
		|| block_type == 72	//�c��
		|| block_type == 73	//�S�[��
		|| block_type == 85	//�N���A��
		|| block_type == 86	//�N���A��
		|| block_type == 87	//�N���A��
		|| block_type == 88	//�N���A��
		|| block_type == 90 //���Ԓn�_
		|| block_type == 91 //�����i�[
		|| block_type == 92 //�O���|��
		|| block_type == 93	//�g�}�g��
		|| block_type == 97	//�}���z�[���̊W(�o��)
		|| block_type == 98	//�}���z�[���̊J���Ă���W
		|| block_type == 101//�߂�u���b�N
		|| block_type == 102//�X�e�[�W1�u���b�N
		|| block_type == 103//�X�e�[�W2�u���b�N
		|| block_type == 104//�X�e�[�W3�u���b�N
		|| block_type == 105//�X�e�[�W3�u���b�N
		|| block_type == 106//�X�e�[�W3�u���b�N
		|| block_type == 107//�X�e�[�W3�u���b�N
		|| block_type == 777//�X�|�[���n�_�u���b�N
		) {
		return false;
	}

	return true;
}
/// <summary>
/// �X���C���̂�����̓����蔻��
/// </summary>
bool STAGE::HitThrowSlime(int y, int x) {
	int block_type = GetMapData(y, x);
	if (
		block_type == -1 //�͈͊O
		|| block_type == 0	//���ʑ�
		|| block_type == 31 //�t����
		|| block_type == 61	//�ǃ{�^��(������)
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 71	//�c�^
		|| block_type == 72	//�c�^(�߂܂镔��)
		|| block_type == 73	//�S�[��
		|| block_type == 86	//�N���A��
		|| block_type == 87	//�N���A��
		|| block_type == 88	//�N���A��
		|| block_type == 89	//�N���A��
		|| block_type == 97	//�}���z�[���̊WEnd
		|| block_type == 98	//�}���z�[���̊J���Ă���W
		|| block_type == 101//�߂�u���b�N
		|| block_type == 102//�X�e�[�W1�u���b�N
		|| block_type == 103//�X�e�[�W2�u���b�N
		|| block_type == 104//�X�e�[�W3�u���b�N
		|| block_type == 777//�X�|�[���n�_�u���b�N
		) {
		return false;
	}
	return true;
}


/// <summary>
/// �X�e�[�W�N���A���菈��
/// </summary>
void STAGE::StageClear(PLAYER* player) {

	int player_map_x = static_cast<int>(roundf(player->GetPlayerX() - scroll_x));
	int player_map_y = static_cast<int>(floorf(player->GetPlayerY()) - scroll_y);

	//���ɐG���ƃQ�[���N���A
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
/// ���Ԓn�_���菈��
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