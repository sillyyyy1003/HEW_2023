#include "Scene.h"
#include "Game.h"
#include "Fade.h"
#include "xa2.h"

Scene::Scene(void)
{
}

STAGEINFO Scene::GetNextStage()
{
	int num = m_stage;
	num++;
	
	//����ĂȂ��X�e�[�W�ɓ����
	if (num > 2) {
		return STAGE_UNDONE;
	}

	if (num > STAGE_NUM) 
	{
		return STAGE_IDLE;
	}else
	{
		return static_cast<STAGEINFO>(num);
	}

}

void Scene::ChangeScene(SCENENAME _scene)
{
	//���̃V�[���ɑJ��
	SetNextScene(_scene);

	//fade Out���s��
	Game::Get()->GetFade()->FadeOut();


	XA_Stop(BGM_Stage1);
	XA_Stop(BGM_Stage2);
	XA_Stop(BGM_Stage3);
	XA_Stop(BGM_SelectStage);
	XA_Stop(SE_SelectDecide);
	XA_Stop(SE_Plant);
	XA_Stop(SE_Result);


}
