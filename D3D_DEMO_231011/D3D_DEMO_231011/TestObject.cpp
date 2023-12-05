#include "TestObject.h"
#include "CDInput.h"

extern Camera* g_WorldCamera;





TestObject::TestObject()
{
	//�}�`������
	m_objSprite = new Sprite();
	m_shadowSprite = new Sprite();

	//�J����������
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
	//����Őݒ肷��p�̃x�N�g���ϐ�
	XMFLOAT3 dir = { 0,0,0 };

	float moveSpeed = 0.0f;


/*----�ړ�----------------------------------------------------------*/
	//���L�[
	if ((CdInput::Get()->GetKeyPress(DIK_DOWN)))
	{
		//�I�u�W�F�N�g�̈ړ�
		dir.y = -1;
		dir.x = dir.y / tan(XMConvertToRadians(30));
		moveSpeed = 0.01f;

		//�e�̕ω�
		//�傫���̕ω�
		m_shadowSprite->m_scale.x += 0.01;
		m_shadowSprite->m_scale.y += 0.01;
	}

	//��L�[
	if ((CdInput::Get()->GetKeyPress(DIK_UP)))
	{
		//�I�u�W�F�N�g�̈ړ�
		dir.y = +1;
		dir.x = dir.y / tan(XMConvertToRadians(30));
		moveSpeed = 0.01f;

		//�e�̕ω�
		//�傫���̕ω�
		m_shadowSprite->m_scale.x -= 0.01;
		m_shadowSprite->m_scale.y -= 0.01;
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
	/*----------------------------------------------------------------*/


/*----��] m_rotation--------------------------------------------------*/

    //�I�u�W�F�N�g�̉�]
	m_objSprite->RotateObj(m_rotation);

	//�e�̉�]
	m_shadowSprite->RotateObj(m_rotation);

	//�����i�������j
	//if (m_objSprite->m_rotation.x < 0.6 || m_objSprite->m_rotation.x > 0 && 
	//	m_objSprite->m_rotation.y < 0.6 || m_objSprite->m_rotation.y > 0)
	//{
	//	m_objSprite->RotateObj(m_rotation);
	//}

	//m_shadowSprite->m_rotation.y = m_objSprite->m_rotation.y;
	//m_shadowSprite->m_rotation.x = m_objSprite->m_rotation.x;






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
