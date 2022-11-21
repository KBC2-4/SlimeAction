#pragma once
#include <Windows.h>
#include <vector>

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
	POINT clearbox;		//�N���A�ɂȂ�{�b�N�X��͈͂̍��W
	int anitimer;
	POINT halfwaypointbox;		//���Ԓn�_���W

	bool clearflg;			//�N���A����t���O
	bool halfwaypoint;		//���Ԓn�_�t���O
	float player_x_old, player_y_old;		//���v���C���[���W
	float player_vector_x;					//�v���C���[�̈ړ�����x
	float player_vector_y;					//�v���C���[�̈ړ�����y

protected:
	int block_image1[100];		//�X�e�[�W�u���b�N�摜
	std::vector<std::vector<int>> map_data;
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
	int GetMapData(int y, int x) { return map_data.at(y).at(x); }
	//�}�b�v�̓����蔻�� );
	bool HitMapDat(int y, int x); 
	//�X���C���̂�����̓����蔻��
	bool HitThrowSlime(int y, int x);
	//��ʃX�N���[�����WX���Z�b�g
	static bool SetScrollPos(int move_x);
	//��ʃX�N���[�����WX�̎擾
	float GetScrollX() { return scroll_x; };	
	//��ʃX�N���[�����WY�̎擾
	float GetScrollY() { return scroll_y; }
	//�}�b�v�f�[�^�̓ǂݍ���
	void LoadMapData(void);	

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };

	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }

	void HalfwayPoint(PLAYER* player);
	//���Ԓn�_���W��Geter
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }

	//���Ԓn�_�ʉ߂���������t���O��Geter
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }
};

