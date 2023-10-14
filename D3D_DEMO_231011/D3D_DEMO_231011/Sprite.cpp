#include "Sprite.h"

Sprite::Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, float splitX, float splitY)
{
	

	const float left = -(_width / 2.0f); 
	const float right = _width / 2.0f;
	const float top = _height / 2.0f;;
	const float bottom = -(_height / 2.0f);
	const float z = 0.0f;

	const float u = 1.0 / splitX;
	const float v = 1.0 / splitY;
	

	VERTEX vertexList[] = {

		//���_�����v���ɎO�p�`���`�����鑤���|���S���̕\�ɂȂ�
		{left,	top,	z,0.0f,	0.0f},		//����
		{right,	bottom,	z,u,	v},			//�E��
		{left,	bottom,	z,0.0f,	v},			//����
		
		{left,	top,	z,0.0f,	0.0f},		//����
		{right,	top,	z,u,	0.0f},		//�E��
		{right,	bottom,	z,u,	v},			//�E��

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

void Sprite::Draw(void)
{

}
