#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"
#include "Element.h"

class GAMEMAIN :
    public AbstractScene
{
private:
	int background_image[5];
	float time;		//�o�ߎ���

	//�Ƃ܂Ƃ�̐��p�̕ϐ�
	int tomaton_count = 0;

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	LEMON* lemonner;	//�����i�[
	GRAPEFRUIT* gurepon;	//�O���ۂ�
	TOMATO** tomaton;	//�Ƃ܂Ƃ�
	ELEMENT* element;	//�X�e�[�W���v�f
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GAMEMAIN();
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

