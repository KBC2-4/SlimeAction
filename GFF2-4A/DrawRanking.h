#pragma once
#include "AbstractScene.h"

class DRAW_RANKING :
	public AbstractScene
{
private:
	int wait_time;
	int best_time[3];
	int title_font,time_font;
	int image;
	int ok_se;
	int background_image;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DRAW_RANKING();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DRAW_RANKING();
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

