#pragma once
#include "AbstractScene.h"
#include "Title.h"

enum class GAMEOVER_MENU
{


	NewGame = 0,		//Restart
	ReSelect			//GameSelect
};

class GameOver : public AbstractScene
{
private:
	int title_image,background_image;
	int selectmenu;
	int menu_font;
	int guid_font;
	int background_music;
	int bad_se[4], ok_se, cursor_move_se;
	int input_margin;
	int timer,se_randnum;
	const char* stage_name;	//���X�^�[�g���̃X�e�[�W�I��p
	
public:
	//�R���X�g���N�^
	GameOver(const char* stage_name);
	//�f�X�g���N�^
	~GameOver();
	//�`��ȊO�̏���
	AbstractScene* Update() override;
	//�`�揈��
	void Draw() const override;
};