#include "Input.h"
/*

�L�[���͗p�֐��쐬�r��

WinMain.cpp��26�s�� newInput������


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
