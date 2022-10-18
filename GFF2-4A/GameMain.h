#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"

class GAMEMAIN :
    public AbstractScene
{
private:

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	LEMON* lemonner;	//�����i�[
	GRAPEFRUIT* gurepon;	//�O���ۂ�
	TOMATO* tomaton;	//�Ƃ܂Ƃ�
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

