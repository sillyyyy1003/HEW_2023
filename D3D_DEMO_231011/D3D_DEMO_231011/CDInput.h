#pragma once

//DirectInputを使ったキーとマウス操作取得クラス
#define DIRECTINPUT_VERSION 0x0800
#include	<dinput.h>

enum KeyCode
{
	DIK_LBUTTON = 0x00,//左マウスボタン
	DIK_RBUTTON = 0x01,//右マウスボタン
	DIK_MBUTTON = 0x02,//中マウスボタン
	DIK_SIDEBUTTON1 = 0x03,//サイドマウスボタン1
	DIK_SIDEBUTTON2 = 0x04,//サイドマウスボタン2
};


class CdInput
{

private:
	IDirectInput8* mDInput = nullptr;
	IDirectInputDevice8* mDevKeyboad = nullptr;
	IDirectInputDevice8* mDevMouse = nullptr;

	unsigned char mKeyBuffer[256] = {};
	unsigned char mOldKeyBuffer[256] = {};

	DIMOUSESTATE2 mMouseState = {};
	DIMOUSESTATE2 mOldMouseState = {};

	CdInput() {};

	
	

public:
	~CdInput();//デストラクタ

	// シングルトンのインスタンスを取得する関数
	static CdInput* Get();

	// DirectInputの初期化を行う関数
	// ゲームループが始まる前に呼び出す
	void Initialize(HWND hWnd, HINSTANCE hInstance);

	// ゲームループで毎回呼び出す関数
	void Update();

	//キーが押された状態
	void SetKeyDownState(int key);

	//キーが離された状態
	void SetKeyUpState(int key);

	//マウスボタンが押された状態
	void SetMouseDownState(int key);

	//マウスボタンが離された状態
	void SetMouseUpState(int key);

	// キーはDIKで始まる定数
	//キープレス
	bool GetKeyPress(int key);

	//キートリガー
	bool GetKeyTrigger(int key);

	//マウスボタンプレス
	bool GetMousePress(int key);

	//マウスボタントリガー
	bool GetMouseTrigger(int key);
};

