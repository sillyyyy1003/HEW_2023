#include "GameObject.h"
#include <math.h>

extern Camera* g_WorldCamera;

GameObject::GameObject()
{
	m_obj = new Sprite();
	m_shadow = new ShadowObject();

	m_obj->m_camera = g_WorldCamera;
}

void GameObject::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateModel(texture, _width, _height, splitX, splitY);
}

void GameObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_shadow->CreateShadow(texture, _width, _height, splitX, splitY);
}


DirectX::XMFLOAT3 GameObject::GenerateShadowPos(DirectX::XMFLOAT3 lightPos)
{
	// 単位ベクトル化する
	//オブジェクトの位置取得
	const XMFLOAT3 objPos = m_obj->m_pos; 

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
	float wallZ = m_shadow->m_obj->m_pos.z;  // 墙壁的Z坐标

	// 距離比率を計算する(计算交点的Z值等于墙壁的Z值时的t)
	float t = (wallZ - lightPos.z) / XMVectorGetZ(directionVector);

	//影の位置を計算する
	XMFLOAT3 shadowPosition;
	shadowPosition.x = lightPos.x + t * XMVectorGetX(directionVector);
	shadowPosition.y = lightPos.y + t * XMVectorGetY(directionVector);
	shadowPosition.z = wallZ;  //影のｚ軸

	return shadowPosition;
}

void GameObject::Update(DirectX::XMFLOAT3 lightPos)
{	
	//オブジェクト情報更新
	
	

	//影情報更新
	m_shadow->m_obj->m_pos = GenerateShadowPos(lightPos);
	
	//アニメーション更新
	Update();//オブジェクト本体
	m_shadow->Update();//影


}

void GameObject::Update(void)
{
	m_obj->m_anime->Update();
}

void GameObject::Draw(void)
{
	m_shadow->Draw();

	m_obj->Draw();
}

GameObject::~GameObject()
{
	delete m_obj;
	delete m_shadow;

}
