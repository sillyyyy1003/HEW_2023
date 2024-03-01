#include "CanvasUI.h"
#include "ObjectAnimation.h"

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
	m_camera = g_WorldCamera;

	//モデル作成
	Sprite::CreateModel(texture, _width, _height, splitX, splitY);

	if (splitX == 1 && (splitY == 1 || splitY == 2)) {
		m_anime = new Animation(m_split.x, m_split.y);
	}
	else {
		m_anime = new ObjectAnimation(m_split.x, m_split.y);
	}
}

void CanvasUI::InitAnimation(bool isMultiPattern)
{
	//アニメーションを配置
	dynamic_cast<ObjectAnimation*>(m_anime)->SetMultiPattern(isMultiPattern);

	if (isMultiPattern) {
		dynamic_cast<ObjectAnimation*>(m_anime)->InitAnimation(m_split.x);
	}
	else {
		int num = m_split.x * m_split.y;
		dynamic_cast<ObjectAnimation*>(m_anime)->InitAnimation(num);
	}
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

