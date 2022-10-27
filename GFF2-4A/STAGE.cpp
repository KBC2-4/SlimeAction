#include "STAGE.h"
#include "Element.h"
#include"DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int STAGE::map_data[MAP_HEIGHT][MAP_WIDTH];
float STAGE::scroll_x = 0;
float STAGE::scroll_y = 0;

STAGE::STAGE() {
	**map_data = 0;
	*block_image1 = 0;
	*stage_image = 0;
	stage_image[0] = LoadGraph("Resource/Images/Stage/BackImage.png");
	LoadDivGraph("Resource/Images/Stage/map_chips.png", 100, 10, 10, 80, 80, block_image1);
	//InitStage();
	LoadMapData();
}


//void STAGE::Update() {
//
//}

void STAGE::Draw()const {
	printfDx("%f",scroll_x);
	DrawGraph(int(scroll_x)%1920+1920, scroll_y, stage_image[0], FALSE);
	DrawGraph(int(scroll_x) % 1920, scroll_y, stage_image[0], FALSE);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//画面外は描画しない
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280) {
				DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[map_data[i][j] - 1], TRUE);
			}
			
		}
	}
	
}

//void STAGE::InitStage() {
//	FILE *fp = NULL;
//	if ((fopen_s(&fp, "Resource/Map_Data/MapData1.csv", "rt")) != 0) {
//		
//		throw "Resource/Map_Data/MapData1.csv";
//	}
//	for (int i = 0; i < MAP_HEIGHT; i++) {
//		for (int j = 0; j < MAP_WIDTH; j++) {
//			//char c;
//			fscanf_s(fp, "%d", &map_data[i][j]);
//			//map_data[i][j] = c - '0';
//		}
//	}
//	fclose(fp);
//	//if ((fopen_s(&fp, "Resource/Map_Data/MapData_res.csv", "a")) != 0) {
//	//	
//	//	throw "Resource/Map_Data/MapData_res.csv";
//	//}
//	//for (int i = 0; i < MAP_HEIGHT; i++) {
//	//	for (int j = 0; j < MAP_WIDTH; j++) {
//	//		//char c;
//	//		//fscanf_s(fp, "%2d,", &map_data[i][j]);
//	//		fprintf_s(fp, "%2d,", map_data[i][j]);
//	//		//map_data[i][j] = c - '0';
//	//	}
//	//	fprintf_s(fp, "\n");
//	//}
//	//fclose(fp);
//
//
//}



void STAGE::HookProcess() {

}

void STAGE::PuddleProcess(){

}

/// <summary>
/// ステージのスクロール
/// </summary>
bool STAGE::SetScrollPos(int move_x) {
	scroll_x -= 5 * move_x;
	if (scroll_x >= 0 || scroll_x <= -7680) {
		scroll_x += 5 * move_x;
		return true;
	}
	return false;
}

bool STAGE::HitMapDat(int y, int x) {
	if (CheckHitKey(KEY_INPUT_Z))return false;		//デバッグ用
	int block_type = GetMapDat(y, x);
	if (block_type == 0 || block_type == 9 || block_type == 64 || block_type == 62) {
		return false;
	}
	return true;
}

void STAGE::LoadMapData(void) {

		std::ifstream ifs("Resource/Map_Data/MapData1.csv");

		std::string str = "";
		int i = 0, j = 0;
		while (std::getline(ifs,str))
		{
			std::string tmp = "";
			std::istringstream stream(str);

			while (std::getline(stream,tmp,','))
			{
				map_data[i][j] = std::stoi(tmp);
				j++;
			}
			j = 0;
			i++;
		}
}