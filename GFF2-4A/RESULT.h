#pragma once
#include "AbstractScene.h"

class RESULT : public AbstractScene
{
private:
	int clear_background_image,gameover_background_image;
	int title_font, menu_font;
	int timer;
	int count;
	bool win;

public:
	RESULT(bool issue);
	~RESULT();
	AbstractScene* Update() override;
	void Draw() const override;
};

