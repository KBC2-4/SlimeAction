#pragma once
#include "AbstractScene.h"
class STAGE_SELECT :
    public AbstractScene
{
private:

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

