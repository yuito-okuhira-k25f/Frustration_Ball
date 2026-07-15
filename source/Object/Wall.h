#pragma once

#define STAGE_WALL_X (64)//画面サイズ/20した数
#define STAGE_WALL_Y (36)//画面サイズ/20した数
#define STAGE_DRAW (3)

struct Wall//二次元配列を利用した座標・画像読み込み
{
	int x;
	int y;
	int image;
	int draw;
};

int WallInit(void);
int WallUpdate(void);
void WallDraw(void);
int LoadWallData(void);
int HitCheckWall(void);
void ChangeStage(void);

