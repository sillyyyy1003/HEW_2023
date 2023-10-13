#pragma once
#include "Direct3D/Direct3D.h"

struct BASEDATA 
{

	float x, y, z;		//�ʒu���W
	float u, v;			//�e�N�X�`����UV���W

};

struct MODELDATA 
{
	ID3D11Buffer* m_VertexBuffer;			//���_�o�b�t�@
	ID3D11ShaderResourceView* m_Texture;	//�e�N�X�`��

};
class Graphics
{
protected:
	
	BASEDATA	m_graphicData = {};
	MODELDATA	m_modelData = {};

public:

	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//
	/*
		�f�X�g���N�^	
	*/
	~Graphics();

	/*
		@brief	
		@param	
		@return	
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);

	/*
		@brief	�`��̐ݒ�ƕ`��
		@param	����
		@return	����
	*/
	virtual void Draw(void);


};

