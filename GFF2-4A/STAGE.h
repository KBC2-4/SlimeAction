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
	std::vector<std::vector<int>> door_info;
	std::vector<std::vector<int>> button_info;
	float scroll_x, scroll_y;	//�}�b�v�X�N���[����
	int temporary_hit;		//�ꎞ�I�ȓ����蔻��
	const char* stage_name;		//�X�e�[�W��
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	STAGE(const char* stage_name = "StageSelect", bool restert = false);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~STAGE();
	/// <summary>
	/// �X�e�[�W�̍X�V
	/// </summary>
	void Update(PLAYER* player, ELEMENT* element);
	/// <summary>
	/// �X�e�[�W�̕`��
	/// </summary>
	virtual void Draw(ELEMENT* element) const;
	/// <summary>
	/// �}�b�v�摜�ԍ�Geter
	/// </summary>
	/// <returns>int�^�F�摜�����ԍ�</returns>	
	int GetMapImage(int num) { return block_image1[num]; }
	/// <summary>
	/// �}�b�v�f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="stage_name">�X�e�[�W�̃C���X�^���X</param>
	void LoadMapData(const char* stage_name);
	/// <summary>
	/// �}�b�v�T�C�Y��Geter
	/// </summary>
	/// <returns>�\���̌^�F�}�b�v�T�C�Y</returns>	
	POINT GetMapSize(void) { POINT mapsize{ map_data.size(),map_data.at(0).size(), };  return mapsize; }
	/// <summary>
	/// �}�b�v�z���Getter
	/// </summary>
	/// <param name="y">�}�b�v�f�[�^�̉��v�f��</param>
	/// <param name="x">�}�b�v�f�[�^�̏c�v�f��</param>
	/// <returns>int�^�F�}�b�v�z��ԍ�</returns>	
	int GetMapData(int y, int x);
	/// <summary>
	/// �}�b�v�z��̒l��Setter
	/// </summary>
	/// <param name="y">�}�b�v�f�[�^�̉��v�f��</param>
	/// <param name="x">�}�b�v�f�[�^�̏c�v�f��</param>
	/// <param name="mapchip_num">�}�b�v�z��ԍ�</param>
	void SetMapData(int y, int x, int mapchip_num) { map_data[y][x] = mapchip_num; }


	/// <summary>
	/// �J�������[�N
	/// </summary>
	/// 	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	/// <param name="element">�G�������g�̃C���X�^���X</param>
	void CameraWork(PLAYER* player, ELEMENT* element);
	/// <summary>
	/// �X�N���[��X��Setter
	/// </summary>
	void SetScrollX(float scroll_x) { if (scroll_x < 0) { this->scroll_x = scroll_x; } }
	/// <summary>
	/// �X�N���[��Y��Setter
	/// </summary>
	void SetScrollY(float scroll_y) { if (scroll_y < 0) { this->scroll_y = scroll_y; } }
	/// <summary>
	/// ��ʃX�N���[�����WX��Setter
	/// </summary>
	bool SetScrollPos(int move_x);
	/// <summary>
	/// ��ʃX�N���[�����WX��Getter
	/// </summary>
	float GetScrollX() { return scroll_x; };
	/// <summary>
	/// ��ʃX�N���[�����WY��Getter
	/// </summary>
	float GetScrollY() { return scroll_y; }


	/// <summary>
	/// �}�b�v�̓����蔻��
	/// </summary>
	/// <param name="y">�}�b�v�f�[�^�̉��v�f��</param>
	/// <param name="x">�}�b�v�f�[�^�̏c�v�f��</param>
	bool HitMapDat(int y, int x);
	/// <summary>
	/// �X���C���̂�����̓����蔻��
	/// </summary>
 	/// <param name="y">�}�b�v�f�[�^�̉��v�f��</param>
	/// <param name="x">�}�b�v�f�[�^�̏c�v�f��</param>
	bool HitThrowSlime(int y, int x);

	/// <summary>
	/// �X�|�[���n�_���W��Getter
	/// </summary>
	/// <returns>�\���̌^�F�X�|�[���n�_���W</returns>	
	POINT GetSpawnPoint(void) { return spawn_point; }
	/// <summary>
	/// �X�e�[�W�N���A���菈��
	/// </summary>
	void StageClear(PLAYER* player);
	/// <summary>
	/// �N���A�������̃t���O��Getter
	/// </summary>
	bool GetClearFlg(void) { return clearflg; };
	/// <summary>
	/// ���Ԓn�_���菈��
	/// </summary>
	void HalfwayPoint(PLAYER* player);
	/// <summary>
	/// ���Ԓn�_���W��Getter
	/// </summary>
	/// <returns>�\���̌^�F���Ԓn�_���W</returns>	
	POINT GetHalfwayPoint(void) {return POINT(halfwaypointbox); }
	/// <summary>
	/// ���Ԓn�_�ʉ߂���������t���O��Getter
	/// </summary>
	bool GetHalfwayPointFlg(void) { return halfwaypoint; }
	/// <summary>
	/// �ꎞ�I�ȓ����蔻���Setter
	/// </summary>
	/// <param name="mapdata">�}�b�v�z��ԍ�</param>
	void SetTemporary_Hit(int mapdata) { temporary_hit = mapdata; }
};

