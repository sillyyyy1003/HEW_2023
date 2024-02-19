#pragma once
#include "SceneManager.h"

class CanvasUI;

class Fade
{
private:
	//fade�̑��x
	float m_fadeSpeed = 0.01f;

public:

	CanvasUI* m_fadePanel; // ��ʂɂ��Ԃ���X�v���C�g
	Fade();
	~Fade();

	void Update();
	void Draw();

	// �J�n�֐�
	void FadeIn();
	void FadeOut();

	void SetFadeSpeed(float speed) { m_fadeSpeed = speed; };

	// ���݂̃t�F�[�h�̏��
	enum {
		NONE,		// �����t�F�[�h���Ă��Ȃ����
		FADE_IN,	// �t�F�[�h�C����
		FADE_OUT,	// �t�F�[�h�A�E�g��
	};

	int mState;

};