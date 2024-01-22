#pragma once
#include "Stage.h"

class StageManager : public Stage
{
private:
	
	StageManager() {}// �R���X�g���N�^
	
	~StageManager() {}// �f�X�g���N�^



	//�R�s�[�Ƃ����֎~�ɂ���
	StageManager(const StageManager&) = delete;// �I�u�W�F�N�g�̃R�s�[
	StageManager& operator=(const StageManager&) = delete;// �I�u�W�F�N�g�̑��
	StageManager(StageManager&&) = delete;// �I�u�W�F�N�g�̃��[�u
	StageManager& operator=(StageManager&&) = delete;// �I�u�W�F�N�g�̃��[�u���

		
public:

	//�V���O���g��
	static StageManager& Get();


	/*Init*/
	void Init();
	/*Update*/
	void Update();
	/*Draw*/
	void Draw();

	



};

