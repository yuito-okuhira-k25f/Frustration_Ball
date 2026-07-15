//キーボードとゲームパッドの入力処理実装
#include"Input.h"
#include<DxLib.h>
#include<math.h>

//キー・ボタンの最大数
#define D_KEYCODE_MAX (256)
#define D_BUTTON_MAX (16)

//現在・前フレームの入力状態
char now_key[D_KEYCODE_MAX];//現在フレームのキー状態
char old_key[D_KEYCODE_MAX];//１フレーム前のキー状態
unsigned char now_button[16];//現在フレームのボタン状態
unsigned char old_button[16];//１フレーム前のボタン状態

void InputInit(void)
{
	//配列クリアとアナログ初期化
	memset(now_key, 0, (sizeof(char) * D_KEYCODE_MAX));
	memset(old_key, 0, (sizeof(char) * D_KEYCODE_MAX));

	memset(now_button, 0, (sizeof(unsigned char) * D_BUTTON_MAX));
	memset(now_button, 0, (sizeof(unsigned char) * D_BUTTON_MAX));
}

void InputUpdate(void)
{
	//キー状態更新（過去→現在）
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	//XInputのゲームパッド状態取得
	XINPUT_STATE controller = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &controller);
	memcpy(old_button, now_button, (sizeof(unsigned char) * D_BUTTON_MAX));
	memcpy(now_button, controller.Buttons, (sizeof(unsigned char) *
		D_BUTTON_MAX));
}

eInputState GetKeyInputState(int key)
{
	//指定キーの状態遷移を返す
	if (0 <= key && key < D_KEYCODE_MAX)
	{
		if (old_key[key] == TRUE)
		{
			if (now_key[key] == TRUE)
			{
				return eHeld;//押しっぱなし
			}
			else
			{
				return eReleased;//離された瞬間
			}
		}
		else
		{
			if (now_key[key] == TRUE)
			{
				return ePressed;
			}
		}
	}
	return eNone;//非入力
}

eInputState GetButtonState(int button)
{
	//指定ボタン状態遷移を返す
	if (0 <= button && button < D_BUTTON_MAX)
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				return eHeld;//押しっぱなし
			}
			else
			{
				return eReleased;//離された瞬間
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				return ePressed;//押された瞬間
			}
		}
	}
	return eNone;//非入力
}