#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

class Input
{
private:
	//キー状態の記憶領域
	bool m_KeyState[256] = { false }; 
	// 1フレーム前のキー状態の記録領域
	bool m_OldKeyState[256] = { false };

public:
	//メンバー関数
	
	//キーが押されたのを記録する関数
	void SetKeyDownState(int key);

	//キーが離されたのを記録する関数
	void SetKeyUpState(int key);

	// キープレスが発生しているか返す関数
	bool GetKeyPress(int key);

	//キートリガーが発生するか返す関数
	bool GetKeyTrigger(int key);

	//ゲームループの最後でキー状態をm_oldKeyStateに保存する関数
	void Upadate();
};

//DWORD XInputGetState(
//    DWORD dwUserIndex,    // コントローラーのインデックス
//    XINPUT_STATE* pState  // 状態を受け取る XINPUT_STATE 構造体へのポインター
//);
////DIJOYSTATE pad_data;

