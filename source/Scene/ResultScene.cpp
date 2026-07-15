#include"ResultScene.h"
#include<DxLib.h>
#include"../Utility/Input.h"
#include"../Ranking/Ranking.h"

int time;
int return_SE;
int result_SE;

FILE* fp = NULL;

int ResultInit(void)//リザルト初期化
{
	result_SE = LoadSoundMem("assets/sounds/result.mp3");//リザルト画面状態に入る際のse読み込み
	return_SE = LoadSoundMem("assets/sounds/tryA.mp3");
	ResultSE();

	return TRUE;
}

eSceneType ResultUpdate(float delta_second)//リザルト画面更新処理
{

	if (GetButtonState(XINPUT_BUTTON_A) == ePressed)
	{
		StopSoundMem(result_SE);
		PlaySoundMem(return_SE, DX_PLAYTYPE_BACK);
		return eTitle;

	}

	return eResult;
}

void ResultDraw(void)//リザルト画面表示
{
	SetFontSize(60);
	DrawString(470, 200, "Game Clear!", GetColor(255, 255, 255), TRUE);
	SetFontSize(50);
	DrawFormatString(140, 350, GetColor(255, 255, 255), "タイムは%d秒です!Aボタンでタイトルに戻る", time);
}

void ResultTime(float x)
{
	time = (int)x;//秒数の取得
	CheckRankData(time);
}

void ResultSE(void)
{
	PlaySoundMem(result_SE, DX_PLAYTYPE_BACK);//seを鳴らす
}