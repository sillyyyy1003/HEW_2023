#pragma once
#include "Material.h"
#include "Camera.h"
#include "Animation.h"


/// <summary>
/// ���_�f�[�^��\���\����
/// </summary>
struct VERTEX
{
	float x, y, z;		//���_�̈ʒu���W
	float u, v;			//�e�N�X�`����UV���W

};

struct BOX
{
	float fLeft, fTop, fRight, fBottom;
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

protected:


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

	//�J����
	Camera* m_camera = nullptr;

	//�A�j���[�V����
	Animation* m_anime = nullptr;

	//���s���e���������e���g���̔��f
	bool isPerspective = false;
public:

	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//

	// ���f���̍쐬->�p��
	//Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);
	
	///�R���X�g���N�^
	Sprite(void);

	/// <summary>
	/// ���f���̍쐬
	/// </summary>
	/// <param name="texture">�e�N�X�`��</param>
	/// <param name="_width">��ʂɕ`�悷�镝</param>
	/// <param name="_height">��ʂɕ`�悷�鍂��</param>
	/// <param name="splitX">������</param>
	/// <param name="splitY">�c����</param>
	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	/// <summary>
	/// �ʒu�̏�����
	/// </summary>
	void InitPos(float x, float y, float z);

	/// <summary>
	/// �V�F�[�_�[�ɓn���s��̏������s���֐�(��]/�g��k��)
	/// ���s���e�p
	/// </summary>
	/// <param name="cb">�V�F�[�_�[�ɓn���s��</param>
	virtual void GenerateMatrix(CONSTBUFFER& cb);


	/// <summary>
	/// �`����s���֐�
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// ��Еt��
	/// </summary>
	~Sprite(void);

};

