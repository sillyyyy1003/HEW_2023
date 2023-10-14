#include "Material.h"


Material::~Material()
{
	// ���̃N���X��������I�u�W�F�N�g�������������
	SAFE_RELEASE(m_modelData.vertexBuffer);
}

void Material::SetTexture(ID3D11ShaderResourceView* _texture)
{
	m_modelData.texture = _texture;
}

