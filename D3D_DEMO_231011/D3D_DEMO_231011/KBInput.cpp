#include "KBInput.h"
#include <memory.h>

void KBInput::SetKeyDownState(int key)
{
    keyState[key] = true;
}

void KBInput::SetKeyUpState(int key)
{
    keyState[key] = false;
}

bool KBInput::GetKeyPress(int key)
{
    return keyState[key];
}

bool KBInput::GetKeyTrigger(int key)
{
	// 1フレーム前の押下状態がfalseでかつ現在フレームの押下状態がtrue
	if (oldKeyState[key] == false && keyState[key] == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void KBInput::Update()
{
	memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));
}
