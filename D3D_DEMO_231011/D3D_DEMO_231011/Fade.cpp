#include "Fade.h"
#include"Sprite.h"


Fade::Fade()
{
}

Fade::~Fade()
{
}

void Fade::Update()
{
	if (fadeState == FADE_IN)
	{
		fade->m_materialDiffuse.w -= 0.01f;

		if (fade->m_materialDiffuse.w <= 0.0f)
		{
			fadeState = NO_FADE;
			fade->SetActive(false);
		}
	}
	else if (fadeState == FADE_OUT)
	{
		fade->m_materialDiffuse.w += 0.01f;

		if (fade->m_materialDiffuse.w >= 1.0f)
		{
			SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
		}
	}
}
