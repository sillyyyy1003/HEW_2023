#pragma once
#include "CanvasUI.h"
#include "GameObject.h"

class DebugManager
{
private:
	//最大表示可能文字数
	static const int maxChars = 256;

	CanvasUI* m_debugASCII[maxChars];

	//初期位置(頭の文字の位置)
	float SposX, SposY;


public:
	DebugManager();

	~DebugManager();

	void UpdateChar(void);

	void SetPosition(float posX, float posY);




};

