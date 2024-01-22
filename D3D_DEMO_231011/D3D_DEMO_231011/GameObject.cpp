#include "GameObject.h"
#include "ShadowObject.h"
#include "SphereCollider.h"
#include <math.h>

extern Camera* g_WorldCamera;

GameObject::GameObject()
{
	//オブジェクトの初期化
	m_obj = new Object();
	//影の初期化
	m_shadow = new ShadowObject();
	
}

void GameObject::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateObject(texture, _width, _height, splitX, splitY);
}

void GameObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_shadow->CreateObject(texture, _width, _height, splitX, splitY);
}


DirectX::XMFLOAT3 GameObject::GenerateShadowPos(DirectX::XMFLOAT3 lightPos)
{
	//単位ベクトル化する
	//オブジェクトの位置取得
	const XMFLOAT3 objPos = m_obj->m_sprite->m_pos; 

	//ベクトル計算用の型に入れる
	XMVECTOR objVector = XMLoadFloat3(&objPos);
	XMVECTOR lightVector = XMLoadFloat3(&lightPos);
	//光からオブジェクトのベクトルを計算する
	XMVECTOR directionVector = XMVectorSubtract(objVector, lightVector);


	// 壁と地面の角度が90度(假设墙壁垂直于地面，沿Z轴)
	float wallZ = m_shadow->m_sprite->m_pos.z;  // 墙壁的Z坐标

	// 距離比率を計算する(计算交点的Z值等于墙壁的Z值时的t)
	float t = (wallZ - lightPos.z) / XMVectorGetZ(directionVector);

	//影の位置を計算する
	XMFLOAT3 shadowPosition;
	shadowPosition.x = lightPos.x + t * XMVectorGetX(directionVector);
	shadowPosition.y = lightPos.y + t * XMVectorGetY(directionVector);
	shadowPosition.z = wallZ;  //影のｚ軸

	return shadowPosition;
}

void GameObject::SetLightPos(DirectX::XMFLOAT3 _lightPos)
{
	m_lightPos = _lightPos;
}


void GameObject::Update(void)
{
	//ここで入力操作

	
	
	
	
	//オブジェクトと影の更新

	

	//影
	//位置を更新
	m_shadow->m_sprite->m_pos = GenerateShadowPos(m_lightPos);
	//大きさを更新
	
	
	
	////本体更新した後
	//if (m_obj->m_collider != nullptr) {
	//	
	//	//ここで具体的なCollisionのセンターやスケールを更新する
	//	UpdateObjectColliderData();

	//}

	////影更新した後
	//if (m_shadow->m_collider != nullptr) {
	//	
	//	//ここで具体的なCollisionのセンターやスケールを更新する
	//	UpdateShadowColliderData();

	//}

	

	//オブジェクト本体
	m_obj->Update();

	//影
	m_obj->Update();
}

void GameObject::UpdateObjectColliderData(void)
{
	//dynamic_castを使って、コライダーのデータを更新する
	
	//switch (m_obj->m_collider->GetColliderType()) {
	//case SPHERE:
	//	//位置と半径をリアルタイムで更新する
	//	//dynamic_cast<SphereCollider*>(m_objCollider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_objCollider)->m_radius = 1.0f;
	// //更新したデータを本体のColliderに更新する
	// m_objCollider->Update();
	//	break;

	//case POLYGON:

	//	break;

	//case SQUARE:

	//	break;

	//default:

	//}






}

void GameObject::UpdateShadowColliderData(void)
{
	//dynamic_castを使って、コライダーのデータを更新する
	
	//switch (m_shadow->m_collider->GetColliderType()) {
	//case SPHERE:
	
	//	
	//	//dynamic_cast<SphereCollider*>(m_shadowCollider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_shadowCollider)->m_radius = 1.0f;
	
	
	////更新したデータを本体のColliderに更新する
	// 	m_shadowCollider->Update();
	//	break;

	//case POLYGON:

	//	break;

	//case SQUARE:

	//	break;

	//default:

	//}




}


void GameObject::Draw(void)
{

	//影を描画する
	m_shadow->Draw();

	//オブジェクトを描画する
	m_obj->Draw();
}

GameObject::~GameObject()
{
	delete m_obj;
	delete m_shadow;

}

