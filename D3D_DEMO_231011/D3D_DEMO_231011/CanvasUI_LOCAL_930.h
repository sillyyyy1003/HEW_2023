#pragma once
#include "Sprite.h"

class CanvasUI :public Sprite
{
private:
	//表示の切り替え
	bool isActive = true;

public:
	enum STATUS {
		ACTIVE,		//起動している時
		INACTIVE,	//
	};
	

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

	
};

