#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"
class ENEMYBULLET
{
private:
    int my_x, my_y;                   //この敵の座標
    double bullet_x, bullet_y, hypote;//弾の細かい座標と三角形の斜辺
    double player_x, player_y;        //プレイヤーの座標
    double dis_x, dis_y;              //プレイヤーと敵の距離
    double bullet_sx, bullet_sy;      //弾のX、Yそれぞれのスピード
    int map_x, map_y;
    float mapd_x, mapd_y;
    bool Hit_flg;                 //弾を消すかどうか
    double rad_x;                     //角度変更用変数
    float scroll_x;
    int i = 0;
    double cos_x = 0.0;
    double sin_y = 0.0;
    PLAYER* player;
    STAGE* stage;

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player, STAGE*, int x, int y, double dis, float);
    ~ENEMYBULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// アニメーション
    /// </summary>
    void Animation();
    void Draw() const;

    bool GetHitFlg(){return Hit_flg;}

};

