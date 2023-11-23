#pragma once
#include "Sprite.h"
#include <vector>
#include "ShadowObject.h"

class GameObject
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	//�I�u�W�F�N�g�̐}�`���
	Sprite* m_obj;
	
	//�e�̐}�`���
	//std::vector<Sprite*> m_shadow;
	ShadowObject* m_shadow;


	//�������邩�ǂ���
	bool isLit = false;
	
public:
	//�R���X�g���N�^
	GameObject();

	/// <summary>
	/// �I�u�W�F�N�g�̃��f�������
	/// </summary>
	/// <param name="texture">�e�L�X�`���[</param>
	/// <param name="_width">��</param>
	/// <param name="_height">����</param>
	/// <param name="splitX">������</param>
	/// <param name="splitY">�c����</param>
	void CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	/// <summary>
	/// �e�̃��f�������
	/// </summary>
	/// <param name="texture">�e�L�X�`���[</param>
	/// <param name="_width">��</param>
	/// <param name="_height">����</param>
	/// <param name="splitX">������</param>
	/// <param name="splitY">�c����</param>
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);


	/// <summary>
	/// �e�̐����ʒu���v�Z����֐�
	/// </summary>
	/// <param name="lightPos">�����̈ʒu</param>
	/// <param name="objPos">�I�u�W�F�N�g�̈ʒu</param>
	/// <returns>�e�̈ʒu</returns>
	DirectX::XMFLOAT3 GenerateShadowPos(DirectX::XMFLOAT3 lightPos);

	//����Q�[�����[�v�ŌĂяo����Ă�
	void Update(DirectX::XMFLOAT3 lightPos);
	void Update(void);


	//�I�u�W�F�N�g��`�悷��
	void Draw(void);

	~GameObject();



};

