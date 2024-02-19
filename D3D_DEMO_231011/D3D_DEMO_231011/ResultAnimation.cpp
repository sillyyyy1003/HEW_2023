#include "ResultAnimation.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"
#include "Game.h"

extern Assets* g_Assets;

//�摜���~�܂��Ă��玟�̉摜��������܂ł̑ҋ@����
#define WAITLIMITE 90
//�摜�̉�]��(��ʒu�ɂ��܂łɉ���]�����邩�j//�Q��]
#define ROTATETIME 2
//�摜�̓������x
#define MOVESPEED 1.4

ResultAnimation::ResultAnimation()
{

}

ResultAnimation::~ResultAnimation()
{
	delete clear1;
	delete clear2;
	delete clear3;
}

void ResultAnimation::SetTexture(ID3D11ShaderResourceView* texture_clear1, ID3D11ShaderResourceView* texture_clear2, ID3D11ShaderResourceView* texture_clear3)
{
	clear1->SetTexture(texture_clear1);
	clear2->SetTexture(texture_clear2);
	clear3->SetTexture(texture_clear3);
}

void ResultAnimation::Init()
{
	clear1 = new CanvasUI();
	clear2 = new CanvasUI();
	clear3 = new CanvasUI();

	skip = new CanvasUI();

	//�e�N�X�`���ǂݍ��݁E���f���쐬
	clear1->CreateModel(g_Assets->resultComic1_1_1, 650, 476, 1, 1);
	clear2->CreateModel(g_Assets->resultComic1_1_2, 707, 503, 1, 1);
	clear3->CreateModel(g_Assets->resultComic1_1_3, 502, 642, 1, 1);

	skip->CreateModel(g_Assets->Button_skip, 892/4, 265/4, 1, 1);

	// �摜�P�`�R�̈ړ��O�̏����ʒu
	clear1->m_pos = { 12.0f,7.6f,0.4f };   //�E��@z���W�@�^�� 
	clear2->m_pos = { -12.1f,7.6f,0.3f };  //����@z���W�@��O
	clear3->m_pos = { 0.0f,-8.6f,0.5f };   //���@�@z���W�@��

	skip->m_pos = { 6.53f,3.97f,0.3f }; //�X�L�b�v�{�^��
}

void ResultAnimation::Update()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetClear())
	{
		// �摜�̈ړ��������������A��x�N���A�����X�e�[�W���Ŕ���
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			// �X�y�[�X�������ƃ��U���g��ʂɑJ�ڂ���
			if (Input::Get()->GetKeyTrigger(DIK_SPACE))
			{
				// �摜�P����R�̈ʒu�������l�i��ʊO�j�ɖ߂�
				clear1->m_pos = { 12.0f,7.6f,0.4f };   //�E��@z���W�@�^�� 
				clear2->m_pos = { -12.1f,7.6f,0.3f };  //����@z���W�@��O
				clear3->m_pos = { 0.0f,-8.6f,0.5f };   //���@�@z���W�@��
				clear1->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g
				clear2->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g
				clear3->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g
				waitcount2 = 0; //�J�E���g���Z�b�g
				waitcount = 0; //�J�E���g���Z�b�g

				// �X�e�[�W����x�N���A��������ɂ���
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetCompleted(true);
				Game::Get()->SetResultAnime(false);
			}
		}

		clear1->Update();
		clear2->Update();
		clear3->Update();
		skip->Update();
	}
}

void ResultAnimation::Draw()
{

	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		// ��x�N���A���Ă����ꍇ�E��ɃX�L�b�v�ƕ\������
		if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			skip->Draw();
		}

		clear3->Draw();
		clear1->Draw();
		clear2->Draw();
	}

}

bool ResultAnimation::Move()
{
	// �摜�P�`�R�����ԂɈړ�����悤�ɂ�����
	
	// �摜3��������^�񒆂Ɉړ�������
	// clear3���������������Ⴄ���߂ɒ�������
	clear3->m_pos.y += 0.1f * (MOVESPEED*1.1f);

	// �摜����ʒu�ɂ��܂łɈ������悤�Ɍv�Z����iROTATETIME�ŉ�]���𒲐��j
	clear3->m_rotation.z += 360/(86/ (MOVESPEED * 1.1f) / ROTATETIME); // ��]���x�i�x�j

	if (clear3->m_pos.y > 0.0f)
	{
		// �摜3���w��̈ʒu�Ɏ~�߂�
		clear3->m_pos.y = 0.0f;
		clear3->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g

		// �J�E���g�J�n
		waitcount++;

		if (waitcount > WAITLIMITE)
		{
			// �摜1���E�ォ��^�񒆂ɍ~��Ă���
			clear1->m_pos.x -= 0.157f * MOVESPEED;
			clear1->m_pos.y -= 0.1f * MOVESPEED;

			// �摜��Z���𒆐S�ɉ�]������
			clear1->m_rotation.z += 360 / (76 / MOVESPEED / ROTATETIME); // ��]���x�i�x�j

			if (clear1->m_pos.y < 0.0f)
			{
				// �摜1���w��̈ʒu�Ɏ~�߂�
				clear1->m_pos.x = 0.0f;
				clear1->m_pos.y = 0.0f;
				clear1->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g

				// �J�E���g�J�n
				waitcount2++;

				if (waitcount2 > WAITLIMITE)
				{
					// �摜2�����ォ��^�񒆂Ɉړ�������
					clear2->m_pos.x += 0.157f * MOVESPEED;
					clear2->m_pos.y -= 0.1f * MOVESPEED;
					clear2->m_rotation.z += 360 / (76 / MOVESPEED / ROTATETIME); // ��]���x�i�x�j

					if (clear2->m_pos.y < 0.0f)
					{
						// �摜2���w��̈ʒu�Ɏ~�߂�
						clear2->m_pos.x = 0.0f;
						clear2->m_pos.y = 0.0f;
						clear2->m_rotation.z = 0.0f; // ��]�p�x�����Z�b�g

						// �摜�̈ړ�������
						return true;
					}
				}
			}
		}
	}


	// �摜�̈ړ����r��
	return false;
}
