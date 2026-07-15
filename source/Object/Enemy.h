#pragma once

struct ENEMY//座標・動き・大きさ・表示
{
	float ex;
	float ey;
	int move;
	int size;
	int mode;
};

struct HIT//自機の座標
{
	float hx;
	float hy;
};

#define ENEMYCOUNT (6)//敵の数

void EnemyInit(void);
void EnemyUpdate(float delta_second);
void EnemyDraw(void);
int HitCheckEnemy1(void);
void ChangeEnemy(int x);