#include "Material.h"


Material::~Material()
{
	// このクラスが作ったオブジェクトだけを解放する
	SAFE_RELEASE(m_modelData.vertexBuffer);
}

void Material::SetTexture(ID3D11ShaderResourceView* _texture)
{
	m_modelData.texture = _texture;
}

