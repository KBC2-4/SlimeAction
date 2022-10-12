#pragma once

#define MAP_HEIGHT 18
#define MAP_WIDTH 32

class STAGE
{
private:
	int image1[100];
	int image2[100];
	int image3[100];
	int image4[100];
	int image5[100];
	int stage;
	int stage_map[36][32];
public:
	STAGE();
	//ステージの描画
	void Draw() const;
	//ボタンの処理
	void ButtonProcess();
	//水たまりの処理
	void PuddleProcess();
	//フックの処理
	void HookProcess();
};

