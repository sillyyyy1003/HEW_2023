#include "Game.h"
#include "Direct3D/Direct3D.h"

Game::Game()
{
}

Game::~Game()
{
	
}

void Game::Draw()
{

	D3D_ClearScreen();

	//============ ��������`�揈�� ============//




	//============ ��������`�揈�� ============//
	 
	//Update Screen
	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
	GetD3D_DATA()->SwapChain->Present(0, 0);
}
