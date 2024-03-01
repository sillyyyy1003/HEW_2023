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
	
	float& alpha = m_fadePanel->m_materialDiffuse.w;	// 参照型を使って別名をつける

	// mStateの値によって、フェード処理を行う
	switch (mState)
	{
	case FADE_IN:
		// パネルのRGBAのAの値を、減らす
		alpha -= m_fadeSpeed; //* Game::Get()->fadeTime;
		// alphaが0.0f以下になったら、フェードイン終了
		if (alpha <= 0.0f)
		{
			mState = NONE; // 何もしない状態

			isStartFade = false;

		}
		break;

	case FADE_OUT:
		// パネルのRGBAのAの値を、増やす
		alpha += m_fadeSpeed;// * Game::Get()->fadeTime;
		// alphaが1.0f以上になったら、フェードアウト終了
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
