#pragma once
#include "AbstractScene.h"

//Aボタンの文字色
#define A_COLOR 0x16F002

//Bボタンの文字色
#define B_COLOR 0xEB7415

//STARTボタンの文字色
#define START_COLOR 0x16F2AC

//BACK(SELECT)ボタンの文字色
#define BACK_COLOR 0x16F2AC

//OK時のバイブレーション設定
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
	static int bgm_vol;        //BGMの音量
	static int se_vol;         //SEの音量
	static bool input_mode;	//入力方式の切り替え
	bool window_mode;//ウィンドウモードの切り替え
	int old_bgm_vol, old_se_vol;
	int selectmenu;     //選択しているメニュー
	bool option_flg;	//オプション画面表示フラグ

public:

	//コンストラクタ
	Option();
	//デストラクタ
	~Option();
	//描画以外の更新を実行
	void Update();
	//描画に関することを実装
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

