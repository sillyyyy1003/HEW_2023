#include "TestObject.h"
#include "KBInput.h"

extern Camera* g_WorldCamera;
extern KBInput* g_KbInput;

TestObject::TestObject()
{
	//図形初期化
	m_objSprite = new Sprite();
	m_shadowSprite = new Sprite();

	//カメラ初期化
	m_objSprite->m_camera = g_WorldCamera;
	m_shadowSprite->m_camera = g_WorldCamera;
}

void TestObject::SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_objSprite->CreateModel(texture, _width, _height, splitX, splitY);
}

void TestObject::SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_shadowSprite->CreateModel(texture, _width, _height, splitX, splitY);
}

void TestObject::Update(void)
{
	//操作で設定する用のベクトル変数
	XMFLOAT3 dir = { 0,0,0 };
	float moveSpeed = 0.0f;

	if (g_KbInput->GetKeyPress(VK_DOWN))
	{
		//オブジェクトの移動
		dir.y = -1;
		dir.x = dir.y / tan(XMConvertToRadians(30));
		moveSpeed = 0.01f;

		//影の変化
		//大きさの変化
		m_shadowSprite->m_scale.x += 0.01;
		m_shadowSprite->m_scale.y += 0.01;
		//
	}


	if (dir.x != 0.0f || dir.y != 0.0f) 
	{
		m_dir = dir;
	}

	XMVECTOR vector = XMLoadFloat3(&m_dir);
	vector = XMVector3Normalize(vector);
	XMStoreFloat3(&m_dir, vector);

	m_objSprite->m_pos.x = m_objSprite->m_pos.x + m_dir.x * moveSpeed;
	m_objSprite->m_pos.y = m_objSprite->m_pos.y + m_dir.y * moveSpeed;

}

void TestObject::Draw(void)
{
	
	m_shadowSprite->Draw();

	m_objSprite->Draw();
}

TestObject::~TestObject()
{
	delete m_objSprite;
	delete m_shadowSprite;
}
