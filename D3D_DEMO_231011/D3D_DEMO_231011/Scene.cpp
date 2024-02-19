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
	//次のシーンに遷移
	SetNextScene(_scene);

	//fade Outを行う
	Game::Get()->GetFade()->FadeOut();

}
