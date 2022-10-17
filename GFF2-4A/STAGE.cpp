#include "STAGE.h"
#include"DxLib.h"

int STAGE::map_data[MAP_HEIGHT][MAP_WIDTH];
float STAGE::scroll_x = 0;
float STAGE::scroll_y = 0;

STAGE::STAGE() {
	**map_data = { 0 };
	*image1 = { 0 };
	LoadDivGraph("Resource/Images/Stage/StageBlock.png",8,8,1,80,80,image1);
	InitStage();
}


void STAGE::Update(float player_x,float player_y) {
	//map_x = player_x - float((MAP_WIDTH/3 + 2) / 2 - 1);
	//map_x++;
	//map_y = player_y - float((MAP_HEIGHT + 2) / 2 - 1);
}

void STAGE::Draw()const {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			//DrawFormatString(200+j*30, 50+i*30, 0xffffff, "%3d ", map_data[i + int(map_x)][j + int(map_y)]);
			//‰æ–ÊŠO‚Í•`‰æ‚µ‚È‚¢
			/*if (j + map_x<0 || i + map_y<0 || j + map_x>MAP_WIDTH * MAP_CEllSIZE || i + map_y>MAP_HEIGHT * MAP_CEllSIZE)
				continue;*/

			if (map_data[i ][j ] == 1) {
				DrawGraph(j*MAP_CEllSIZE+scroll_x, i*MAP_CEllSIZE, image1[0], TRUE);
			}
			else if (map_data[i][j ] == 2) {
				DrawGraph(j * MAP_CEllSIZE+scroll_x , i*MAP_CEllSIZE , image1[3], TRUE);
			}
			
		}
	}
	
}

void STAGE::InitStage() {
	FILE *fp = NULL;
	if ((fopen_s(&fp, "Resource/Map_Data/MapData_1.txt", "r")) != 0) {
		
		throw "Resource/Map_Data/MapData_1.txt";
	}
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH+1; j++) {
			char c;
			fscanf_s(fp, "%c", &c);
			
			map_data[i][j] = c - '0';
		}
	}
	fclose(fp);
}

void STAGE::ButtonProcess() {

}

void STAGE::HookProcess() {

}

void STAGE::PuddleProcess(){

}

void STAGE::SetScrollPos(int move_type) {
	if (move_type ==0) {
		scroll_x--;
	}
	else {
		scroll_x++;
	}
}