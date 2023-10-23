#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"

extern Assets* g_Assets;

Game::Game()
{
	//�I�u�W�F�N�g������
	testObject = new Object(g_Assets->textureTest, 1, 1, 3, 4);
	//�A�j���[�V�������x��ݒ�
	testObject->m_sprite->m_anime->SetAnimeSpeed(0.01f);
	//�A�j���[�V�����p�^�[����ݒ�
	testObject->m_anime->SetAnimePattern(1);
}

void Game::Update(void)
{
	testObject->m_anime->Update();
}

Game::~Game()
{
	delete testObject;
}

void Game::Draw()
{

	D3D_ClearScreen();

	//============ ��������`�揈�� ============//
	

	testObject->m_sprite->Draw();

	
	//============ �����܂ŕ`�揈�� ============//
	 
	//Update Screen
	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
	GetD3D_DATA()->SwapChain->Present(0, 0);
}
