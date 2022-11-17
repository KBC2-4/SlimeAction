#pragma once


#define MAP_HEIGHT 14
#define MAP_WIDTH 117
#define MAP_CEllSIZE 80

class PLAYER;
class ELEMENT;

class STAGE
{
private:
	
	int stage_image[5];			//�X�e�[�W�w�i�摜
	int halfwaypoint_se;		//���Ԓn�_SE
	float map_x, map_y;			//�}�b�v�`����W
	int clearbox[2];		//�N���A�ɂȂ�{�b�N�X��͈�	0=x,1=y
	int anitimer;
	int halfwaypointbox[2];		//���Ԓn�_����ɂȂ�{�b�N�X��͈�	0=x,1=y
	bool clearflg;			//�N���A����t���O
	bool halfwaypoint;		//���Ԓn�_�t���O
	float player_x_old, player_y_old;		//���v���C���[���W
	float player_vector_x;					//�v���C���[�̈ړ�����x
	float player_vector_y;					//�v���C���[�̈ړ�����y

protected:
	int block_image1[100];		//�X�e�[�W�u���b�N�摜
	static int map_data[MAP_HEIGHT][MAP_WIDTH];
	static float scroll_x, scroll_y;	//�}�b�v�X�N���[����
public:
	STAGE();
	//�}�b�v���̍X�V
	void Update(PLAYER* player, ELEMENT* element);
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
	//��ʃX�N���[�����WY�̎擾
	static float GetScrollY() { return scroll_y; }
	//�}�b�v�f�[�^�̓ǂݍ���
	void LoadMapData(void);	

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };

	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }

	bool HalfwayPoint(PLAYER* player);

	int GetHalfwayPoint(int xy) {if(xy == 0 || xy == 1) return halfwaypointbox[xy]; }
};

