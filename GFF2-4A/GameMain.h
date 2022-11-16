#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"
#include "Element.h"
#include "RESULT.h"

class GAMEMAIN :
    public AbstractScene
{
private:
	int background_image[5];
	int title_font, menu_font;	//�t�H���g
	int cursor_move_se, ok_se;	//SE
	int selectmenu;				//�I��p
	int time;		//�o�ߎ���
	int halfway_time; //���Ԓn�_�o�ߎ��̎���
	bool pause_flg;	//�|�[�Y�t���O

	//�����i�[�̐��p�̕ϐ�
	int lemoner_count;

	//�Ƃ܂Ƃ�̐��p�̕ϐ�
	int tomaton_count;

	//�O���|���̐��p�̕ϐ�
	int gurepon_count = 0;

	bool restart;	//�����t���O

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	LEMON** lemoner;	//�����i�[
	GRAPEFRUIT** gurepon;	//�O���ۂ�
	TOMATO** tomaton;	//�Ƃ܃g��
	ELEMENT* element;	//�X�e�[�W���v�f
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GAMEMAIN(bool restert = false);
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
};

