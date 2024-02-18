#include "ResultAnimation.h"
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

	//�e�N�X�`���ǂݍ��݁E���f���쐬
	clear1->CreateModel(g_Assets->resultComic1_1_1, 485, 319, 1, 1);
	clear2->CreateModel(g_Assets->resultComic1_1_2, 483, 316, 1, 1);
	clear3->CreateModel(g_Assets->resultComic1_1_3, 538 / 1.1, 692 / 1.05, 1, 1);

	// �摜�P�`�R�̈ړ��O�̏����ʒu
	clear1->m_pos = { -3.3f,6.6f,0.3f };
	clear2->m_pos = { -11.3f,-2.1f,0.3f };
	clear3->m_pos = { 11.1f,0.0f,0.3f };

	// �摜�P�`�R�̈ړ���̈ʒu
	//clear1_1_1->m_pos = { -3.3f,2.1f,0.3f };
	//clear1_1_2->m_pos = { -3.3f,-2.1f,0.3f };
	//clear1_1_3->m_pos = { 3.1f,0.0f,0.3f };
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
				clear1->m_pos = { -3.3f,6.6f,0.3f };
				clear2->m_pos = { -11.3f,-2.1f,0.3f };
				clear3->m_pos = { 11.1f,0.0f,0.3f };

				// �X�e�[�W����x�N���A��������ɂ���
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetCompleted(true);
				SceneManager::Get()->SetScene(RESULT);

			}
		}

		clear1->Update();
		clear2->Update();
		clear3->Update();
	}
}

void ResultAnimation::Draw()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		clear1->Draw();
		clear2->Draw();
		clear3->Draw();
	}
}

bool ResultAnimation::Move()
{
	// �摜�P�`�R�����ԂɈړ�����悤�ɂ�����
	// �摜�R���ォ�牺�ɍ~��Ă���
	clear3->m_pos.x -= 0.1f;


	if (clear3->m_pos.x < 3.1f)
	{
		// �摜�R���w��̈ʒu�Ɏ~�߂�
		clear3->m_pos.x = 3.1f;

		// �摜1��������E�Ɉړ�������
		clear1->m_pos.y -= 0.1f;

		if (clear1->m_pos.y < 2.1f)
		{
			// �摜�P���w��̈ʒu�Ɏ~�߂�
			clear1->m_pos.y = 2.1f;

			// �摜�Q��������E�Ɉړ�������
			clear2->m_pos.x += 0.15f;

			if (clear2->m_pos.x > -3.3f)
			{
				// �摜�Q���w��̈ʒu�Ɏ~�߂�
				clear2->m_pos.x = -3.3f;

				// �摜�̈ړ�������
				return true;
			}

		}
	}

	// �摜�̈ړ����r��
	return false;
}
