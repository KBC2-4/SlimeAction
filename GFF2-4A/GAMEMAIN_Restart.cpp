#include "GAMEMAIN_Restart.h"
#include "GameMain.h"
#include "DxLib.h"

GAMEMAIN_RESTART::GAMEMAIN_RESTART(bool restart, int halfway_time, const char* stage_name, int now_graph) : AbstractScene(false) {
	this->restart = restart;
	this->halfway_time = halfway_time;
	this->stage_name = stage_name;
	this->now_graph = now_graph;
}

GAMEMAIN_RESTART::~GAMEMAIN_RESTART()
{
	DeleteGraph(now_graph);

}

AbstractScene* GAMEMAIN_RESTART::Update() {
		return new GAMEMAIN(restart, halfway_time, stage_name);
}


void GAMEMAIN_RESTART::Draw()const {
	DrawGraph(0, 0, now_graph, FALSE);
}