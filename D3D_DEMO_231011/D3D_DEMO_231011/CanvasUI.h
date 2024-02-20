#pragma once
#include "Sprite.h"
#include <vector>

class CanvasUI :public Sprite
{
private:
	//表示の切り替え
	bool isActive = true;

	//Has Animation or Not
	bool isAnimated = false;

	//フレームの枚数
	int m_frameNum = 0;

	std::vector<int> animeTable;

	//ループするかどうか
	bool isLoop = true;



public:
	enum STATUS {
		ACTIVE = 0,		//起動している時
		INACTIVE = 1,	//
	};
	
	//多種のアニメパターンを持つかどうか
	bool isMultiPattern = false;

public:
	CanvasUI();

	~CanvasUI();


	//モデル作成・アニメーション配置・カメラ使用
	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) override;

	//UV座標更新
	void Update(void);

	//状態を獲得
	bool GetActive(void) { return isActive; };
	//状態の切り替え
	void SetActive(bool status) { isActive = status; };

	void Draw(void) override;

	void InitPos(float x, float y, float z) { m_pos = DirectX::XMFLOAT3{ x,y,z }; };

	//アニメパターンの変更
	void SetAnimeActive(STATUS status) { m_anime->SetAnimePattern(status); };

	//アニメション用
	void InitAnimation(int num);

	//アニメションの状態
	void SetAnimeted(bool isAnimated) { this->isAnimated = isAnimated; };
	bool GetAnimated(void) { return this->isAnimated; };

	void SetLoop(bool isLoop) { this->isLoop = isLoop; };
	bool GetLoop(void) { return isLoop; };
	

};