#include "STAGE.h"
#include "Element.h"
#include"DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int STAGE::map_data[MAP_HEIGHT][MAP_WIDTH];
float STAGE::scroll_x = 0;
float STAGE::scroll_y = 0;

STAGE::STAGE() {
	**map_data = 0;
	*block_image1 = 0;
	*stage_image = 0;
	scroll_x = 0;
	scroll_y = 0;
	LoadDivGraph("Resource/Images/Stage/map_chips.png", 100, 10, 10, 80, 80, block_image1);
	//InitStage();
	LoadMapData();
}
	

//void STAGE::Update() {
//
//}

void STAGE::Draw()const {
	//printfDx("%f",scroll_x);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//��ʊO�͕`�悵�Ȃ�
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280) {
				if (map_data[i][j] < 90/* && map_data[i][j] != 68*/) { DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[map_data[i][j] - 1], TRUE); }
			}
			
		}
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
	if (scroll_x >= 0 || scroll_x <= -7680) {
		scroll_x += 5 * move_x;
		return true;
	}
	return false;
}

bool STAGE::HitMapDat(int y, int x) {
	if (CheckHitKey(KEY_INPUT_Z))return false;		//�f�o�b�O�p
	int block_type = GetMapDat(y, x);
	if (
		block_type == -1 //�͈͊O
		|| block_type == 0	//���ʑ�
		|| block_type == 15 //�t���[��
		|| block_type == 14 //�A�J�V�A��
		|| block_type == 13 //�I�[�N��
		|| block_type == 64	//�h�A 
		|| block_type == 65	//�h�A 
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 73	//�S�[��
		|| block_type == 95	//������

		//���}���u
		|| block_type == 19	//New �A�J�V�A��
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
		|| block_type == 62	//�{�^��(������)
		|| block_type == 68	//�}���z�[���̊W
		|| block_type == 69	//�}���z�[���̒�
		|| block_type == 73	//�S�[��
		) {
		return true;
	}
	return false;
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