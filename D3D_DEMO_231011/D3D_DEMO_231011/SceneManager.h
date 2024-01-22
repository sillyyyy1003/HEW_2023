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


	/*Update*/
	void Update();

};

