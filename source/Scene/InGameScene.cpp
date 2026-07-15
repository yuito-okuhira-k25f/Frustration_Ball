#include"InGameScene.h"
#include"../Object/Circle.h"
#include"../Object/Enemy.h"
#include"../Object/Wall.h"
#include"../Scene/ResultScene.h"
#include"../Utility/Input.h"
#include<DxLib.h>

float count_time;
int stage_SE;
int stage_BGM;

int InGameInit(void)//各プログラムの初期化
{
	if (WallInit() != TRUE)//壁・ゴールの初期化
	{
		return FALSE;//できなかったらゲームを終了する
	}

	CircleInit();//自機の初期化
	EnemyInit();//敵の初期化

	count_time = 0;//タイマーの初期化

	stage_SE = LoadSoundMem("assets/sounds/stage_change.mp3");//ステージ変更時のse読み込み
	stage_BGM = LoadSoundMem("assets/sounds/Fade_away.mp3");
	PlaySoundMem(stage_BGM, DX_PLAYTYPE_LOOP);
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	count_time += delta_second;//InGame状態の秒数を取得

	CircleUpdate(delta_second);//自機の更新
	EnemyUpdate(delta_second);//敵の更新
	WallUpdate();//壁の更新

	if (HitCheckEnemy1() == TRUE)//敵と衝突
	{
		Retry();
	}

	if (HitCheckWall() == 2)//壁と衝突
	{
		Retry();
	}

	if (HitCheckWall() == TRUE)//ゴールに到着した場合、秒数を送り、リザルト画面へ移行する
	{
		ResultTime(count_time);
		StopSoundMem(stage_BGM);
		return eResult;
	}

	if (GetButtonState(XINPUT_BUTTON_A) == ePressed)//Aボタンが押された場合、seを鳴らし画面を変更する
	{
		PlaySoundMem(stage_SE, DX_PLAYTYPE_BACK);
		ChangeStage();
	}

	return eInGame;
}

void InGameDraw(void)
{
	WallDraw();//壁・ゴールの描画
	CircleDraw();//自機の描画
	EnemyDraw();//敵の描画
}