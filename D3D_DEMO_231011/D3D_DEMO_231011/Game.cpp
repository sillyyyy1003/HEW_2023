#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

extern Assets* g_Assets;
extern KBInput* g_KbInput;
extern TrackCamera* g_WorldCamera;


Game::Game()
{
	//�I�u�W�F�N�g�쐬
	testWall = new Object(g_Assets->testWallbg, 1280, 720, 1, 1);
	testGround = new Object(g_Assets->testGroundbg, 1280, 720, 1, 1);
	//testChara = new TestObject();

	//�I�u�W�F�N�g�̏����ݒ�E�e�N�X�`���̓ǂݍ���
	testChara = new Object(g_Assets->testChara01, 32, 32, 3, 4);

	/*testChara->m_objSprite->CreateModel(g_Assets->testChara01, 200, 200, 1, 1);
	testChara->m_shadowSprite->CreateModel(g_Assets->testChara01, 200, 200, 1, 1);*/

	//�I�u�W�F�N�g�̓��e��ς���


	//�A�j���[�V�����̐ݒ�
	testWall->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testGround->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_sprite->m_anime = new ObjectAnimation(3, 4);
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);
	/*testChara->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_shadowSprite->m_anime = new ObjectAnimation(1, 1);;*/


	//�����ʒu�ݒ�
	testWall->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };

	testGround->m_sprite->m_pos = { 0.0f, 1.5f,2.0f};

	testGround->m_sprite->m_rotation.x = 90;
	testGround->m_sprite->m_pos.y = -360 * 1.25 / 96 + 1.5f;

	testChara->m_sprite->m_pos.y = (-360 + 96) * 1.25 / 96 + 1.5f;
	testChara->m_sprite->m_pos.z = -0.5f;
	testChara->m_sprite->m_scale = { 3.0f,3.0f,3.0f };

	g_WorldCamera->TrackCamera::SetTarget(testChara);

	
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
	
	
	
	if (g_KbInput->GetKeyPress(VK_UP))
	{
		testChara->m_sprite->m_pos.z += 0.02f;

	}
	if (g_KbInput->GetKeyPress(VK_DOWN)) {
		testChara->m_sprite->m_pos.z -= 0.02f;
	}

	if (g_KbInput->GetKeyPress(VK_LEFT)) {
		testChara->m_sprite->m_pos.x -= 0.02f;
	}

	if (g_KbInput->GetKeyPress(VK_RIGHT)) {
		testChara->m_sprite->m_pos.x += 0.02f;
	}

	testWall->Update();
	testGround->Update();
	testChara->Update();
	


}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	
	
	
}

void Game::GameDraw()
{

	D3D_ClearScreen();

	//============ ��������`�揈�� ============//
	
	
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

	//============ �����܂ŕ`�揈�� ============//
	 
	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	testWall->Draw();

	testGround->Draw();

	testChara->Draw();
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
