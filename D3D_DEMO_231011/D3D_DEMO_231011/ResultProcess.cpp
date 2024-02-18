#include "ResultProcess.h"
#include "CanvasUI.h"
#include "Assets.h"

extern Assets* g_Assets;

ResultProcess::ResultProcess()
{

}

ResultProcess::~ResultProcess()
{
	for (auto& stepnum : StepNum) {
		delete stepnum;
	}
}

void ResultProcess::Init(float posX, float posY)
{
	//�X�e�b�v���̕\���̂���
	for (auto& stepnum : StepNum) {
		//������
		stepnum = new CanvasUI();
		//���f���쐬
		stepnum->CreateModel(g_Assets->Result_num, m_size * 5238 / 70, m_size * 1105 / 10, 10, 1);
	}
	//�ʒu����
	SetPosition(posX,posY);
}

void ResultProcess::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void ResultProcess::UpdateChar(char* outputChar)
{
	//for (int i = 0; i < strlen(outputChar); i++)
	//{
	//	//�����̉��Ԗڂ��擾 SPACE ASCII->32
	//	int frameX = ((int)outputChar[i] - 32) % 16;
	//	//�I�u�W�F�N�g�ɃZ�b�g����
	//	StepNum[i]->m_anime->SetFrameX(frameX);

	//	//�����̈ʒu��ݒ肷��
	//	float posX = (74 / SCREEN_PARA / 2) * i;
	//	StepNum[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

	//	//UVOFFSET�X�V
	//	StepNum[i]->m_anime->Update();

	//	//�`��
	//	StepNum[i]->Draw();

	//}
	
	int totalCharacters = strlen(outputChar);
	float totalWidth = totalCharacters * (74 / SCREEN_PARA / 2);

	for (int i = 0; i < totalCharacters; i++)
	{
		// �����̉��Ԗڂ��擾 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		// �I�u�W�F�N�g�ɃZ�b�g����
		StepNum[i]->m_anime->SetFrameX(frameX);

		// �����̈ʒu��ݒ肷��i�����ɒ����j
		float posX = m_sPosX - totalWidth / 2 + i * (74 / SCREEN_PARA / 2);
		
		StepNum[i]->InitPos(posX, m_sPosY, 0.1);

		// UVOFFSET�X�V
		StepNum[i]->m_anime->Update();

		// �`��
		StepNum[i]->Draw();
	}

}

void ResultProcess::PrintDebugLog(const int _num)
{
	//������ɓ]��
	char str[32];
	snprintf(str, 31, "%d", _num);
	//�X�V�ƕ`��
	UpdateChar(str);
}
