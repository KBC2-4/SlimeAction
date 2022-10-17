#pragma once

#define MAP_HEIGHT 9
#define MAP_WIDTH 48
#define MAP_CEllSIZE 80

class STAGE
{
private:
	int image1[100];
	float map_x, map_y;			//�}�b�v�`����W
	static float scroll_x, scroll_y;	//

	static int map_data[MAP_HEIGHT][MAP_WIDTH];
public:
	STAGE();
	//�}�b�v���̍X�V
	void Update(float player_x,float player_y);
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
	static void SetScrollPos(int move_type);
	static float GetScrollX() { return scroll_x; };
};

