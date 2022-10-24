#pragma once

#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int block_image1[100];		//�X�e�[�W�u���b�N�摜
	int stage_image[5];			//�X�e�[�W�w�i�摜
	float map_x, map_y;			//�}�b�v�`����W
	static float scroll_x, scroll_y;	//�}�b�v�X�N���[����

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//�}�b�v���̍X�V
	void Update();
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
	static bool HitMapDat(int y, int x);
	static bool SetScrollPos(int move_x);
	static float GetScrollX() { return scroll_x; };
	void LoadMapData(void);
};

