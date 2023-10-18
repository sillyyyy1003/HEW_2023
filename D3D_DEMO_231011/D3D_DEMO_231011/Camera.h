#pragma once
#include "Direct3D/Direct3D.h"


class Camera
{
private:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	//�J�����p�̍s��
	DirectX::XMMATRIX m_MatrixView;
	//�J�����̈ʒu
	XMFLOAT3 m_CameraPos = XMFLOAT3(0.0f, 0.0f, -2.0f);
	//�����_
	XMFLOAT3 m_FocusPos = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//�J�����̏����
	XMFLOAT3 m_UpDir = XMFLOAT3(0.0f, 1.0f, 0.0f);

private:
	
	//�R���X�g���N�^
	Camera() = default;

	//�B��̃C���X�^���X���`
	static Camera* m_camera;


public:
	
	
	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//
	
	/// <summary>
	/// View�ϊ��s��̍쐬���J�����p�̍s��
	/// </summary>
	/// <returns>�쐬���J�����p�s���Ԃ��֐�</returns>
	DirectX::XMMATRIX GetMatrixView(void);
	
	/// <summary>
	/// �B��̃C���X�^���X��Ԃ��֐�
	/// </summary>
	/// <returns>m_camera->WorldCamera</returns>
	Camera* GetCamera(void);

	virtual void Update();

	/// <summary>
	/// �J�����ʒu�ύX���s���֐�
	/// </summary>
	void SetCameraPos(XMFLOAT3 _cameraPos);
	//�J�����ʒu��Ԃ��֐�
	DirectX::XMFLOAT3 GetCameraPos(void);


	/// <summary>
	/// �J�����ʒu�ύX���s���֐�
	/// </summary>
	void SetFocusPos(XMFLOAT3 _focusPos);
	//�����_�ʒu��Ԃ��֐�
	DirectX::XMFLOAT3 GetFocusPos(void);
	
	/// <summary>
	/// �J�����̏�����ύX���s���֐�
	/// </summary>
	void SetUpDir(XMFLOAT3 _Updir);
	//�J�����̏������Ԃ��֐�
	DirectX::XMFLOAT3 GetUpDir(void);

};

