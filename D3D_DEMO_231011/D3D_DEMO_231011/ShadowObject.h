#pragma once
#include "Sprite.h"

class ShadowObject
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	
	Sprite* m_obj;

	bool isActive = false;

	
	
	
public:
	//Constructor
	ShadowObject(void);

	//�e�̃��f���쐬
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
	void Update(void);

	BOOL CheckShadow(void);

	//�`��֐�
	void Draw(void);

	~ShadowObject(void);

};

