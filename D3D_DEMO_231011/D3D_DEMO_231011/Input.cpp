#include "Input.h"

// ゲームパッドの振動
XINPUT_VIBRATION vibration;
// ゲームパッドの現在の状態
XINPUT_STATE state;
// ゲームパッド入力イベントを取得
XINPUT_KEYSTROKE pkeystroke;

bool Input::SetPADButton(PADBUTTON PadButton)
{
    // 設定されている状態を実行する
    if (pkeystroke.Flags)
    {
        // ゲームパッドボタンAが押された時の処理
        if (PadButton == A)
        {
            // ボタンAが押されているか
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
                return true;
            }
        }

        // ゲームパッドボタンBが押された時の処理
        if (PadButton == B)
        {
            // ボタンBが押されているか
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                return true;
            }
        }

        // ゲームパッドボタンXが押された時の処理
        if (PadButton == X)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
            {
                // ボタンXが押されているか
                return true;
            }
        }

        // ゲームパッドボタンYが押された時の処理
        if (PadButton == Y)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
            {
                // ボタンYが押されているか
                return true;
            }
        }

        // ゲームパッド十字キー左が押された時の処理
        if (PadButton == LEFT)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
            {
                // 十字キー左が押されているか
                return true;
            }
        }

        // ゲームパッド十字キー右が押された時の処理
        if (PadButton == RIGHT)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
            {
                // 十字キー右が押されているか
                return true;
            }
        }

        // ゲームパッド十字キー上が押された時の処理
        if (PadButton == UP)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
            {
                // 十字キー上が押されているか
                return true;
            }
        }

        // ゲームパッド十字キー下が押された時の処理
        if (PadButton == DOWN)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
            {
                // 十字キー下が押されているか
                return true;
            }
            else
            {
                return false;
            }
        }

        // ゲームパッドLが押された時の処理
        if (PadButton == L)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
            {
                // ゲームパッドLが押されているか
                return true;
            }
        }

        // ゲームパッドRが押された時の処理
        if (PadButton == R)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            {
                // ゲームパッドRが押されているか
                return true;
            }
        }

        // ゲームパッドBACKが押された時の処理
        if (PadButton == BACK)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
            {
                // ゲームパッドBACKが押されているか
                return true;
            }
        }

        // ゲームパッドSTARTが押された時の処理
        if (PadButton == START)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
            {
                //ゲームパッドSTARTが押されているか
                return true;
            }
        }

        // ゲームパッド左トリガーが押された時の処理
        if (PadButton == LEFTTRIGGER)
        {
            if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                // 左トリガーが押されているか
                return true;
            }
        }

        // ゲームパッド右トリガーが押された時の処理
        if (PadButton == RIGHTTRIGGER)
        {
            if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                // 右トリガーが押されているか
                return true;
            }
        }

        // ゲームパッド左スティックが押された時の処理
        if (PadButton == LEFTSTICK)
        {
            if (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                // 左スティックが押されているか
                return true;
            }
        }

        // ゲームパッド右スティックが押された時の処理
        if (PadButton == RIGHTSTICK)
        {
            if (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                // 右スティックが押されているか
                return true;
            }
        }

        // ゲームパッド上スティックが押された時の処理
        if (PadButton == DOWNSTICK)
        {
            if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                // 上スティックが押されているか
                return true;
            }
        }

        // ゲームパッド下スティックが押された時の処理
        if (PadButton == UPSTICK)
        {
            if (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                // 下スティックが押されているか
                return true;
            }
        }
    }

    return false;
}

void Input::Vibration(int pattern)
{
    // パターンによって処理を変える
    switch (pattern)
    {

    case 0:// パターン0 何も振動しない
        vibration.wLeftMotorSpeed = 0;
        vibration.wRightMotorSpeed = 0;
        XInputSetState(0, &vibration);
        // 振動が開始した時刻を記録する
        Vibrationtime = GetTickCount64();
        break;

    case 1:// パターン１ 左側が最大振動
        vibration.wLeftMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 2:// パターン2　右側が最大振動
        vibration.wRightMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 3:// パターン3 左側と右側が最大振動
        vibration.wRightMotorSpeed = 65535;
        vibration.wLeftMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 4:// パターン４ 左側と右側が最大から半分の振動
        vibration.wRightMotorSpeed = 65535 / 2;
        vibration.wLeftMotorSpeed = 65535 / 2;
        XInputSetState(0, &vibration);
        break;
    }
}

bool Input::GetPADRepeat(PADBUTTON PadButton)
{
    // キーが押されている間ずっと処理を実行するように設定
    pkeystroke.Flags = XINPUT_KEYSTROKE_REPEAT;

    // 任意のボタンが押された時の処理を返す
    return Input::SetPADButton(PadButton);
}

bool Input::GetPADTrigger(PADBUTTON PadButton)
{
    // キーが押された瞬間に処理が実行するように設定
    pkeystroke.Flags = XINPUT_KEYSTROKE_KEYDOWN;

    // 押されていない時、falseでかつ任意のボタンが押された時、true
    if (Input::SetPADButton(PadButton))
    {
        keyState[PadButton] = true;
    }
    else
    {
        keyState[PadButton] = false;
    }

    // 1フレーム前の押下状態がfalseでかつ現在フレームの押下状態がtrue
    if (oldKeyState[PadButton] == false && keyState[PadButton] == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Input::Update()
{
    // XInputGetState関数呼び出し前に構造体のクリア
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // 指定されたコントローラーの現在の状態を取得します。
    XInputGetState(0, &state);

    // XInputGetKeystroke関数呼び出し前に構造体のクリア
    ZeroMemory(&pkeystroke, sizeof(PXINPUT_KEYSTROKE));

    // ゲームパッドの入力イベントを取得します。
    XInputGetKeystroke(0, 0, &pkeystroke);

    // パッドの振動をさせる
    Input::Vibration(pattern);

    // パッドの振動を止めるための処理
    if (pattern > 0)
    {
        // 振動が開始して0.5秒後で止める
        if (GetTickCount64() > Vibrationtime + 1 * 500)
        {
            pattern = 0;
        }
    }

    // 　※デッドゾーンは、アナログスティックに触っていないときや、
    // 　　ステックが中央にある場合でも、コントローラーが報告する「動作」値
    //　デッドゾーン内の入力を 0 に丸めるプログラム。
    if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
        state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
            state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        state.Gamepad.sThumbLX = 0;
        state.Gamepad.sThumbLY = 0;
    }

    // oldKeyStateにkeyStateをコピーする
    memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));

    // 左スティックからの入力を方向パッドに変換
    state.Gamepad.wButtons |= ThumbToDPad(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

// スティックの入力を方向パッドフラグに変換
WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
    WORD wButtons = 0;

    if (sThumbY >= sDeadZone)
    {
        wButtons |= XINPUT_GAMEPAD_DPAD_UP;
    }
    else if (sThumbY <= -sDeadZone)
    {
        wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
    }

    if (sThumbX <= -sDeadZone)
    {
        wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
    }
    else if (sThumbX >= sDeadZone)
    {
        wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
    }

    return wButtons;
}
