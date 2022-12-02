#pragma once
#include <Windows.h>
#include <vector>

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
	POINT spawn_point;			//�X�|�[���n�_���W

	bool clearflg;			//�N���A����t���O
	int clear_count;		//�X�e�[�W�N���A���̃J�E���g�^�C�}�[
	bool halfwaypoint;		//���Ԓn�_�t���O
	int halfway_timer;		//���Ԓn�_�p�^�C�}�[
	float player_x_old, player_y_old;		//���v���C���[���W
	float player_longold;	//���t���[���O�̃v���C���[���W
	int count_timer;		//�J�E���g�p�^�C�}�[
	float player_vector_x;					//�v���C���[�̈ړ�����x
	float player_vector_y;					//�v���C���[�̈ړ�����y
	float scroll_speed_x;					//�X�N���[���ړ���(x)
	float scroll_speed_y;					//�X�N���[���ړ���(y)

protected:
	int block_image1[110];		//�X�e�[�W�u���b�N�摜
	std::vector<std::vector<int>> map_data;
	float scroll_x, scroll_y;	//�}�b�v�X�N���[����
public:
	STAGE(const char* stage_name = "StageSelect");
	//�}�b�v���̍X�V
	void Update(PLAYER* player, ELEMENT* element);
	//�X�e�[�W�̕`��
	virtual void Draw() const;
	//�X�e�[�W�̏�����
	//void InitStage();

	//�}�b�v�T�C�Y��Geter
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }

	//�}�b�v�摜�ԍ�Geter
	int GetMapImage(int num) { return block_image1[num]; }

	//�J�������[�N
	void CameraWork(PLAYER* player, ELEMENT* element);
	
	//�����܂�̏���
	void PuddleProcess();
	//�t�b�N�̏���
	void HookProcess();
	//////�}�b�v�z��̒l���擾
	int GetMapData(int y, int x);
	//�}�b�v�z��̒l��ݒ�
	void SetMapData(int y, int x, int mapchip_num) { map_data[y][x] = mapchip_num; }
	//�}�b�v�̓����蔻�� 
	bool HitMapDat(int y, int x); 
	//�X���C���̂�����̓����蔻��
	bool HitThrowSlime(int y, int x);
	//��ʃX�N���[�����WX���Z�b�g
	bool SetScrollPos(int move_x);
	//��ʃX�N���[�����WX�̎擾
	float GetScrollX() { return scroll_x; };	
	//��ʃX�N���[�����WY�̎擾
	float GetScrollY() { return scroll_y; }
	//�}�b�v�f�[�^�̓ǂݍ���
	void LoadMapData(const char* stage_name);

	void StageClear(PLAYER* player);

	bool GetClearFlg(void) { return clearflg; };

	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }
	void SetScrollY(float scroll_y) { if (scroll_y < 0) { this->scroll_y = scroll_y; } }

	void HalfwayPoint(PLAYER* player);
	//���Ԓn�_���W��Geter
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }

	//���Ԓn�_�ʉ߂���������t���O��Geter
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }

	//�X�|�[���n�_��Geter
	POINT GetSpawnPoint(void) { return spawn_point; }
};

