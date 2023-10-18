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

	//�c�t���[�����Ԗ�
	int m_AnimePattern = 0;

	//���t���[���̉��Ԗڂ���X�^�[�g
	int m_StartFrame = 0;

	//���t���[���̉��Ԗڂ܂ŏI���
	int m_EndFrame = 0;

	//�e�N�X�`���̏c������
	DirectX::XMINT2 m_split = { 1,1 };

	// �A�j���[�V�����̃J�E���^�[
	float m_AnimeCounter = 0.0f;

	//�Đ����x
	float m_AnimeSpeed = 0.0f;

public:

	//���ݍĐ�������\���ϐ�
	bool isPlaying = true;


public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="XMINT2"></param>
	Animation(XMINT2 _split);

	/// <summary>
	/// UV���W�̍X�V���s���֐�
	/// </summary>
	/// <param name="_frameX">�����Ԗ� aniTab�̒l����</param>
	/// <param name="_frameY">animePattern �c�t���[�����Ԗ�</param>
	virtual void Update(int _frameX,int _frameY);

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

