#pragma once


#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class PLAYER;

class STAGE
{
private:
	
	int stage_image[5];			//�X�e�[�W�w�i�摜
	float map_x, map_y;			//�}�b�v�`����W
	int clearbox[2];		//�N���A�ɂȂ�{�b�N�X��͈�	0=x,1=y
	bool clearflg;			//�N���A����t���O
	float player_x_old, player_y_old;		//���v���C���[���W(x�Ay)
	/*int player_vector_x;
	int player_vector_y;*/

protected:
	int block_image1[100];		//�X�e�[�W�u���b�N�摜
	static int map_data[MAP_HEIGHT][MAP_WIDTH];
	static float scroll_x, scroll_y;	//�}�b�v�X�N���[����
public:
	STAGE();
	//�}�b�v���̍X�V
	void Update(PLAYER *player);
	//�X�e�[�W�̕`��
	virtual void Draw() const;
	//�X�e�[�W�̏�����
	//void InitStage();

	//�J�������[�N
	void CameraWork(PLAYER* player);
	
	//�����܂�̏���
	void PuddleProcess();
	//�t�b�N�̏���
	void HookProcess();
	//////�}�b�v�z��̒l���擾
	static int GetMapDat(int y, int x) { return map_data[y][x]; }
	//�}�b�v�̓����蔻�� 
	static bool HitMapDat(int y, int x); 
	//�X���C���̂�����̓����蔻��
	bool HitThrowSlime(int y, int x);
	//��ʃX�N���[�����WX���Z�b�g
	static bool SetScrollPos(int move_x);
	//��ʃX�N���[�����WX�̎擾
	static float GetScrollX() { return scroll_x; };	
	//�}�b�v�f�[�^�̓ǂݍ���
	void LoadMapData(void);	

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };
};

