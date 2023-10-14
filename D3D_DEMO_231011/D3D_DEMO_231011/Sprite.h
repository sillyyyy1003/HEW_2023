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
	VERTEX m_BaseData;

	float m_OffsetU = 0.0f;
	float m_OffsetV = 0.0f;




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


	virtual void Draw(void);












};

