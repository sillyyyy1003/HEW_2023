#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

#include "ObjectCollision.h"
#include "SAT.h"
#include <algorithm> // �K�v�ȃw�b�_�[�t�@�C��
#define SQUREWIDTH 1.2
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846
#define M_PIX 0.1//1.5
#define M_PIY 0.0333333333// 0.5

extern Assets* g_Assets;
extern KBInput* g_KbInput;
extern ObjectCollision* g_objectCollision;

Game::Game()
{
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
	g_objectCollision->Update();
	testBg->Update();
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
	g_objectCollision->Draw();
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