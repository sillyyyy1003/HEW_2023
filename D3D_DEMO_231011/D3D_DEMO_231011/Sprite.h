#pragma once
#include "Material.h"
#include "Animation.h"
#include "Camera.h"


/// <summary>
/// ���_�f�[�^��\���\����
/// </summary>
struct VERTEX
{
	float x, y, z;		//���_�̈ʒu���W
	float u, v;			//�e�N�X�`����UV���W

};

//�萔�o�b�t�@�p�\����
struct CONSTBUFFER
{
	DirectX::XMMATRIX matrixTex;		//UV���W�ړ��s��
	DirectX::XMMATRIX matrixProj;		//���e�s��
	DirectX::XMMATRIX matrixWorld;		//���[���h�ϊ��s��
	DirectX::XMFLOAT4 materialDiffuse;	//�}�e���A���F
};

/// <summary>
/// �摜�̏����ƕ`��
/// </summary>
class Sprite :public Material
{
private:

	//�X�v���C�g�̖��O��ݒ�A�G���[�`�F�b�N�Ɏg��
	//char m_Name[256];


public:
	//----------------------------//
	// �ϐ�
	//----------------------------//

	//���z���E�̃��[���h���W
	DirectX::XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };

	//��]
	DirectX::XMFLOAT3 m_rotation = { 0.0f, 0.0f, 0.0f };

	//�摜�̑傫��(Default Data:1.0)
	DirectX::XMFLOAT3 m_scale = { 1.0, 1.0f, 1.0f };

	//�c������->�`��p
	DirectX::XMINT2 m_split = { 1,1 };

	//���̃L�����N�^�[�̃}�e���A���F(DEFAULT COLOR:WHITE)
	DirectX::XMFLOAT4 m_materialDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	Camera* m_camera;

	Animation* m_anime = nullptr;

public:

	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//

	/// <summary>
	/// ���f���̍쐬
	/// </summary>
	/// <param name="texture">�e�N�X�`��</param>
	/// <param name="_width">��ʂɕ`�悷�镝</param>
	/// <param name="_height">��ʂɕ`�悷�鍂��</param>
	/// <param name="splitX">������</param>
	/// <param name="splitY">�c����</param>
	Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	/// <summary>
	/// �V�F�[�_�[�ɓn���s��̏������s���֐�(��]/�g��k��)
	/// </summary>
	/// <param name="cb">�V�F�[�_�[�ɓn���s��</param>
	void GenerateMatrix(CONSTBUFFER& cb);


	/// <summary>
	/// �`����s���֐�
	/// </summary>
	virtual void Draw(void);


};

