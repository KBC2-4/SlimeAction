#pragma once
#include "AbstractScene.h"
#include"PLAYER.h"
#include"STAGE.h"
#include"Lemon.h"
#include"GrapeFruit.h"
#include"Tomato.h"
#include "Element.h"
#include "RESULT.h"
#include"ITEMBALL.h"
class GAMEMAIN :
    public AbstractScene
{
private:
	int background_image[5];
	int time;		//�o�ߎ���

	//�����i�[�̐��p�̕ϐ�
	int lemoner_count;

	//�Ƃ܂Ƃ�̐��p�̕ϐ�
	int tomaton_count;

	//�O���|���̐��p�̕ϐ�
	int gurepon_count;

	//�A�C�e���̐��p�ϐ�
	int item_count;

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	LEMON** lemoner;	//�����i�[
	GRAPEFRUIT** gurepon;	//�O���ۂ�
	TOMATO** tomaton;	//�Ƃ܃g��
	ITEMBALL** item;     //�A�C�e��
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

