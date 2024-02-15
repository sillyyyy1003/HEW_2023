#include "Scene.h"

Scene::Scene(void)
{
}

STAGEINFO Scene::GetNextStage()
{
	int num = m_stage;
	num++;
	return static_cast<STAGEINFO>(num);
}
