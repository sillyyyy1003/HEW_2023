#include "CanvasUI.h"
#include "StaticAnimation.h"

extern Camera* g_WorldCamera;

CanvasUI::CanvasUI()
{
}

CanvasUI::~CanvasUI()
{
}

void CanvasUI::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//�J�����̎g�p���ւ���
	isUseCamera = false;

	//���f���쐬
	Sprite::CreateModel(texture, _width, _height, splitX, splitY);

	//�A�j���[�V������z�u
	m_anime = new Animation(splitX,splitY);

	m_camera = g_WorldCamera;

}

void CanvasUI::Update(void)
{
	//UV���W�̍X�V
	m_anime->Update();

}
