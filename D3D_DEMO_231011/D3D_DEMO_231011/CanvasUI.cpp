#include "CanvasUI.h"
#include "StaticAnimation.h"

extern Camera* g_WorldCamera;

CanvasUI::CanvasUI()
{
}

CanvasUI::~CanvasUI()
{
}

void CanvasUI::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//カメラの使用を禁じる
	isUseCamera = false;

	//モデル作成
	Sprite::CreateModel(texture, _width, _height, splitX, splitY);

	//アニメーションを配置
	m_anime = new Animation(splitX,splitY);

	m_camera = g_WorldCamera;

}

void CanvasUI::Update(void)
{
	//UV座標の更新
	m_anime->Update();

}

void CanvasUI::Draw(void)
{
	if (isActive) {
		Sprite::Draw();
	}


}
