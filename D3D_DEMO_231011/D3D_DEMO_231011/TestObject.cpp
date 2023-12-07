#include "TestObject.h"
#include "CDInput.h"

extern Camera* g_WorldCamera;





TestObject::TestObject()
{
	//図形初期化
	m_objSprite = new Sprite();
	//m_shadowSprite = new Sprite();


	//カメラ初期化
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
	//����Őݒ肷��p�̃x�N�g���ϐ�
	XMFLOAT3 dir = { 0,0,0 };

	float moveSpeed = 0.0f;


/*----�ړ�----------------------------------------------------------*/
	//���L�[
	if ((CdInput::Get()->GetKeyPress(DIK_DOWN)))
	{
		//オブジェクトの移動
		dir.y = -1;
		dir.x = dir.y / tan(XMConvertToRadians(30));
		moveSpeed = 0.01f;

		//影の変化
		//大きさの変化
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






		m_objSprite->m_pos.x = m_objSprite->m_pos.x + m_dir.x * moveSpeed;
		m_objSprite->m_pos.y = m_objSprite->m_pos.y + m_dir.y * moveSpeed;
	}
	else
	{
		// 操作しないオブジェクトを大きくする処理
		if (g_KbInput->GetKeyPress(VK_SPACE))
		{
			//大きさの変化
			Scale_countX += 0.013;// 当たり判定も大きくする
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
	bc.center = m_objSprite->m_pos; // 判定円の中心
	if (!isPlayer)
	{
		// 操作していないオブジェクト 
		// オブジェクトと同じように当たり判定も大きくする
		bc.radius = 1.30f + Scale_countX; // 判定円の半径を設定
	}
	else
	{
		// 操作しているオブジェクト
		bc.radius = 1.30f; // 判定円の半径を設定
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
