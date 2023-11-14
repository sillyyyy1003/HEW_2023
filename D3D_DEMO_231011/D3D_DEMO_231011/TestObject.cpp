#include "TestObject.h"
#include "KBInput.h"

extern Camera* g_WorldCamera;
extern KBInput* g_KbInput;

TestObject::TestObject()
{
	//�}�`������
	m_objSprite = new Sprite();
	//m_shadowSprite = new Sprite();

	//�J����������
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
	if (isPlayer)
	{
		//����Őݒ肷��p�̃x�N�g���ϐ�
		XMFLOAT3 dir = { 0,0,0 };
		float moveSpeed = 0.0f;

		if (g_KbInput->GetKeyPress(VK_DOWN))
		{
			//�I�u�W�F�N�g�̈ړ�
			dir.y = -1;
			moveSpeed = 0.1f;
		}
		if (g_KbInput->GetKeyPress(VK_UP))
		{
			//�I�u�W�F�N�g�̈ړ�
			dir.y = 1;
			moveSpeed = 0.1f;
		}
		if (g_KbInput->GetKeyPress(VK_RIGHT))
		{
			//�I�u�W�F�N�g�̈ړ�
			dir.x = 1;
			moveSpeed = 0.1f;
		}
		if (g_KbInput->GetKeyPress(VK_LEFT))
		{
			//�I�u�W�F�N�g�̈ړ�
			dir.x = -1;
			moveSpeed = 0.1f;
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
	else
	{
		// ���삵�Ȃ��I�u�W�F�N�g��傫�����鏈��
		if (g_KbInput->GetKeyPress(VK_SPACE))
		{
			//�傫���̕ω�
			Scale_countX += 0.013;// �����蔻����傫������
			Scale_countY += 0.013;
			m_objSprite->m_scale.x += 0.01;
			m_objSprite->m_scale.y += 0.01;
		}
	}
}

void TestObject::Draw(void)
{

	//m_shadowSprite->Draw();

	m_objSprite->Draw();
}

BOUNDING_CIRCLE TestObject::GetBoundingCircle()
{
	BOUNDING_CIRCLE bc;
	bc.center = m_objSprite->m_pos; // ����~�̒��S
	if (!isPlayer)
	{
		// ���삵�Ă��Ȃ��I�u�W�F�N�g 
		// �I�u�W�F�N�g�Ɠ����悤�ɓ����蔻����傫������
		bc.radius = 1.30f + Scale_countX; // ����~�̔��a��ݒ�
	}
	else
	{
		// ���삵�Ă���I�u�W�F�N�g
		bc.radius = 1.30f; // ����~�̔��a��ݒ�
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
	//delete m_shadowSprite;
}
