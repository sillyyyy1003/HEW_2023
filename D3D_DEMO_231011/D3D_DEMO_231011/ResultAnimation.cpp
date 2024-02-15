#include "ResultAnimation.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"

extern Assets* g_Assets;
extern ResultAnimation* g_ResultAnimation = new ResultAnimation();

ResultAnimation::ResultAnimation()
{

}

ResultAnimation::~ResultAnimation()
{
	delete clear1_1_1;
	delete clear1_1_2;
	delete clear1_1_3;
}

void ResultAnimation::Init()
{
	clear1_1_1 = new CanvasUI();
	clear1_1_2 = new CanvasUI();
	clear1_1_3 = new CanvasUI();

	//�e�N�X�`���ǂݍ��݁E���f���쐬
	clear1_1_1->CreateModel(g_Assets->clear1_1_1, 485, 319, 1, 1);
	clear1_1_2->CreateModel(g_Assets->clear1_1_2, 483, 316, 1, 1);
	clear1_1_3->CreateModel(g_Assets->clear1_1_3, 538 / 1.1, 692/1.05, 1, 1);

	// �摜�P�`�R�̈ړ��O�̏����ʒu
	clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
	clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
	clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

	// �摜�P�`�R�̈ړ���̈ʒu
	//clear1_1_1->m_pos = { -3.3f,2.1f,0.3f };
	//clear1_1_2->m_pos = { -3.3f,-2.1f,0.3f };
	//clear1_1_3->m_pos = { 3.1f,0.0f,0.3f };
}

void ResultAnimation::Update()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		// �摜�̈ړ��������������A��x�N���A�����X�e�[�W���Ŕ���
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetCompleted())
		{
			// �X�y�[�X�������ƃ��U���g��ʂɑJ�ڂ���
			if (Input::Get()->GetKeyPress(DIK_SPACE))
			{
				// �摜�P����R�̈ʒu�������l�i��ʊO�j�ɖ߂�
				clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
				clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
				clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

				// �X�e�[�W����x�N���A��������ɂ���
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetCompleted(true);

				// ���U���g�ɑJ�ڂ���
				SceneManager::Get()->SetScene(SCENENAME::RESULT);
			}
		}

		clear1_1_1->Update();
		clear1_1_2->Update();
		clear1_1_3->Update();
	}
}

void ResultAnimation::Draw()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		clear1_1_1->Draw();
		clear1_1_2->Draw();
		clear1_1_3->Draw();
	}
}

bool ResultAnimation::Move()
{
	// �摜�P�`�R�����ԂɈړ�����悤�ɂ�����
	// �摜�P���ォ�牺�ɍ~��Ă���
	clear1_1_1->m_pos.y -= 0.1f;

	if (clear1_1_1->m_pos.y < 2.1f)
	{
		// �摜�P���w��̈ʒu�Ɏ~�߂�
		clear1_1_1->m_pos.y = 2.1f;

		// �摜�Q��������E�Ɉړ�������
		clear1_1_2->m_pos.x += 0.1f;

		if (clear1_1_2->m_pos.x > -3.3f)
		{
			// �摜�Q���w��̈ʒu�Ɏ~�߂�
			clear1_1_2->m_pos.x = -3.3f;

			// �摜�R���E���獶�ֈړ�������
			clear1_1_3->m_pos.x -= 0.1f;

			if (clear1_1_3->m_pos.x < 3.1f)
			{
				// �摜�R���w��̈ʒu�Ɏ~�߂�
				clear1_1_3->m_pos.x = 3.1f;

				// �摜�̈ړ�������
				return true;
			}

		}
	}

	// �摜�̈ړ����r��
	return false;
}
