#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"

extern Assets* g_Assets;

Game::Game()
{
	testObject = new Object(g_Assets->textureTest, 1, 1, 3, 4);
	testObject->m_sprite->m_anime->SetAnimeSpeed(0.01f);

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
