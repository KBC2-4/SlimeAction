#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"

class STAGE_SELECT :
    public AbstractScene
{
private:
	//�w�i�摜
	int background_image[5];

	PLAYER* player;	//�v���C���[
	STAGE* stage;	//�X�e�[�W
	ELEMENT* element;	//�X�e�[�W���v�f

	float player_map_x, player_map_y;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	STAGE_SELECT();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~STAGE_SELECT();
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

