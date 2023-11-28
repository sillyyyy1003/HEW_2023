#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

// ※Retro-Bit 製のサターンパッドは方向パッドが左スティックとして実装されているので、
// 　wButtons を読むだけでは入力を認識することができない。
// 　そこで、wButtons を読む前にスティックの入力を方向パッドに変換して対応を行う。
// スティックの入力を方向パッドフラグに変換
WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

class Input
{
public:
    // 使えるパッドのボタンの種類
    typedef enum
    {
        NONE,
        A, // ゲームパッドA
        B, // ゲームパッドB
        X, // ゲームパッドX
        Y, // ゲームパッドY
        R, // ゲームパッドR
        L, // ゲームパッドL
        LEFT, // ゲームパッド十字キー左
        RIGHT,// ゲームパッド十字キー右
        UP,   // ゲームパッド十字キー上
        DOWN, // ゲームパッド十字キー下
        START,// ゲームパッドSTATRT
        BACK, // ゲームパッドBACK
        LEFTTRIGGER, // 左トリガー
        RIGHTTRIGGER,// 右トリガー
        LEFTSTICK,   // 左スティック
        RIGHTSTICK,  // 右スティック
        UPSTICK,     // 上スティック
        DOWNSTICK,   // 下スティック
    }PADBUTTON;

    PADBUTTON PadButton = NONE;

private:

    // キー状態の記録領域
    bool keyState[256] = { false };

    // 1フレーム前のキー状態の記録領域
    bool oldKeyState[256] = { false };

    // パッドが押された時の処理を保存する関数
    bool SetPADButton(PADBUTTON PadButton);

    // パッドを振動させるための関数
    void Vibration(int pattern);

    // 振動のパターンを入れる変数
    int pattern = 0;

    // 振動時間を記憶する変数
    ULONGLONG Vibrationtime = 0;

public:

    // ボタンの長押しが発生しているかを返す関数
    bool GetPADRepeat(PADBUTTON PadButton);

    // ボタンのトリガーが発生しているかを返す関数
    bool GetPADTrigger(PADBUTTON PadButton);

    void Update();

    //振動パターンを設定する関数
    void SetPattern(int pt)
    {
        pattern = pt;
    }
};

// 唯一の実体変数のextern宣言
extern Input* gInput;


