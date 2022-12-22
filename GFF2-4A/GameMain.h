#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"
#include "Lemon.h"
#include "GrapeFruit.h"
#include "Tomato.h"
#include "Element.h"
#include "RESULT.h"
#include "PAUSE.h"
#include "ITEMBALL.h"
class GAMEMAIN :
    public AbstractScene
{
private:
	//�w�i�摜
	int background_image[3];
	int background_music[3];		//BGM
	int start_time_font, time_font;	//�t�H���g
	int cursor_move_se, ok_se;	//SE
	int start_time;		//�J�n�܂ł̒x������
	int start_effect_timer;
	int elapsed_time;	//�o�ߎ���
	const char* stage_name;	//���X�^�[�g���̃X�e�[�W�I��p

	//�v���C���[�̃��C�t�̉摜
	int hp_img;

	//�����i�[�̐��p�̕ϐ�
	int lemoner_count;

	//�Ƃ܂Ƃ�̐��p�̕ϐ�
	int tomaton_count;

	//�O���|���̐��p�̕ϐ�
	int gurepon_count;

	//�A�C�e���̐��p�ϐ�
	int item_count;
	int item_num;
	int item_rand;

	bool restart;	//�����t���O

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	PAUSE* pause;	//�|�[�Y
	LEMON** lemoner;	//�����i�[
	GRAPEFRUIT** gurepon;	//�O���ۂ�
	TOMATO** tomaton;	//�Ƃ܃g��
	ITEMBALL** item;     //�A�C�e��
	ELEMENT* element;	//�X�e�[�W���v�f
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GAMEMAIN(bool restert = false, int halfway_time = 0, const char* stage_name = "StageSelect");
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GAMEMAIN();
	/// <summary>
	/// �`��ȊO�̍X�V�����s
	/// </summary>
	/// <returns>�V�[���̃A�h���X��Ԃ�</returns>
	AbstractScene* Update() override;
	/// <summary>
	/// �`��Ɋւ��邱�Ƃ�����
	/// </summary>
	void Draw() const override;

	void ItemTrunc();
};

