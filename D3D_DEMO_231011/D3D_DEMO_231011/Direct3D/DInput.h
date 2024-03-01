#pragma once
//Direct Inputを使ったキーとマウス操作取得クラス
#define DIRECTINPUT_VERSION 0x0800
#include	<dinput.h>


class Input
{

private:
	IDirectInput8* mDInput = nullptr;
	IDirectInputDevice8* mDevKeyboad = nullptr;
	IDirectInputDevice8* mDevMouse = nullptr;

	unsigned char mKeyBuffer[256] = {};
	unsigned char mOldKeyBuffer[256] = {};

	DIMOUSESTATE2 mMouseState = {};
	DIMOUSESTATE2 mOldMouseState = {};

	Input() {};

	~Input();
	

public:
	/// <summary>
	/// Singleton Instanceを取得する関数
	/// </summary>
	/// <returns></returns>
	static Input* Get();
	
	/// <summary>
	///	Direct Inputの初期化を行う関数
	/// ゲームループが始める前に呼び出す
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="hInstance"></param>
	void Initialize(HWND hWnd, HINSTANCE hInstance);
		
	/// <summary>
	/// ゲームループで毎回呼び出す関数
	/// </summary>
	void Update();

	//key：DIK_Dで始まる定数
	bool GetKeyPress(int key);

	bool GetKeyTrigger(int key);

	/// <summary>
	/// マウスのボタンが押されているか判定
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool GetMousePress(int key);

	//マウスの移動量を取得
	POINT GetMouseMove(void);

};

