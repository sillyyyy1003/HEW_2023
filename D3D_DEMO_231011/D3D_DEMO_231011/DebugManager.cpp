#include "DebugManager.h"
#include "Assets.h"



DebugManager::DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		//������
		pASCII = new CanvasUI();
		//���f���쐬
		pASCII->CreateModel(Assets::debugFont,20.0f, 20.0f, 12, 8);
	}
}


DebugManager::~DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		delete pASCII;
	}
}

void DebugManager::UpdateChar(char* outputChar)
{
	for (int i = 0; i < strlen(outputChar); i++) 
	{
		//�����̉��Ԗڂ��擾 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 12;
		//�I�u�W�F�N�g�ɃZ�b�g����
		m_debugASCII[i]->m_anime->SetFrameX(frameX);

		//�����̏c�Ԗڂ��擾
		int frameY = ((int)outputChar[i] - 32) / 12;
		m_debugASCII[i]->m_anime->SetAnimePattern(frameY);

		//�����̈ʒu��ݒ肷��
		float posX = 20.0f / SCREEN_PARA * i;
		m_debugASCII[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET�X�V
		m_debugASCII[i]->m_anime->Update();


		//�`��
		m_debugASCII[i]->Draw();

	}



}

void DebugManager::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const char* word)
{
	//������ɓ]��
	char str[256];
	snprintf(str, 255, "%s", word);
	//�X�^�[�g�ʒu��ݒ�
	SetPosition(_posX, _posY);
	//�X�V�ƕ`��
	UpdateChar(str);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const float _num)
{
	//������ɓ]��
	char str[32];
	snprintf(str, 31, "%f", _num);
	//�X�^�[�g�ʒu��ݒ�
	SetPosition(_posX, _posY);
	//�X�V�ƕ`��
	UpdateChar(str);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const int _num)
{
	//������ɓ]��
	char str[32];
	snprintf(str, 31, "%d", _num);
	//�X�^�[�g�ʒu��ݒ�
	SetPosition(_posX, _posY);
	//�X�V�ƕ`��
	UpdateChar(str);
}
