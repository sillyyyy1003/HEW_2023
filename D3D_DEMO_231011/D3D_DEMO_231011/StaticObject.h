#pragma once
#include "Direct3D/Direct3D.h"
class Sprite;

//�����Ȃ��I�u�W�F�N�g
class StaticObject
{
private:
	//�}�`��������
	Sprite* m_sprite;
	
public:

	//�R���X�g���N�^
	StaticObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//game loop�Ŗ���Ăяo�����֐�
	void Update(void);
	
	void Draw(void);

	~StaticObject(void);


};

