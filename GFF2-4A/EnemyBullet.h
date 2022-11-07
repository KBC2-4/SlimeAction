#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
class ENEMYBULLET :
    public ENEMY
{
private:    
    int my_x, my_y;                   //この敵の座標
    double bullet_x, bullet_y, hypote;//弾の細かい座標と三角形の斜辺
    double player_x, player_y;        //プレイヤーの座標
    double dis_x, dis_y;              //プレイヤーと敵の距離
    double bullet_sx, bullet_sy;      //弾のX、Yそれぞれのスピード
    bool bullet_flag;                 //弾を消すかどうか

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player,int x,int y);
    ~ENEMYBULLET() {};

    void Update() override;
    void Move() override;
    void Hit()override;
    /// <summary>
    /// アニメーション
    /// </summary>
    void Animation()override;
    void Draw() const override;

};

