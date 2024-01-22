#include "TestObject.h"
#include "CDInput.h"

extern Camera* g_WorldCamera;





TestObject::TestObject()
{
	//?????
	m_objSprite = new Sprite();
	//m_shadowSprite = new Sprite();


	//??????
	m_objSprite->m_camera = g_WorldCamera;
	//m_shadowSprite->m_camera = g_WorldCamera;
}

void TestObject::SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_objSprite->CreateModel(texture, _width, _height, splitX, splitY);
}

void TestObject::SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//m_shadowSprite->CreateModel(texture, _width, _height, splitX, splitY);
}

void TestObject::Update(void)
{
	//if (isPlayer)
	//{
	//	//???????????????
	//	XMFLOAT3 dir = { 0,0,0 };
	//	float moveSpeed = 0.0f;

	//if (g_KbInput->GetKeyPress(VK_DOWN))
	//{
	//	//?????????
	//	dir.y = -1;
	//	dir.x = dir.y / tan(XMConvertToRadians(30));
	//	moveSpeed = 0.01f;

	//	//????
	//	//??????
	//	m_shadowSprite->m_scale.x += 0.01;
	//	m_shadowSprite->m_scale.y += 0.01;
	//	//
	//}


	//if (dir.x != 0.0f || dir.y != 0.0f) 
	//{
	//	m_dir = dir;
	//}

	//	XMVECTOR vector = XMLoadFloat3(&m_dir);
	//	vector = XMVector3Normalize(vector);
	//	XMStoreFloat3(&m_dir, vector);

	//	m_objSprite->m_pos.x = m_objSprite->m_pos.x + m_dir.x * moveSpeed;
	//	m_objSprite->m_pos.y = m_objSprite->m_pos.y + m_dir.y * moveSpeed;
	//}
	//else
	//{
	//	// ???????????????????
	//	if (g_KbInput->GetKeyPress(VK_SPACE))
	//	{
	//		//??????
	//		Scale_countX += 0.013;// ???????????
	//		Scale_countY += 0.013;
	//		m_objSprite->m_scale.x += 0.01;
	//		m_objSprite->m_scale.y += 0.01;
	//	}
	//}
	m_anime->Update();
}




void TestObject::Draw(void)
{

	//m_shadowSprite->Draw();

	m_objSprite->Draw();
}

BOUNDING_CIRCLE TestObject::GetBoundingCircle()
{
	BOUNDING_CIRCLE bc;
	bc.center = m_objSprite->m_pos; // ??????
	if (!isPlayer)
	{
		// ????????????? 
		// ???????????????????????
		bc.radius = 1.30f + Scale_countX; // ?????????
	}
	else
	{
		// ????????????
		bc.radius = 1.30f; // ?????????
	}
	return bc;
}

void TestObject::SetBoundingCircle(BOUNDING_CIRCLE bc)
{
	m_objSprite->m_pos = bc.center;
}

TestObject::~TestObject()
{
	delete m_objSprite;
	delete m_shadowSprite;
}
