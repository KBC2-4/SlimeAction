#pragma once
#include "AbstractScene.h"
#include "PLAYER.h"
#include "STAGE.h"
#include "Lemon.h"

class STAGE_SELECT :
	public AbstractScene
{
private:
	//背景画像
	int background_image[5];
	//BGM
	int background_music;

	int ok_se;
	//フォント
	int guid_font, buttonguid_font, stagename_font, move_to_title_font;
	int guid_timer;		//ガイド表示タイマー
	bool effect_delta;
	int effect_timer[2];	//[0:出現エフェクト, 1:ステージポータルエフェクト]

	//チュートリアル用
	int joys_anitimer;
	bool joystick_delta;

	PLAYER* player;	//プレイヤー
	STAGE* stage;	//ステージ
	ELEMENT* element;	//ステージ内要素
	LEMON** lemoner;	//レモナー
	int lemoner_count;

	float player_map_x, player_map_y;	//プレイヤーマップ内座標計算用
	POINT stage_return;		//タイトルへ戻る座標
	POINT stage_move[4];	//ステージポータル座標

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

	/// <summary>
	/// ステージに入る時のUpdate
	/// </summary>
	void StageIn(void);
	/// <summary>
	/// ステージに入る時のアニメーション
	/// </summary>
	void StageIn_Animation(void);
	/// <summary>
	/// ステージポータルガイド表示
	/// </summary>
	/// <param name="stage_name">表示したい文字</param>
	/// <param name="x">描画位置X</param>
	/// <param name="y">描画位置Y</param>
	/// <param name="stagename_font">表示する文字のフォント</param>
	/// <param name="text_color">表示する文字色</param>
	/// <param name="textback_color">表示する文字の輪郭色 (-1の場合は0xFFFFFF)</param>
	/// <param name="text_margin_x">表示する文字X位置を誤差修正 (デフォルトは0)</param>
	/// <param name="text_margin_y">表示する文字Y位置を誤差修正 (デフォルトは0)</param>
	/// <param name="backcolor">描画する楕円の色 (-1の場合は0xFFFFFF)</param>
	/// <param name="second_title">2番目に表示する文字 (""空白で無効化)</param>
	/// <param name="secont_margin_x">2番目に表示する文字X位置を誤差修正 (デフォルトは0)</param>
	/// <param name="secont_margin_y">2番目に表示する文字Y位置を誤差修正 (デフォルトは25 : 0にするとstage_nameと重なる)</param>
	void DrawStageGuid(const char* stage_name, const float x, const float y, const int stagename_font, const int text_color, const int textback_color = -1,
		const int text_margin_x = 0, const int text_margin_y = 0, const int backcolor = -1, const char* second_title = "", const int secont_margin_x = 0, const int secont_margin_y = 25) const;
};

