#include "ShadowObject.h"
#include "Camera.h"

extern Camera* g_WorldCamera;

ShadowObject::ShadowObject(void)
{
	//図形作成
	m_obj = new Sprite();

	//カメラ設置
	m_obj->m_camera = g_WorldCamera;

	//アニメーション配置
	

}

void ShadowObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateModel(texture, _width, _height, splitX, splitY);
}

void ShadowObject::Update(void)
{
	//アニメーションの更新
	m_obj->m_anime->Update();


}


void ShadowObject::Draw(void)
{
	
	if (isLight) 
	{
		//光があるときだけ描画する
		m_obj->Draw();
	}

	
}

ShadowObject::~ShadowObject(void)
{
	delete m_obj;
}
