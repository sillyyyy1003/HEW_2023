#pragma once
#include "SceneManager.h"

class CanvasUI;

class Fade
{
private:
	//fadeの速度
	float m_fadeSpeed = 0.01f;

public:

	CanvasUI* m_fadePanel; // 画面にかぶせるスプライト
	Fade();
	~Fade();

	void Update();
	void Draw();

	// 開始関数
	void FadeIn();
	void FadeOut();

	void SetFadeSpeed(float speed) { m_fadeSpeed = speed; };

	// 現在のフェードの状態
	enum {
		NONE,		// 何もフェードしていない状態
		FADE_IN,	// フェードイン中
		FADE_OUT,	// フェードアウト中
	};

	int mState;

};