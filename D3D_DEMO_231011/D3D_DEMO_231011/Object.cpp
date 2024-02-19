#include "Object.h"

extern Camera* g_WorldCamera;

Object::Object(void)
{
	//図形初期化
	m_sprite = new Sprite();

	//カメラ初期化
	m_sprite->m_camera = g_WorldCamera;


}

void Object::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) 
{
	//モデル作成
	m_sprite->CreateModel(texture, _width, _height, splitX, splitY);
}

void Object::GenerateColliderData()
{
	//m_extents.x = m_sprite->GetExtents().x * m_sprite->m_scale.x;
	//m_extents.y = m_sprite->GetExtents().y * m_sprite->m_scale.y;
	//m_extents.z = m_sprite->GetExtents().z * m_sprite->m_scale.z;

	//m_radius = m_sprite->GetCollide().radius * m_sprite->m_scale.x;
}



void Object::Update(void)
{

	//モデルのextents&radiusを更新する
	/*GenerateColliderData();*/

	//アニメーション更新
	m_sprite->m_anime->Update();

}

void Object::Draw(void)
{
	m_sprite->Draw();
}

Object::~Object(void)
{
	delete m_sprite;
	//delete m_collider;
}
