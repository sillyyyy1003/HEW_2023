#pragma once

//キー入力を管理するクラス
//仕組み：WndProc関数でキーが押された/離されたイベント時にそれを記録していく。
//キーの状態を判定する関数が呼ばれたら、その記録状態を返す。

class KBInput
{
private:
	// キー状態の記録領域
	bool keyState[256] = { false };

	// 1フレーム前のキー状態の記録領域
	bool oldKeyState[256] = { false };

public:


	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	// キーが押されたのを記録する関数
	void SetKeyDownState(int key);

	// キーが離されたのを記録する関数
	void SetKeyUpState(int key);

	// キープレスが発生しているか返す関数
	bool GetKeyPress(int key);

	// キートリガーが発生しているか返す関数
	bool GetKeyTrigger(int key);

	// ゲームループの最後でキー状態をoldKeyStateに保存する関数
	void Update();


};

