#pragma once
class PAUSE
{
private:
	int cursor_move_se,ok_se;
	int menu_font, title_font;
	int selectmenu;
	bool pause_flg;	//ポーズフラグ

public:
	PAUSE();
	~PAUSE();
	int Update(void);
	void Draw(int pause_graph);
	bool IsPause(void) { return pause_flg; }
	void SetPause(void) { pause_flg = !pause_flg; if (pause_flg == false) { selectmenu = 0; } }
};

