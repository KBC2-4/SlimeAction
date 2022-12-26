#pragma once
#include "AbstractScene.h"


class GAMEMAIN_RESTART : public AbstractScene
{
private:
	int now_graph;
	bool restart;
	int halfway_time;
	const char* stage_name;

public:
	//コンストラクタ
	GAMEMAIN_RESTART(bool restart = false, int halfway_time = 0, const char* stage_name = "StageSelect", int now_graph = 0);
	~GAMEMAIN_RESTART();

	AbstractScene* Update() override;

	void Draw() const override;
};

