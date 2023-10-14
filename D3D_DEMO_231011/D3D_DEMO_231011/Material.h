#pragma once
#include "Direct3D/Direct3D.h"

/// <summary>
/// 
/// </summary>
struct BASEDATA 
{

	float x, y, z;		//�ʒu���W
	float u, v;			//�e�N�X�`����UV���W

};

/// <summary>
/// ���_�o�b�t�@�ƃe�N�X�`����ۑ�����\����
/// </summary>
struct MODELDATA 
{
	ID3D11Buffer*				vertexBuffer;			//���_�o�b�t�@
	ID3D11ShaderResourceView*	texture;				//�e�N�X�`��

};

/// <summary>
/// �}�e���A����ۑ�����֐�
/// </summary>
class Material
{

protected:
	
	//���f�����
	MODELDATA m_modelData = {};

public:

	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//

	/*
		�f�X�g���N�^	
	*/
	~Material();

	/*
		@brief	
		@param	
		@return	
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);












	///*
	//	@brief	�`��̐ݒ�ƕ`��
	//	@param	����
	//	@return	����
	//*/
	//virtual void Draw(void);


};


