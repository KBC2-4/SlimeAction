#pragma once
#include "Option.h"

class PAUSE
{
private:
	int cursor_move_se,ok_se;
	int menu_font, title_font, buttonguid_font;
	int selectmenu;
	int nextmenu;
	bool pause_flg;	//ポーズフラグ

	Option* option;

public:
	PAUSE();
	~PAUSE();
	int Update(void);
	void Draw(int pause_graph);
	bool IsPause(void) { return pause_flg; }
	void SetPause(void) { pause_flg = !pause_flg; if (pause_flg == false) { selectmenu = 0; } }
	int GetSelectMenu(void) { return nextmenu; }

	int GetDrawCenterX(const char* string, int font_handle)const;
};

