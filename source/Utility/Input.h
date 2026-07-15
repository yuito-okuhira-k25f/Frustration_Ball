#pragma once

//入力状態の列挙（キー・ボタン）
enum eInputState
{
	eNone,//非入力
	ePressed,//今フレームで押された
	eReleased,//今フレームで離された
	eHeld,//押しっぱなし
};

//初期化・更新・状態取得
void InputInit(void);//入力バッファ初期化
void InputUpdate(void);//入力バッファ更新
eInputState GetKeyInputState(int key);//キーの状態取得
eInputState GetButtonState(int button);//ボタンの状態取得

