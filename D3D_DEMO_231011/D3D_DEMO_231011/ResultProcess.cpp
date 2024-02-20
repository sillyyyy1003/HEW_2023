#include "ResultProcess.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "Game.h"
#include "Fade.h"

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

void ResultProcess::Init(float posX, float posY, float size, float interval)
{
	m_size = size;

	m_interval = interval;

	//�X�e�b�v���̕\���̂���
	for (auto& stepnum : StepNum) {
		//������
		stepnum = new CanvasUI();
		//���f���쐬
		stepnum->CreateModel(g_Assets->Result_num, m_size * 74.83, m_size * 110.5, 10, 1);

		stepnum->m_pos.z = m_posz;
	}
	//�ʒu����
	SetPosition(posX,posY);
}

void ResultProcess::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void ResultProcess::UpdateCharCenter(char* outputChar)
{

	int totalCharacters = strlen(outputChar);
	float totalWidth = totalCharacters * (74 / SCREEN_PARA / 2);

	for (int i = 0; i < totalCharacters; i++)
	{
		// �����̉��Ԗڂ��擾 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		// �I�u�W�F�N�g�ɃZ�b�g����
		StepNum[i]->m_anime->SetFrameX(frameX);

		// �����̈ʒu��ݒ肷��i�����ɒ����j
		float posX = m_sPosX - totalWidth / 2 + i * (74 / SCREEN_PARA / 2) + m_interval;
		
		StepNum[i]->InitPos(posX, m_sPosY, 0.1);

		// UVOFFSET�X�V
		StepNum[i]->m_anime->Update();

		if (Game::Get()->GetFade()->m_fadePanel->m_materialDiffuse.w <= 0.01) {
			// �`��
			StepNum[i]->Draw();
		}
	}

}

void ResultProcess::UpdateCharLeft(char* outputChar)
{	
	for (int i = 0; i < strlen(outputChar); i++)
	{
		//�����̉��Ԗڂ��擾 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		//�I�u�W�F�N�g�ɃZ�b�g����
		StepNum[i]->m_anime->SetFrameX(frameX);

		//�����̈ʒu��ݒ肷��
		float posX = ((74 + m_interval) / SCREEN_PARA)* i;
		StepNum[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET�X�V
		StepNum[i]->m_anime->Update();

		if (Game::Get()->GetFade()->m_fadePanel->m_materialDiffuse.w <= 0.01) {
		//�`��
		StepNum[i]->Draw();
		}
	}

}

void ResultProcess::PrintDebugLogCenter(const int _num)
{
	//������ɓ]��
	char str[32];
	snprintf(str, 31, "%d", _num);
	//�X�V�ƕ`��
	UpdateCharCenter(str);
}

void ResultProcess::PrintDebugLogLeft(const int _num)
{
	//������ɓ]��
	char str[32];
	snprintf(str, 31, "%d", _num);
	//�X�V�ƕ`��
	UpdateCharLeft(str);
}
