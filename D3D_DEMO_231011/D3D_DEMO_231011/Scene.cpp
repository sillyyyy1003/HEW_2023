#include "Scene.h"
#include "Game.h"
#include "Fade.h"

Scene::Scene(void)
{
}

STAGEINFO Scene::GetNextStage()
{
	int num = m_stage;
	num++;
	return static_cast<STAGEINFO>(num);
}

void Scene::ChangeScene(SCENENAME _scene)
{
	//ŽŸ‚ÌƒV[ƒ“‚É‘JˆÚ
	SetNextScene(_scene);

	//fade Out‚ðs‚¤
	Game::Get()->GetFade()->FadeOut();

}
