#include "Sprite.h"
#include "Camera.h"
#include "Assets.h"
#include "CDInput.h"

extern Assets* g_Assets;

//Sprite::Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
//{
//	//�c��������ݒ�
//	m_split=(XMINT2(splitX, splitY));
//
//
//	//���f�����_�f�[�^�쐬
//	//Notion:*1.25/96 -> ���͂����摜�̑傫�������̂܂ܕ\�����邽��
//	const float left = -(_width / 2.0f) * 1.25 / 96;
//	const float right = (_width / 2.0f) * 1.25 / 96;
//	const float top = (_height / 2.0f) * 1.25 / 96;
//	const float bottom = -(_height / 2.0f) * 1.25 / 96;
//	const float z = 0.0f;
//
//	//��������̃e�N�X�`���A�ꖇ���̑傫���i���A���j
//	const float u = 1.0 / m_split.x;
//	const float v = 1.0 / m_split.y;
//
//	VERTEX vertexList[] = {
//
//		//���_�����v���ɎO�p�`���`�����鑤���|���S���̕\�ɂȂ�
//		{left,	top,	z,	0.0f,	0.0f},		//����
//		{right,	bottom,	z,	u,		v},			//�E��
//		{left,	bottom,	z,	0.0f,	v},			//����
//		
//		{left,	top,	z,	0.0f,	0.0f},		//����
//		{right,	top,	z,	u,		0.0f},		//�E��
//		{right,	bottom,	z,	u,		v},			//�E��
//
//	};
//
//	// ���_�o�b�t�@���쐬����
//	D3D11_BUFFER_DESC bufferDesc;
//	bufferDesc.ByteWidth = sizeof(vertexList);// �m�ۂ���o�b�t�@�T�C�Y���w��
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
//	bufferDesc.CPUAccessFlags = 0;
//	bufferDesc.MiscFlags = 0;
//	bufferDesc.StructureByteStride = 0;
//
//	D3D11_SUBRESOURCE_DATA subResourceData;
//	subResourceData.pSysMem = vertexList;// VRAM�ɑ���f�[�^���w��
//	subResourceData.SysMemPitch = 0;
//	subResourceData.SysMemSlicePitch = 0;
//
//	HRESULT hr=GetD3D_Device()->CreateBuffer(&bufferDesc, &subResourceData, &(m_modelData.vertexBuffer));
//
//	if (FAILED(hr)) {
//		throw hr;
//		MessageBoxA(NULL, "���_�o�b�t�@�̍쐬���s�I", "�G���[����", MB_OK | MB_ICONERROR);
//	}
//
//	//�e�N�X�`��������
//	SetTexture(texture);
//}


Sprite::Sprite(void)
{
}

void Sprite::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//�c��������ݒ�
	m_split.x = splitX;
	m_split.y = splitY;

	//���f�����_�f�[�^�쐬
	//Notion:*1.25/96 -> ���͂����摜�̑傫�������̂܂ܕ\�����邽��
	const float left = -(_width / 2.0f) * 1.25 / 96;
	const float right = (_width / 2.0f) * 1.25 / 96;
	const float top = (_height / 2.0f) * 1.25 / 96;
	const float bottom = -(_height / 2.0f) * 1.25 / 96;
	const float z = 0.0f;

	//��������̃e�N�X�`���A�ꖇ���̑傫���i���A���j
	const float u = 1.0 / m_split.x;
	const float v = 1.0 / m_split.y;

	VERTEX vertexList[] = {

		//���_�����v���ɎO�p�`���`�����鑤���|���S���̕\�ɂȂ�
		{left,	top,	z,	0.0f,	0.0f},		//����
		{right,	bottom,	z,	u,		v},			//�E��
		{left,	bottom,	z,	0.0f,	v},			//����
		
		{left,	top,	z,	0.0f,	0.0f},		//����
		{right,	top,	z,	u,		0.0f},		//�E��
		{right,	bottom,	z,	u,		v},			//�E��

	};

	// ���_�o�b�t�@���쐬����
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// �m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr=GetD3D_Device()->CreateBuffer(&bufferDesc, &subResourceData, &(m_modelData.vertexBuffer));

	if (FAILED(hr)) {
		throw hr;
		MessageBoxA(NULL, "���_�o�b�t�@�̍쐬���s�I", "�G���[����", MB_OK | MB_ICONERROR);
	}

	//�e�N�X�`��������
	SetTexture(texture);
}

void Sprite::InitPos(float x, float y, float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Sprite::GenerateMatrix(CONSTBUFFER& cb)
{
	//���s���e�̍s��쐬
	XMMATRIX matrixProj = XMMatrixOrthographicLH(RATIO_W, RATIO_H, 0.0f, 3.0f);
	XMMATRIX matrixView = m_camera->GetMatrixView();
	matrixProj = matrixView * matrixProj;
	
	//���[���h�ϊ��s��̍쐬
	//�ړ��s��
	XMMATRIX matrixMove = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	//�g��k���s��
	XMMATRIX matrixScale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	//��]�s��
	XMMATRIX matrixRotateX = XMMatrixRotationX(XMConvertToRadians(m_rotation.x));
	XMMATRIX matrixRotateY = XMMatrixRotationY(XMConvertToRadians(m_rotation.y));
	XMMATRIX matrixRotateZ = XMMatrixRotationZ(XMConvertToRadians(m_rotation.z));
	XMMATRIX matrixRotate = matrixRotateX * matrixRotateY * matrixRotateZ;
	XMMATRIX matrixWorld = matrixScale * matrixRotate * matrixMove;

	//UV�A�j���[�V�����s��쐬
	XMMATRIX matrixTex = XMMatrixTranslation(m_anime->GetUVOffset().x, m_anime->GetUVOffset().y, 0.0f);
	
	cb.matrixProj = XMMatrixTranspose(matrixProj);
	cb.matrixTex = XMMatrixTranspose(matrixTex);
	cb.matrixWorld = XMMatrixTranspose(matrixWorld);
	//�}�e���A���F��萔�o�b�t�@�f�[�^�ɑ��
	cb.materialDiffuse = m_materialDiffuse;
}

void Sprite::RotateObj(XMFLOAT3& rot)
{

	enum VALUE
	{
		val = 1,//�e�X�g�̒l
	};
	
	float fval = 0.2;//�e�X�g�̒l


	POINT mouseMovePos = CdInput::Get()->GetMouseMove();


	/*rot.x += mouseMovePos.y * val;*/
	rot.x = m_rotation.x += mouseMovePos.y * val*fval;
	rot.y = m_rotation.y += mouseMovePos.x * val*fval;
}





void Sprite::Draw(void)
{
	UINT strides = sizeof(VERTEX);
	UINT offsets = 0;

	//�s��쐬
	CONSTBUFFER cb;
	GenerateMatrix(cb);

	//�s����V�F�[�_�[�ɓn��
	GetD3D_Context()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &cb, 0, 0);

	//�`�悷�钸�_�o�b�t�@(���f��)���w�肷��
	GetD3D_Context()->IASetVertexBuffers(0, 1, &Material::m_modelData.vertexBuffer, &strides, &offsets);

	//�s�N�Z���V�F�[�_�[�Ƀe�N�X�`����n��
	GetD3D_Context()->PSSetShaderResources(0, 1, &Material::m_modelData.texture);

	//vertexCount:�`�悷�钸�_��
	GetD3D_Context()->Draw(6, 0);


}

Sprite::~Sprite(void)
{
	//
	delete m_anime;
}




