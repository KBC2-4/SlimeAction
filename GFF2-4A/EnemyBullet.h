#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"


class ENEMY_BULLET
{
private:
    int my_x, my_y;                   //この敵の座標
    double bullet_x, bullet_y, hypote;//弾の細かい座標と三角形の斜辺
    double player_x, player_y;        //プレイヤーの座標
    double dis_x, dis_y;              //プレイヤーと敵の距離
    double bullet_sx, bullet_sy;      //弾のX、Yそれぞれのスピード
    int map_x, map_y;
    float mapd_x, mapd_y;
    bool end_flg;                     //弾の消えるアニメーションをするかどうか
    bool bullet_flag;                 //弾を消すかどうか
    double rad_x;                     //角度変更用変数
    float now_scroll_x;
    float old_scroll_x;
    float scroll_x;
    float GetDrawX() const;
    bool delete_flg;
    bool hit_flg;
    int bullet_images[4];
    int bullet_end_images[20];
    double rad;
    int image_index;
    int image;
    int animation_timer;
    int animation_type;
    PLAYER* player;
    STAGE* stage;

    const int ANIMATION_TIMER = 5;
    const int IMAGE_Y_SIZE = 20;
public:
    ENEMY_BULLET();
    ENEMY_BULLET(PLAYER* player, STAGE* aug_stage, int x, int y, double dis, float scroll,double,int);
    ~ENEMY_BULLET() {};

    void Update();
    void Move();
    void Hit();
    /// <summary>
    /// 弾が消えるアニメーション
    /// </summary>
    /// <returns>アニメーションの終了判定</returns>
    bool EndAnimation();
    /// <summary>
    /// 移動アニメーション
    /// </summary>
    void MoveAnimation();
    void Draw() const;

    bool GetDeleteFlg(){return delete_flg;}
};

