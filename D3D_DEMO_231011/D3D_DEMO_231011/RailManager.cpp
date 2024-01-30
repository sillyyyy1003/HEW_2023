#include "RailManager.h"

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
	
		//1�S�����I�[�v���ɂ���
		m_info[i].isVacant = true;

		//2
		for (int j = 0; j < 8; j++) 
		{
			m_info[i].isMoveable[j] = false;
		}
		
	}

}
