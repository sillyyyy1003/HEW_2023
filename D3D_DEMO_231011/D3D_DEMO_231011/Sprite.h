#pragma once
#include "Material.h"


/// <summary>
/// ���_�f�[�^��\���\����
/// </summary>
struct VERTEX
{

	float x, y, z;		//�ʒu���W
	float u, v;			//�e�N�X�`����UV���W

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
	//���f���̏����i�[����ϐ�
	VERTEX m_BaseData;

	//��]
	DirectX::XMFLOAT3 m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	//�摜�̑傫��(Default Data:1.0)
	DirectX::XMFLOAT3 m_scale = DirectX::XMFLOAT3(1.0, 1.0f, 1.0f);



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
	Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, float splitX, float splitY);

	/// <summary>
	/// �V�F�[�_�[�ɓn���s��̏������s���֐�(��]/�g��k��)
	/// </summary>
	/// <param name="cb">�V�F�[�_�[�ɓn���s��</param>
	void GenerateMatrix(CONSTBUFFER& cb);


	virtual void Draw(void);












};

