#include "Fade.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "Game.h"

extern Assets* g_Assets;

Fade::Fade()
{
	m_fadePanel = new CanvasUI();	

	m_fadePanel->CreateModel(g_Assets->fade, 1280, 720, 1, 1);

	m_fadePanel->m_pos.z = 0.1f;

	mState = NONE;
}

Fade::~Fade()
{
	delete 	m_fadePanel;
}

void Fade::Update()
{
	
	float& alpha = m_fadePanel->m_materialDiffuse.w;	// �Q�ƌ^���g���ĕʖ�������

	// mState�̒l�ɂ���āA�t�F�[�h�������s��
	switch (mState)
	{
	case FADE_IN:
		// �p�l����RGBA��A�̒l���A���炷
		alpha -= m_fadeSpeed; //* Game::Get()->fadeTime;
		// alpha��0.0f�ȉ��ɂȂ�����A�t�F�[�h�C���I��
		if (alpha <= 0.0f)
		{
			mState = NONE; // �������Ȃ����

			isStartFade = false;

		}
		break;

	case FADE_OUT:
		// �p�l����RGBA��A�̒l���A���₷
		alpha += m_fadeSpeed;// * Game::Get()->fadeTime;
		// alpha��1.0f�ȏ�ɂȂ�����A�t�F�[�h�A�E�g�I��
		if (alpha >= 1.0f)
		{
			mState = NONE;
		}
		break;
	}
}

void Fade::Draw()
{
	m_fadePanel->Draw();
}

void Fade::FadeIn()
{
	if (mState == NONE)
		mState = FADE_IN;
	isStartFade = true;

}

void Fade::FadeOut()
{
	if (mState == NONE)
		mState = FADE_OUT;
}
