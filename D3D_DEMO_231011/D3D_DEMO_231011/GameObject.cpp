#include "GameObject.h"
#include "KBInput.h"
#include <math.h>

extern KBInput* g_KbInput;
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
	//ベクトル計算用の型に入れる
	XMVECTOR objVector = XMLoadFloat3(&objPos);
	XMVECTOR lightVector = XMLoadFloat3(&lightPos);
	//光からオブジェクトのベクトルを計算する
	XMVECTOR directionVector = XMVectorSubtract(objVector, lightVector);
	//正規化する
	directionVector = XMVector3Normalize(directionVector);

	//ベクトルとx/y軸の内積を計算する
	float xProduct = XMVectorGetX(XMVector3Dot(directionVector, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f))); 
	float yProduct = XMVectorGetX(XMVector3Dot(directionVector, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	
	//ラジアンを計算する
	float xangle = asin(xProduct); 
	float yangle = acos(yProduct); 
	
	//ラジアンから角度に変換
	float xDegrees = DirectX::XMConvertToDegrees(xangle); 
	float yDegrees = DirectX::XMConvertToDegrees(yangle); 
	
	//長さを計算する
	float zLenth = m_shadow->m_obj->m_pos.z - lightPos.z;
	float xLenth = zLenth / tan(xDegrees);
	float yLenth = zLenth / tan(yDegrees);

	//角度の中心位置を計算する
	float posX = xLenth;
	
	float posY = yLenth;


	XMFLOAT3 shadowPos = XMFLOAT3(posX, posY, m_shadow->m_obj->m_pos.z);
	
	//できた値を返す
	return shadowPos;
}

void GameObject::Update(DirectX::XMFLOAT3 lightPos)
{	
	//オブジェクト情報更新
	
	//テスト
	if (g_KbInput->GetKeyPress(VK_UP)) {
		//キャラクター移動
		m_obj->m_pos.z += 0.03f;

	}
	if (g_KbInput->GetKeyPress(VK_DOWN)) {
		m_obj->m_pos.z -= 0.03f;
	}

	if (g_KbInput->GetKeyPress(VK_LEFT)) {
		m_obj->m_pos.x -= 0.03f;
	}

	
	

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
