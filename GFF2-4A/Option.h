#pragma once
#include "AbstractScene.h"

//A�{�^���̕����F
#define A_COLOR 0x16F002

//B�{�^���̕����F
#define B_COLOR 0xEB7415

//START�{�^���̕����F
#define START_COLOR 0x16F2AC

//BACK(SELECT)�{�^���̕����F
#define BACK_COLOR 0x16F2AC

//OK���̃o�C�u���[�V�����ݒ�
#define OK_VIBRATION_POWER	130
#define OK_VIBRATION_TIME	150

class Option
{

private:

	enum class MENU
	{
		WindowMode,
		BGM,
		SE,
		RETURN
	};

	int menu_font, buttonguid_font;
	int cursor_move_se, ok_se, mute_se;
	int input_margin;
	static int bgm_vol;        //BGM�̉���
	static int se_vol;         //SE�̉���
	static bool input_mode;	//���͕����̐؂�ւ�
	bool window_mode;//�E�B���h�E���[�h�̐؂�ւ�
	int old_bgm_vol, old_se_vol;
	int selectmenu;     //�I�����Ă��郁�j���[
	bool option_flg;	//�I�v�V������ʕ\���t���O

public:

	//�R���X�g���N�^
	Option();
	//�f�X�g���N�^
	~Option();
	//�`��ȊO�̍X�V�����s
	void Update();
	//�`��Ɋւ��邱�Ƃ�����
	void Draw();

	static int GetBGMVolume(void) { return bgm_vol; }
	static int GetSEVolume(void) { return se_vol; }
	bool GetOptionFlg(void) { return option_flg; }
	void ChangeOptionFlg(void) { option_flg = !option_flg; }
	static bool GetInputMode(void) { return input_mode; }

	void LoadData(void);
	void SaveData(void);


	int GetDrawCenterX(const char* string, int font_handle)const;
};

