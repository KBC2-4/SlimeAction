#pragma once

class AbstractScene
{
public:
	//�f�X�g���N�^
	virtual ~AbstractScene() {};
	//�`��ȊO�̍X�V�����s
	virtual AbstractScene* Update() = 0;
	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const = 0;

	int GetDrawCenterX(const char* string, int font_handle)const;
};