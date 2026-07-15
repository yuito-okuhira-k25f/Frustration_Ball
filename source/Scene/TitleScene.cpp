#include"TitleScene.h"
#include"../Utility/Input.h"
#include"../Ranking/Ranking.h"
#include<DxLib.h>

int title_se;
int title_bgm;
int start_white;
int start_black;
float title_time;

int TitleInit(void)//タイトルの初期化
{
	title_se = LoadSoundMem("assets/sounds/tryA.mp3");
	title_bgm = LoadSoundMem("assets/sounds/EDIT.mp3");
	PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP);
	int title_check = LoadRankData();
	SortRankData();

	if (title_check != TRUE)
	{
		return FALSE;
	}
	return TRUE;
}

eSceneType TitleUpdate(float delta_second)//タイトル更新処理
{
	title_time += delta_second;

	if ((int)title_time % 2 == 0)
	{
		start_white = GetColor(255, 255, 255);
		start_black = GetColor(0, 0, 0);
	}
	else
	{
		start_white = GetColor(0, 0, 0);
		start_black = GetColor(255, 255, 255);
	}
	ColorRankW(start_white);
	ColorRankB(start_black);

	if (GetButtonState(XINPUT_BUTTON_A))
	{
		PlaySoundMem(title_se, DX_PLAYTYPE_BACK);
		StopSoundMem(title_bgm);
		return eInGame;
	}

	return eTitle;
}

void TitleDraw(void)//タイトル表示
{
	DrawBox(0, 0, 1280, 359, start_black, TRUE);
	DrawBox(0, 360, 1280, 720, start_white, TRUE);
	SetFontSize(50);
	DrawString(450, 100, "イライラ棒～る", start_white);
	SetFontSize(40);
	DrawString(45, 240, "十字キーとAキーで操作・そこそこすべる!", start_white);
	SetFontSize(50);
	DrawString(50, 295, "Aボタンで決定＆画面をチェンジ!", start_white);
	DrawString(500, 500, "スタート", start_black);
	DrawCircle(470, 525, 10.0, start_black, TRUE);
	DrawRankData();
}