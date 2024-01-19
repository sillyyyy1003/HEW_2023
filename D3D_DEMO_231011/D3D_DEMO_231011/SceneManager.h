#pragma once
#include "Scene.h"
#include "Stage.h"
#include <vector>

class SceneManager : public Scene
{
private:
	
	SceneManager() {}// �R���X�g���N�^
	
	~SceneManager() {}// �f�X�g���N�^



	//�R�s�[�Ƃ����֎~�ɂ���
	SceneManager(const SceneManager&) = delete;// �I�u�W�F�N�g�̃R�s�[
	SceneManager& operator=(const SceneManager&) = delete;// �I�u�W�F�N�g�̑��
	SceneManager(SceneManager&&) = delete;// �I�u�W�F�N�g�̃��[�u
	SceneManager& operator=(SceneManager&&) = delete;// �I�u�W�F�N�g�̃��[�u���

	//�X�e�[�W�̏�񈵂�
	Stage** m_stageHolder;
		
public:
	
	//�V���O���g��
	static SceneManager* Get();

	/*Init*/
	void Init();
	void InitStage();
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);
	void InitStage2_1(void);
	void InitStage2_2(void);
	void InitStage2_3(void);
	void InitStage3_1(void);
	void InitStage3_2(void);
	void InitStage3_3(void);

	/*Update*/
	void Update();
	void TitleUpdate();
	void StageSelect();

	//STAGEUPDATE
	void UpdateStage1_1(void);
	void UpdateStage1_2(void);
	void UpdateStage1_3(void);
	void UpdateStage2_1(void);
	void UpdateStage2_2(void);
	void UpdateStage2_3(void);
	void UpdateStage3_1(void);
	void UpdateStage3_2(void);
	void UpdateStage3_3(void);
	//RESUTL UPDATE




	
	/*Draw*/
	void Draw();
	//�X�e�[�W�`��
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();

	//���U���g�`��


	



};

