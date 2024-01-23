#include "StageManager.h"
#include "Game.h"

StageManager& StageManager::Get()
{
	static StageManager IniInstance;
	return IniInstance;
}

void StageManager::Init()
{
	Game::Get()->Init();


}

void StageManager::Update()
{

	

}

void StageManager::Draw()
{

	
}
