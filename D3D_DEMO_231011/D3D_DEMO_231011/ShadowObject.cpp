#include "ShadowObject.h"
#include "Camera.h"

extern Camera* g_WorldCamera;

ShadowObject::ShadowObject(void)
{

}

//void ShadowObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
//{
//	//図形作成
//	Object::CreateObject(texture, _width, _height, splitX, splitY);
//	
//}

void ShadowObject::Update(void)
{




	//アニメーションの更新
	Object::Update();


}


void ShadowObject::Draw(void)
{
	
	if (isLight) 
	{
		//光があるときだけ描画する
		Object::Draw();
	}

	
}

ShadowObject::~ShadowObject(void)
{
}
