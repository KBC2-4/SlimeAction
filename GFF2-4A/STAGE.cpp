#include "STAGE.h"
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


void STAGE::Update() {
	//scroll_x-=10;
	//map_x = player_x - float((MAP_WIDTH/3 + 2) / 2 - 1);
	//map_x++;
	//map_y = player_y - float((MAP_HEIGHT + 2) / 2 - 1);
}

void STAGE::Draw()const {
	printfDx("%f",scroll_x);
	DrawGraph(scroll_x, scroll_y, stage_image[0], FALSE);

	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//DrawFormatString(200+j*30, 50+i*30, 0xffffff, "%3d ", map_data[i + int(map_x)][j + int(map_y)]);
			//画面外は描画しない
			/*if (j + map_x<0 || i + map_y<0 || j + map_x>MAP_WIDTH * MAP_CEllSIZE || i + map_y>MAP_HEIGHT * MAP_CEllSIZE)
				continue;*/
			if (j * MAP_CEllSIZE + scroll_x >= -80 && j * MAP_CEllSIZE + scroll_x <= 1280) {
				int NotDraw[] = { 5,6,7,10 };
				/*if(map_data[i][j] != 0 && map_data[i][j] <= 4)*/DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[map_data[i][j] - 1], TRUE);
			}

				/*if (map_data[i][j] == 1) {
					DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[0], TRUE);
				}
				else if (map_data[i][j] == 2) {
					DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[1], TRUE);
				}
				else if (map_data[i][j] == 3) {
					DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[2], TRUE);
				}
				else if (map_data[i][j] == 4) {
					DrawGraph(j * MAP_CEllSIZE + scroll_x, i * MAP_CEllSIZE, block_image1[3], TRUE);
				}*/
			
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

void STAGE::ButtonProcess() {

}

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
	if (block_type == 0 || block_type == 9 || block_type == 64) {
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