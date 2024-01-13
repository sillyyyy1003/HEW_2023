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
	/*m_shadow->CreateShadow(texture, _width, _height, splitX, splitY);*/
	m_shadow->CreateObject(texture, _width, _height, splitX, splitY);
}


DirectX::XMFLOAT3 GameObject::GenerateShadowPos(DirectX::XMFLOAT3 lightPos)
{
	// 単位ベクトル化する
	//オブジェクトの位置取得
	const XMFLOAT3 objPos = m_obj->m_sprite->m_pos; 

	/*
	////ベクトル計算用の型に入れる
	//XMVECTOR objVector = XMLoadFloat3(&objPos);
	//XMVECTOR lightVector = XMLoadFloat3(&lightPos);
	////光からオブジェクトのベクトルを計算する
	//XMVECTOR directionVector = XMVectorSubtract(objVector, lightVector);
	////正規化する
	//directionVector = XMVector3Normalize(directionVector);

	////ベクトルとx/y軸の内積を計算する
	//float xProduct = XMVectorGetX(XMVector3Dot(directionVector, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f))); 
	//float yProduct = XMVectorGetX(XMVector3Dot(directionVector, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	//
	////ラジアンを計算する
	//float xangle = asin(xProduct); 
	//float yangle = acos(yProduct); 
	//
	////ラジアンから角度に変換
	//float xDegrees = DirectX::XMConvertToDegrees(xangle); 
	//float yDegrees = DirectX::XMConvertToDegrees(yangle); 
	//
	////長さを計算する
	//float zLenth = m_shadow->m_obj->m_pos.z - lightPos.z;
	//float xLenth = zLenth / tan(xDegrees);
	//float yLenth = zLenth / tan(yDegrees);

	////角度の中心位置を計算する
	//float posX = xLenth;
	//
	//float posY = yLenth;


	//XMFLOAT3 shadowPos = XMFLOAT3(posX, posY, m_shadow->m_obj->m_pos.z);
	//
	////できた値を返す
	//return shadowPos;
	*/


	//ベクトル計算用の型に入れる
	XMVECTOR objVector = XMLoadFloat3(&objPos);
	XMVECTOR lightVector = XMLoadFloat3(&lightPos);
	//	////光からオブジェクトのベクトルを計算する
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
	

	m_shadow->m_sprite->m_pos = GenerateShadowPos(m_lightPos);
	
	
	
	
	//本体更新した後
	if (m_obj->m_collider != nullptr) {
		
		UpdateObjectColliderData();

	}

	//影更新した後
	if (m_shadow->m_collider != nullptr) {

		UpdateShadowColliderData();

	}

	

	//オブジェクト本体
	m_obj->Update();
	//影
	m_obj->Update();
}

void GameObject::UpdateObjectColliderData(void)
{
	////dynamic_castを使って、コライダーのデータを更新する
	//switch (m_obj->m_collider->GetColliderType()) {
	//case SPHERE:
	//	//Object
	//	//dynamic_cast<SphereCollider*>(m_obj->m_collider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_obj->m_collider)->m_radius = 1.0f;
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
	////dynamic_castを使って、コライダーのデータを更新する
	//switch (m_shadow->m_collider->GetColliderType()) {
	//case SPHERE:
	//	//Object
	//	//dynamic_cast<SphereCollider*>(m_obj->m_collider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_obj->m_collider)->m_radius = 1.0f;
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

