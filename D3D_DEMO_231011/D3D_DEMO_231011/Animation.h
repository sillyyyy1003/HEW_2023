#pragma once
#include "Direct3D/Direct3D.h"



class Animation
{
protected:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	// UV�A�j���[�V�����p�I�t�Z�b�g
	DirectX::XMFLOAT2 m_offsetUV = { 0.0f,0.0f };

	//���E�c�t���[�����Ԗ�
	int m_frameX = 0;	//�����Ԗ�
	int m_frameY = 0;	//�c���Ԗځ��A�j���p�^�[��

	//�e�N�X�`���̏c������
	DirectX::XMINT2 m_split = { 1,1 };

	//���t���[���̉��Ԗڂ���X�^�[�g
	int m_StartFrame = 0;

	//���t���[���̉��Ԗڂ܂ŏI���
	int m_endFrame = 0;

	// �A�j���[�V�����̃J�E���^�[
	float m_animeCounter = 0.0f;

	//�Đ����x
	float m_animeSpeed = 0.0f;

public:

	//���ݍĐ�������\���ϐ�
	bool isPlaying = true;


public:
	/// <summary>
	/// �������@�c��������ݒ肷��
	/// </summary>
	/// <param name="splitX">��������</param>
	/// <param name="splitY">�c������</param>
	Animation(int splitX,int splitY);

	/// <summary>
	/// �c�������̏����ݒ�
	/// </summary>
	/// <param name="_split">�c������ SPRITE�ƈ�v����</param>
	void SetSplit(XMINT2 _split);


	DirectX::XMINT2 GetSplit(void);
		
	/// <summary>
	/// UV���W�̍X�V���s���֐�
	/// </summary>
	/// NOTE:�p���N���X�ŃA�j���e�[�u���̐ݒ�Əc���̃A�j���X�V���s��
	virtual void Update(void);

	/// <summary>
	/// �Đ����x��ݒ肷��֐�
	/// </summary>
	/// <param name="_speed">�Đ����x</param>
	void SetAnimeSpeed(float _speed);

	/// <summary>
	/// �A�j���[�V�����p�^�[����ݒ肷��֐�
	/// </summary>
	/// <param name="_animePattern">�c�t���[�����Ԗ� �A�j���[�V�����̃p�^�[��</param>
	void SetAnimePattern(int _animePattern);

	/// <summary>
	/// UV���W��Ԃ��֐�
	/// </summary>
	/// <returns>�X�V���ꂽUV���W</returns>
	DirectX::XMFLOAT2 GetUVOffset(void);

};

