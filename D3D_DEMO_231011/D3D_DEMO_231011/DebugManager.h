#pragma once
#include "CanvasUI.h"
#include <string>

//数字・文字・string
class DebugManager
{
private:
	//最大表示可能文字数
	static const int maxChars = 256;

	CanvasUI* m_debugASCII[maxChars];

	//初期位置(頭の文字の位置)
	float m_sPosX = 0;
	float m_sPosY = 0;


public:
	DebugManager();

	~DebugManager();

	//文字をセット＆描画
	void UpdateChar(char* outputChar);
	
	//文字列のスタート位置を設定
	void SetPosition(float posX, float posY);

	//文字を出力する
	void PrintDebugLog(float _posX, float _posY, const char* word);


	//float型数字を出力する
	void PrintDebugLog(float _posX, float _posY, const float _num);

	//int型数字を出力する
	void PrintDebugLog(float _posX, float _posY, const int _num);



};

