#pragma once
#include "Direct3D/Direct3D.h"



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
		@brief	�ǂݍ��ݍς݂̃e�N�X�`�����󂯎��
		@param	�ǂݍ��ݍς݂̃e�N�X�`���|�C���^�[
		@return	����
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);














};


