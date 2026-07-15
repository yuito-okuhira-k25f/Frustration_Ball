#include<DxLib.h>
#include"Wall.h"
#include"Circle.h"
#include"Enemy.h"
#include"../Utility/Input.h"

Wall init_wall{ 0,0 };
Wall stage_wall[STAGE_WALL_Y][STAGE_WALL_X];

int stage_draw[STAGE_DRAW];
int stage;//画面の状態
int stage_number;//Excelの番号

int LoadWallData(void);

int WallInit(void)
{
	int stage_check = LoadDivGraph("assets/images/Stage_Colors.png", STAGE_DRAW, STAGE_DRAW, 1, 20, 20, stage_draw);

	if (stage_check == -1)
	{
		return FALSE;
	}

	stage = TRUE;
	stage_number = 1;

	for (int y = 0; y < STAGE_WALL_Y; y++)//
	{
		for (int x = 0; x < STAGE_WALL_X; x++)
		{
			stage_wall[y][x] = init_wall;
			stage_wall[y][x].x = x * 20;
			stage_wall[y][x].y = y * 20;
		}
	}

	if (LoadWallData() != TRUE)//Excelが読み込めなかった場合、ゲームを終了する
	{
		return FALSE;
	}

	return TRUE;
}

int WallUpdate(void)//壁の更新処理
{
	if (LoadWallData() != TRUE)
	{
		return FALSE;
	}

	return TRUE;
}

void WallDraw(void)//壁・ゴールの描画処理
{
	for (int y = 0; y < STAGE_WALL_Y; y++)
	{
		for (int x = 0; x < STAGE_WALL_X; x++)
		{
			if (stage_wall[y][x].image != NULL)
			{
				DrawGraphF(
					stage_wall[y][x].x,
					stage_wall[y][x].y,
					stage_wall[y][x].image,
					FALSE
				);
			}
		}
	}
}

int LoadWallData(void)
{
	char file_name[256] = {};
	FILE* fp = NULL;
	sprintf_s(file_name, "assets/dat/Book%d.csv", stage_number);

	errno_t result = fopen_s(&fp, file_name, "r");
	if (result != NULL || fp == NULL)
	{
		return FALSE;
	}

	int x = 0, y = 0;

	while (TRUE)
	{
		char c = fgetc(fp);
		if (c == EOF)//ファイル読み込み
		{
			break;
		}
		if (c == '\n')//改行
		{
			x = 0;
			y++;
		}
		if (c == '1')//壁読み込み
		{
			stage_wall[y][x].image = stage_draw[1];
			stage_wall[y][x].draw = 2;
			x++;
		}
		if (c == '2')//ゴール画像読み込み
		{
			stage_wall[y][x].image = stage_draw[2];
			stage_wall[y][x].draw = 3;
			x++;
		}
		else if (c == '0')//
		{
			stage_wall[y][x].image = stage_draw[0];
			stage_wall[y][x].draw = 1;
			x++;
		}
	}

	fclose(fp);

	return TRUE;
}

int HitCheckWall(void)//自機の位置を参照する
{
	Circle circle = ReturnCircle();
	int x = circle.x / 20;
	int y = circle.y / 20;

	if (stage_wall[y][x].draw == 3)//ゴール地点に到着
	{
		return 1;
	}
	if (stage_wall[y][x].draw == stage_number)//壁との衝突
	{
		return 2;
	}

	return FALSE;
}

void ChangeStage(void)//ステージ画面の切り替え
{
	if (stage == TRUE)
	{
		stage = FALSE;
		stage_number = 2;
	}
	else
	{
		stage = TRUE;
		stage_number = 1;
	}

	ChangeEnemy(stage);
}