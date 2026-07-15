#include <DxLib.h>
#include"Circle.h"
#include<math.h>
#include"../Utility/input.h"

Circle circle;

double rx;
double ry;
float xspeed;
float yspeed;
int save;
int miss_SE;
int check_point_SE;

void CircleInit(void)
{
	circle.x = 40.0;//ゲーム開始初期x座標
	circle.y = 40.0;//ゲーム開始初期y座標
	rx = 40.0;//復活時初期x座標
	ry = 40.0;//復活時初期y座標
	xspeed = 0.0f;//x座標速度
	yspeed = 0.0f;//y座標速度
	save = 0;//チェックポイント通過判定
	miss_SE = LoadSoundMem("assets/sounds/miss.mp3");//敵と衝突・壁に激突時のse読み込み
	check_point_SE = LoadSoundMem("assets/sounds/check_point.mp3");//チェックポイント通過時のse読み込み

}

void CircleUpdate(float delta_second)//自機の操作処理
{
	if (GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eHeld && xspeed > (-160.0f * delta_second))
	{
		xspeed += -22.0f * delta_second;
	}

	if (GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eHeld && xspeed < (160.0f * delta_second))
	{
		xspeed += 22.0f * delta_second;
	}

	if (xspeed > (2.75f * delta_second))
	{
		xspeed += (-2.75f * delta_second);
	}
	else if (xspeed < (-2.75f * delta_second))
	{
		xspeed += (2.75f * delta_second);
	}
	else
	{
		xspeed = 0.0f;
	}

	circle.x += xspeed;

	if (GetButtonState(XINPUT_BUTTON_DPAD_UP) == eHeld && yspeed > (-160.0f * delta_second))
	{
		yspeed += -22.0f * delta_second;
	}

	if (GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == eHeld && yspeed < (160.0f * delta_second))
	{
		yspeed += 22.0f * delta_second;
	}

	if (yspeed > (2.75f * delta_second))
	{
		yspeed += (-2.75f * delta_second);
	}
	else if (yspeed < (-2.75f * delta_second))
	{
		yspeed += (2.75f * delta_second);
	}
	else
	{
		yspeed = 0.0f;
	}

	circle.y += yspeed;


	if (circle.x < 0.0 || circle.x > 1280.0)//画面からはみ出した際にリスポーン地点に戻す
	{
		Retry();
	}
	if (circle.y < 0.0 || circle.y > 720.0)//画面からはみ出した際にリスポーン地点に戻す
	{
		Retry();
	}

	if (save == 0)//チェックポイント当たり判定
	{
		double x = circle.x - 1160.0;
		double y = circle.y - 580.0;

		if (x >= -20.0 && x <= 20.0)
		{
			if (y >= -20.0 && y <= 20.0)//リスポーン地点をチェックポイントに設定し、リスポーン地点の描画をoffにする
			{
				PlaySoundMem(check_point_SE, DX_PLAYTYPE_BACK);
				rx = 1160.0;
				ry = 580.0;
				save = 1;
			}
		}
	}


}

void CircleDraw(void)
{
	DrawCircle(circle.x, circle.y, 10, GetColor(100, 255, 100), TRUE);//自機表示

	if (save == 0)
	{
		DrawCircle(1160.0, 580.0, 13, GetColor(0, 180, 255), TRUE);//チェックポイント表示
	}

	SetFontSize(30);
}

Circle ReturnCircle(void)
{
	return circle;
}

void Retry(void)//自機をリスポーン地点に移動させ、慣性を0に戻し、キーの入力を可能にする
{
	PlaySoundMem(miss_SE, DX_PLAYTYPE_BACK);
	circle.x = rx;
	circle.y = ry;
	xspeed = 0.0f;
	yspeed = 0.0f;
}