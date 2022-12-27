#pragma once
#include "AbstractScene.h"
#include "STAGE.h"
#include "GameOver.h"
#include "PadInput.h"
#include "Option.h"

enum class MENU
{
	GAME_SELECT = 0,
	RANKING,
	OPTION,
	END
};
class Title : public AbstractScene
{
private:

	int background_image;
	int background_music;
	int cursor_move_se, ok_se,exit_se;
	int title_font, menu_font, guid_font;
	int selectmenu;
	int input_margin;
	int timer;
	bool exit_flg;

	int title_anitimer[2];

	Option* option;

public:

	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();
	//�`��ȊO�̍X�V�����s
	AbstractScene* Update() override;
	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const override;
};