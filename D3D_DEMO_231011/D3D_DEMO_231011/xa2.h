//=============================================================================
//
// �T�E���h���� [xa2.h]
//
//=============================================================================
#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_

#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	BGM_Stage1 = 0,		// BGM
	BGM_Stage2,			// BGM
	BGM_Stage3,			// BGM
	BGM_SelectStage,	// BGM
	

	SE_Select,			// SE
	SE_SelectDecide,	// SE
	SE_TITLE,			// SE
	SE_Present,			// SE
	SE_Combine,			// SE
	SE_Result,
	//SE_Press,
	//SOUND_LABEL_SE007,			// �T���v��SE


	SOUND_LABEL_LAST,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

// �Q�[�����[�v�J�n�O�ɌĂяo���T�E���h�̏���������
HRESULT XA_Initialize(void);

// �Q�[�����[�v�I����ɌĂяo���T�E���h�̉������
void XA_Release(void);

// �����Ŏw�肵���T�E���h���Đ�����
void XA_Play(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h���~����
void XA_Stop(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h�̍Đ����ĊJ����
void XA_Resume(SOUND_LABEL label);

// �����Ŏw�肵���T�E���h�̉��ʂ𐔒l�Őݒ肷��
void XA_SetVolume(SOUND_LABEL label, float volume);

#endif
