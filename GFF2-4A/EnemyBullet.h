#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"
#define BULLET_SPEED 12

class ENEMY_BULLET
{
private:
    int my_x, my_y;                   //この敵の座標
    int draw_x;                       //壁に当たった時に描画場所をずらすための変数
    double bullet_x, bullet_y, hypote;//弾の細かい座標と三角形の斜辺
    double player_x, player_y;        //プレイヤーの座標
    double dis_x, dis_y;              //プレイヤーと敵の距離
    double bullet_sx, bullet_sy;      //弾のX、Yそれぞれのスピード
    int map_x, map_y;                 //弾のマップ上のX, Y（int型）
    float mapd_x, mapd_y;             //弾のマップ上のX,Y（double）
    int o_map_x, o_map_y;             //弾のマップ上の古い座標
    bool end_flg;                     //弾の消えるアニメーションをするかどうか
    double rad_x;                     //角度変更用変数
    float scroll_x;                   //スクロールの値(x)
    float scroll_y;                   //スクロールの値(y)
    bool delete_flg;                  //デリートするためのフラグ
    bool hit_flg;                     //プレイヤーの投げたボールに当たったかどうかのフラグ
    bool right_side_hit;              //物体の右側面に当たったかどうかのフラグ
    bool left_side_hit;               //物体の左側面にあたったかどうかのフラグ
    double hit_rad;                   //弾が物体に当たった時にでるアニメーションの角度の変数
    int bullet_images[4];             //弾のアニメーション用の変数
    int bullet_end_images[20];        //弾が地面に当たった時にでるアニメーションの変数
    double rad;                       //角度の変数
    int image_index;                  //画像の判別用の変数
    int image;                        //画像の変数
    int animation_timer;              //アニメーションの時間
    int animation_type;               //アニメーションの判別
    int splash_se;                    //弾けるときのSE

    PLAYER* player;                   //プレイヤーのクラスの変数
    STAGE* stage;                     //ステージのクラスの変数

    const int ANIMATION_TIMER = 5;    //アニメーションの時間
    const int IMAGE_Y_SIZE = 20;      //画像の縦のサイズ

private:
    float GetDrawX() const;           //スクロールの値を計算する関数
    float GetDrawY() const;           //スクロールの値を計算する関数

public:
    ENEMY_BULLET();                   //最初のコンストラクタ
    ENEMY_BULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis,double,int); //引数アリのコンストラクタ
    ~ENEMY_BULLET();               //デストラクタ

    void Update();                    //弾のアップデート
    void Move();                      //弾の動き
    void Hit();                       //弾の当たり判定
    /// <summary>
    /// 弾が消えるアニメーション
    /// </summary>
    /// <returns>アニメーションの終了判定</returns>
    bool EndAnimation();
    /// <summary>
    /// 移動アニメーション
    /// </summary>
    void MoveAnimation();
    void Draw() const;                 //弾の描画
    bool GetDeleteFlg(){return delete_flg;}//デリートフラグのゲット
};

