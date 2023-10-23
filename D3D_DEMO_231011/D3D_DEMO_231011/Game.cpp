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

void Game::GameUpdate(void)
{
	switch (m_gameScene)
	{
	case TITLE:

		TitleUpdate();
		break;
		
	case STAGE1:

		StageUpdate();
		break;

	case RESULT:

		ResultUpdate();
		break;

	}
}

void Game::TitleUpdate(void)
{
	testObject->Update();
}

void Game::StageUpdate(void)
{
}

void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	delete testObject;
}

void Game::GameDraw()
{

	D3D_ClearScreen();

	//============ ��������`�揈�� ============//
	
	switch (m_gameScene) 
	{
		switch (m_gameScene)
		{
		case TITLE:

			TitleDraw();
			break;

		case STAGE1:

			StageDraw();
			break;

		case RESULT:

			ResultDraw();
			break;

		}

	}

	//============ �����܂ŕ`�揈�� ============//
	 
	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	testObject->m_sprite->Draw();
}

void Game::StageDraw(void)
{
}

void Game::ResultDraw(void)
{
}

void Game::SetGameScene(GAMESCENE scene)
{
	m_gameScene = scene;
}
