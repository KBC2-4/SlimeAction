#pragma once
#include"Enemy.h"
#include<math.h>
#include"DxLib.h"
#include"PLAYER.h"
#include"STAGE.h"

#define BULLET_SPEED 10
class ENEMYBULLET
{
private:
    double x, y;//弾の細かい座標と三角形の斜辺
    int map_x, map_y;
    double player_x, player_y;
    float scroll_x;
    double rad;
    bool delete_flg;
    PLAYER* player;
    STAGE* stage;

public:
    ENEMYBULLET();
    ENEMYBULLET(PLAYER* player, STAGE*, int x, int y, double rad, float);
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

