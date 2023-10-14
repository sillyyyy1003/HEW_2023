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

	//============ ここから描画処理 ============//




	//============ ここから描画処理 ============//
	 
	//Update Screen
	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}
