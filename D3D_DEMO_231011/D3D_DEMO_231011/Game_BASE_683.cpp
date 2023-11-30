#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

extern Assets* g_Assets;
extern KBInput* g_KbInput;


Game::Game()
{
	////�I�u�W�F�N�g������
	//testObject = new Object(g_Assets->testchar01, 96, 96, 3, 4);
	////�A�j���[�V�����N���X������->�ǂ̃A�j���[�V�����ɂ���
	//testObject->m_sprite->m_anime = new ObjectAnimation(3, 4);
	////�A�j���[�V�������x��ݒ�
	//testObject->m_sprite->m_anime->SetAnimeSpeed(0.1f);
	////�A�j���[�V�����p�^�[����ݒ�
	//testObject->m_sprite->m_anime->SetAnimePattern(0);

	testObj = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
	testObj->SetObjTex(g_Assets->testObj, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-2, -1.16, 0.1f);
	

	//�e�̏����ݒ�
	testObj->SetShadowTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj->m_shadowSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_shadowSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_shadowSprite->m_anime->SetAnimePattern(0);
	testObj->m_shadowSprite->InitPos(1.7, 0.712, 0.2f);


	//�I�u�W�F�N�g������
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//�O��̈ʒu�ݒ���N���X���ōs��
	//�A�j���[�V�����N���X������->�ǂ̃A�j���[�V�����ɂ���
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//�A�j���[�V�������x��ݒ�
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//�A�j���[�V�����p�^�[����ݒ�
	testBg->m_sprite->m_anime->SetAnimePattern(0);

	


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
	testBg->Update();
	testObj->Update();
	//testObject->Update();
}

void Game::StageUpdate(void)
{
}

void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	//delete testObject;
	delete testObj;
	delete testBg;
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
	testBg->m_sprite->Draw();

	testObj->Draw();


	//testBg->m_sprite->Draw();
	//testObject->m_sprite->Draw();
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
