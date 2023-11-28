#include "DebugManager.h"
#include "Assets.h"

DebugManager::DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		//初期化
		pASCII = new CanvasUI();
		pASCII->CreateModel(Assets::debugFont, 16.2f, 32.0f, 12, 8);
	}
}


DebugManager::~DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		delete pASCII;
	}
}

void DebugManager::UpdateChar(void)
{
}
