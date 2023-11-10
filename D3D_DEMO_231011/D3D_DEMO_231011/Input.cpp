#include "Input.h"

// �Q�[���p�b�h�̐U��
XINPUT_VIBRATION vibration;
// �Q�[���p�b�h�̌��݂̏��
XINPUT_STATE state;
// �Q�[���p�b�h���̓C�x���g���擾
XINPUT_KEYSTROKE pkeystroke;

bool Input::SetPADButton(PADBUTTON PadButton)
{
    // �ݒ肳��Ă����Ԃ����s����
    if (pkeystroke.Flags)
    {
        // �Q�[���p�b�h�{�^��A�������ꂽ���̏���
        if (PadButton == A)
        {
            // �{�^��A��������Ă��邩
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
            {
                return true;
            }
        }

        // �Q�[���p�b�h�{�^��B�������ꂽ���̏���
        if (PadButton == B)
        {
            // �{�^��B��������Ă��邩
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            {
                return true;
            }
        }

        // �Q�[���p�b�h�{�^��X�������ꂽ���̏���
        if (PadButton == X)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
            {
                // �{�^��X��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�{�^��Y�������ꂽ���̏���
        if (PadButton == Y)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
            {
                // �{�^��Y��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�\���L�[���������ꂽ���̏���
        if (PadButton == LEFT)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
            {
                // �\���L�[����������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�\���L�[�E�������ꂽ���̏���
        if (PadButton == RIGHT)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
            {
                // �\���L�[�E��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�\���L�[�オ�����ꂽ���̏���
        if (PadButton == UP)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
            {
                // �\���L�[�オ������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�\���L�[���������ꂽ���̏���
        if (PadButton == DOWN)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
            {
                // �\���L�[����������Ă��邩
                return true;
            }
            else
            {
                return false;
            }
        }

        // �Q�[���p�b�hL�������ꂽ���̏���
        if (PadButton == L)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
            {
                // �Q�[���p�b�hL��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�hR�������ꂽ���̏���
        if (PadButton == R)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
            {
                // �Q�[���p�b�hR��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�hBACK�������ꂽ���̏���
        if (PadButton == BACK)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
            {
                // �Q�[���p�b�hBACK��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�hSTART�������ꂽ���̏���
        if (PadButton == START)
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
            {
                //�Q�[���p�b�hSTART��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h���g���K�[�������ꂽ���̏���
        if (PadButton == LEFTTRIGGER)
        {
            if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                // ���g���K�[��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�E�g���K�[�������ꂽ���̏���
        if (PadButton == RIGHTTRIGGER)
        {
            if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
            {
                // �E�g���K�[��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h���X�e�B�b�N�������ꂽ���̏���
        if (PadButton == LEFTSTICK)
        {
            if (state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                // ���X�e�B�b�N��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h�E�X�e�B�b�N�������ꂽ���̏���
        if (PadButton == RIGHTSTICK)
        {
            if (state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                // �E�X�e�B�b�N��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h��X�e�B�b�N�������ꂽ���̏���
        if (PadButton == DOWNSTICK)
        {
            if (state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
            {
                // ��X�e�B�b�N��������Ă��邩
                return true;
            }
        }

        // �Q�[���p�b�h���X�e�B�b�N�������ꂽ���̏���
        if (PadButton == UPSTICK)
        {
            if (state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
            {
                // ���X�e�B�b�N��������Ă��邩
                return true;
            }
        }
    }

    return false;
}

void Input::Vibration(int pattern)
{
    // �p�^�[���ɂ���ď�����ς���
    switch (pattern)
    {

    case 0:// �p�^�[��0 �����U�����Ȃ�
        vibration.wLeftMotorSpeed = 0;
        vibration.wRightMotorSpeed = 0;
        XInputSetState(0, &vibration);
        // �U�����J�n�����������L�^����
        Vibrationtime = GetTickCount64();
        break;

    case 1:// �p�^�[���P �������ő�U��
        vibration.wLeftMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 2:// �p�^�[��2�@�E�����ő�U��
        vibration.wRightMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 3:// �p�^�[��3 �����ƉE�����ő�U��
        vibration.wRightMotorSpeed = 65535;
        vibration.wLeftMotorSpeed = 65535;
        XInputSetState(0, &vibration);
        break;

    case 4:// �p�^�[���S �����ƉE�����ő傩�甼���̐U��
        vibration.wRightMotorSpeed = 65535 / 2;
        vibration.wLeftMotorSpeed = 65535 / 2;
        XInputSetState(0, &vibration);
        break;
    }
}

bool Input::GetPADRepeat(PADBUTTON PadButton)
{
    // �L�[��������Ă���Ԃ����Ə��������s����悤�ɐݒ�
    pkeystroke.Flags = XINPUT_KEYSTROKE_REPEAT;

    // �C�ӂ̃{�^���������ꂽ���̏�����Ԃ�
    return Input::SetPADButton(PadButton);
}

bool Input::GetPADTrigger(PADBUTTON PadButton)
{
    // �L�[�������ꂽ�u�Ԃɏ��������s����悤�ɐݒ�
    pkeystroke.Flags = XINPUT_KEYSTROKE_KEYDOWN;

    // ������Ă��Ȃ����Afalse�ł��C�ӂ̃{�^���������ꂽ���Atrue
    if (Input::SetPADButton(PadButton))
    {
        keyState[PadButton] = true;
    }
    else
    {
        keyState[PadButton] = false;
    }

    // 1�t���[���O�̉�����Ԃ�false�ł����݃t���[���̉�����Ԃ�true
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
    // XInputGetState�֐��Ăяo���O�ɍ\���̂̃N���A
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    // �w�肳�ꂽ�R���g���[���[�̌��݂̏�Ԃ��擾���܂��B
    XInputGetState(0, &state);

    // XInputGetKeystroke�֐��Ăяo���O�ɍ\���̂̃N���A
    ZeroMemory(&pkeystroke, sizeof(PXINPUT_KEYSTROKE));

    // �Q�[���p�b�h�̓��̓C�x���g���擾���܂��B
    XInputGetKeystroke(0, 0, &pkeystroke);

    // �p�b�h�̐U����������
    Input::Vibration(pattern);

    // �p�b�h�̐U�����~�߂邽�߂̏���
    if (pattern > 0)
    {
        // �U�����J�n����0.5�b��Ŏ~�߂�
        if (GetTickCount64() > Vibrationtime + 1 * 500)
        {
            pattern = 0;
        }
    }

    // �@���f�b�h�]�[���́A�A�i���O�X�e�B�b�N�ɐG���Ă��Ȃ��Ƃ���A
    // �@�@�X�e�b�N�������ɂ���ꍇ�ł��A�R���g���[���[���񍐂���u����v�l
    //�@�f�b�h�]�[�����̓��͂� 0 �Ɋۂ߂�v���O�����B
    if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
        state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
            state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        state.Gamepad.sThumbLX = 0;
        state.Gamepad.sThumbLY = 0;
    }

    // oldKeyState��keyState���R�s�[����
    memcpy_s(oldKeyState, sizeof(oldKeyState), keyState, sizeof(keyState));

    // ���X�e�B�b�N����̓��͂�����p�b�h�ɕϊ�
    state.Gamepad.wButtons |= ThumbToDPad(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
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
