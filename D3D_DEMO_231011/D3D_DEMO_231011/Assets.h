#pragma once
#include"Direct3D/Direct3D.h"
#include"WICTextureLoader.h"	//�e�N�X�`���ǂݍ��݃��C�u����

class Assets
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	ID3D11ShaderResourceView* textureTest;


public:
	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//

	//�R���X�g���N�^
	Assets();

	//�f�X�g���N�^
	~Assets();

	/*
		@brief	�t�@�C���ǂݍ��݂��s���֐�
		@param	�t�@�C����
		@return SRV�̃|�C���^�[
	*/
	ID3D11ShaderResourceView* LoadTexture(const char* _fileName);

};

