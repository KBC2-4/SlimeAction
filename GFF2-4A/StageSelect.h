#pragma once
#include "AbstractScene.h"
class STAGE_SELECT :
    public AbstractScene
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	STAGE_SELECT();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~STAGE_SELECT();
	/// <summary>
	/// 描画以外の更新を実行
	/// </summary>
	/// <returns>シーンのアドレスを返す</returns>
	AbstractScene* Update() override;
	/// <summary>
	/// 描画に関することを実装
	/// </summary>
	void Draw() const override;
};

