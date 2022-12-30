#pragma once
#include "Option.h"

class PAUSE
{
private:
	int pause_graph;
	int pause_effect_timer;
	int cursor_move_se,ok_se, memu_open_se, memu_close_se;
	int menu_font, title_font, buttonguid_font;
	int selectmenu;
	int input_margin;
	int nextmenu;
	bool pause_flg;	//ポーズフラグ

	Option* option;

public:
	PAUSE();
	~PAUSE();
	int Update(void);
	void Draw();
	bool IsPause(void) { return pause_flg; }
	void SetPause(void) { pause_flg = !pause_flg; if (pause_flg == false) { selectmenu = 0; } }
	int GetSelectMenu(void) { return nextmenu; }

	int GetDrawCenterX(const char* string, int font_handle)const;



	enum class MENU
	{
		RETURN,
		RESTART,
		OPTION,
		STAGE_SELECT
	};
};

