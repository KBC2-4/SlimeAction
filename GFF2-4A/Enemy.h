#pragma once

enum class CITRUS_STATE
{
	IDOL = 0,	//�A�C�h�����
	MOVE,		//�v���C���[��W�������킹�����Ă���Ƃ�
	STANDBY,	//���ˏ���
	RETURN,		//���ˉ\��Ԃɖ߂�
	PRESS		//���ˏ��
};

class ENEMY
{
protected:
	int x, y;			//���W
	int map_x, map_y;	//�}�b�v���ł̍��W
	int image;			//�摜

public:

	/// <summary>
	/// �ړ�
	/// </summary>
	virtual void Move() = 0;
	/// <summary>
	/// �ʏ`�𔭎�
	/// </summary>
	virtual void ShotFruitJuice() = 0;
	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	virtual void Animation() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw()const = 0 ;
	
};

