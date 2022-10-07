#pragma once

class AbstractScene
{
public:
	//デストラクタ
	virtual ~AbstractScene() {};
	//描画以外の更新を実行
	virtual AbstractScene* Update()=0;
	//描画に関することを実装
	virtual void Draw() const = 0;
};