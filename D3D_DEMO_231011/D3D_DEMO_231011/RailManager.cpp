#include "RailManager.h"
#include "Game.h"
#include "GameObject.h"

RailManager::~RailManager()
{
}

RailManager* RailManager::Get()
{
	static RailManager instance;
	return &instance;
}

void RailManager::InitRail()
{
	for (int i = 0; i < 15; i++) {
	
		//1全部をオープンにする
		m_info[i].isVacant = true;

		//2
		for (int j = 0; j < 8; j++) 
		{
			m_info[i].isMoveable[j] = false;
		}
		
	}

}

void RailManager::InitRailPos(void)
{


	for (auto& element : Game::Get()->GetObjectList()) {
		//位置を獲得
		int pos = element->GetRailPos().verticalPos * 5 + element->GetRailPos().horizontalPos;

		//情報更新
		RailManager::Get()->m_info[pos].isVacant = true;
	}

}
