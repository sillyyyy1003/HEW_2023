#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

class Input
{

};

DWORD XInputGetState(
    DWORD dwUserIndex,    // �R���g���[���[�̃C���f�b�N�X
    XINPUT_STATE* pState  // ��Ԃ��󂯎�� XINPUT_STATE �\���̂ւ̃|�C���^�[
);
//DIJOYSTATE pad_data;

