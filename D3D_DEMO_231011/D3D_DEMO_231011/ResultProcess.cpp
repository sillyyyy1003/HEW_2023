#include "ResultProcess.h"
#include "CanvasUI.h"
#include "Assets.h"

extern Assets* g_Assets;
extern ResultProcess* g_resultprocess = new ResultProcess;

ResultProcess::ResultProcess()
{

}

ResultProcess::~ResultProcess()
{
	for (auto& stepnum : StepNum) {
		delete stepnum;
	}
	delete[] StepNum;
}

void ResultProcess::Init(float posX, float posY)
{
	//�X�e�b�v���̕\���̂���
	for (auto& stepnum : StepNum) {
		//������
		stepnum = new CanvasUI();
		//���f���쐬
		//stepnum->CreateModel(Assets::debugFont, 60.0f, 80.0f, 12, 8);
		stepnum->CreateModel(g_Assets->Result_num, 5238 / 70, 1105 / 10, 10, 1);
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
	for (int i = 0; i < strlen(outputChar); i++)
	{
		//�����̉��Ԗڂ��擾 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		//�I�u�W�F�N�g�ɃZ�b�g����
		StepNum[i]->m_anime->SetFrameX(frameX);

		////�����̏c�Ԗڂ��擾
		//int frameY = ((int)outputChar[i] - 32) / 12;
		//StepNum[i]->m_anime->SetAnimePattern(frameY);

		//�����̈ʒu��ݒ肷��
		float posX = 20.0f / SCREEN_PARA * 4 * i;
		StepNum[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET�X�V
		StepNum[i]->m_anime->Update();

		//�`��
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
