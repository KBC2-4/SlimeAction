#include "STAGE.h"
#include"DxLib.h"

int STAGE::map_data[MAP_HEIGHT][MAP_WIDTH];

STAGE::STAGE() {
	**map_data = { 0 };
	*image1 = { 0 };
	LoadDivGraph("Resource/Images/Stage/StageBlock.png",4,4,1,40,40,image1);
	InitStage();
}


void STAGE::Draw()const {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map_data[i][j] == 1) {
				DrawGraph(j * MAP_CEllSIZE, i * MAP_CEllSIZE, image1[0], TRUE);
			}
			else if (map_data[i][j] == 2) {
				DrawGraph(j * MAP_CEllSIZE, i * MAP_CEllSIZE, image1[3], TRUE);
			}
		}
	}
	
}

void STAGE::InitStage() {
	FILE *fp = NULL;
	if ((fopen_s(&fp, "data/Map_Data/MapData_1.txt", "r")) != 0) {
		
		throw "data/Map_Data/MapData_1.txt";
	}
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH+1; j++) {
			char c;
			fscanf_s(fp, "%c", &c);
			/*if (c == '0') {
				map_data[i][j] = 0;
			}
			else {
				map_data[i][j] = 1;
			}*/
			//if (j == 31) {
			//	map_data[i][j] = c - '0';
			//}
			map_data[i][j] = c - '0';
		}
	}
}

void STAGE::ButtonProcess() {

}

void STAGE::HookProcess() {

}

void STAGE::PuddleProcess(){

}