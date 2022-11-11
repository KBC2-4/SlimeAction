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
    bool bullet_flag;                 //弾を消すかどうか
    double rad_x;                     //角度変更用変数
    float now_scroll_x;
    float old_scroll_x;
    float scroll_x;
    float GetDrawX() const;
    bool delete_flg;
    PLAYER* player;
    STAGE* stage;

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis, float scroll);
    ~ENEMYBULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// アニメーション
    /// </summary>
    void Animation();
    void Draw() const;

    bool GetDeleteFlg(){return delete_flg;}
};

