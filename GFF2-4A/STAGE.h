#pragma once

#define MAP_HEIGHT 9
#define MAP_WIDTH 16
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int image1[100];

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//�X�e�[�W�̕`��
	void Draw() const;
	//�X�e�[�W�̏�����
	void InitStage();
	//�{�^���̏���
	void ButtonProcess();
	//�����܂�̏���
	void PuddleProcess();
	//�t�b�N�̏���
	void HookProcess();
	////�}�b�v�f�[�^�擾�֐�
	static int GetMapDat(int y, int x) { return map_data[y][x]; }
};

