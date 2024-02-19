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
	//���̃V�[���ɑJ��
	SetNextScene(_scene);

	//fade Out���s��
	Game::Get()->GetFade()->FadeOut();

}
