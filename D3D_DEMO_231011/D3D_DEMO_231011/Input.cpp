#include "Input.h"
/*

キー入力用関数作成途中

WinMain.cppの26行目 newInputをする


*/




void Input::SetKeyDownState(int key)
{
}

void Input::SetKeyUpState(int key)
{
}

bool Input::GetKeyPress(int key)
{
	return m_KeyState[key];
}

bool Input::GetKeyTrigger(int key)
{
	return false;
}

void Input::Upadate()
{
}
