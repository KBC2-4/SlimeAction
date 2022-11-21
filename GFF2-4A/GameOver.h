#pragma once
#include "AbstractScene.h"
#include "Title.h"

enum class GAMEOVER_MENU
{

	ReSelect=0,	//GameSelect
	NewGame		//Restart
};

class GameOver : public AbstractScene
{
private:
	int GameOverImage;	//�摜�p�ϐ�
	int SelectCount;	//Select�p�ϐ�
	int Select_font;	//Select_font�p�ϐ�
	int Input_WaitTime;	//Selectcursor��WaitTime
	
public:
	//�R���X�g���N�^
	GameOver();
	//�f�X�g���N�^
	~GameOver(){}
	//�`��ȊO�̏���
	AbstractScene* Update() override;
	//�`�揈��
	void Draw() const override;
};