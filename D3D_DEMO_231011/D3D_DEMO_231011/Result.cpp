#include "Result.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "StaticObject.h"
#include "DInput.h"
#include "SceneManager.h"
#include "ResultProcess.h"
#include "Game.h"
#include "xa2.h"

#define SIZECHANGE 0.95f

extern Assets* g_Assets;

Result::Result()
{
	processor = new ResultProcess();

	//30�ȉ��܂Ő��T
	//31�ȏ�40�܂Ő��S
	//41�ȏ�50�܂Ő��R
	//51�ȏ�60�܂Ő��Q
	//61�ȏォ�琯�P
	SetStarNum({ 30,40,50,60 });
}

Result::~Result()
{
	delete processor;
	delete uiResult;
	delete resultBg;
	delete Button_again;
	delete Button_next;
	delete Result_score;
	delete Button_return;
	delete Result_stepcount;
	for (int i = 0; i < 5; i++)
	{
		delete star[i];
		delete starShadow[i];
	}
}
void Result::Init()
{
	//StepNum�̏�����
	processor->Init(1.8f * SIZECHANGE, 0.0f, 1.0 * SIZECHANGE, 10);

	uiResult = new CanvasUI();
	resultBg = new CanvasUI();
	Result_score = new CanvasUI();
	Result_stepcount = new CanvasUI();
	Button_again = new CanvasUI();
	Button_next = new CanvasUI();
	Button_return = new CanvasUI();

	//�e�N�X�`���ǂݍ��݁E���f���쐬
	uiResult->CreateModel(g_Assets->result, 430* SIZECHANGE, 104 * SIZECHANGE, 1, 1);
	resultBg->CreateModel(g_Assets->resultBg, 1029 * SIZECHANGE, 713 * SIZECHANGE, 1, 1);
	Result_score->CreateModel(g_Assets->Result_score, 139 * SIZECHANGE, 66 * SIZECHANGE, 1, 1);
	Result_stepcount->CreateModel(g_Assets->Result_stepcount, 375 * SIZECHANGE, 72 * SIZECHANGE, 1, 1);
	Button_again->CreateModel(g_Assets->Button_again, 299 * SIZECHANGE, 96 * SIZECHANGE, 1, 2);
	Button_next->CreateModel(g_Assets->Button_next, 316 * SIZECHANGE, 107 * SIZECHANGE, 1, 2);
	Button_return->CreateModel(g_Assets->Button_return, 311 * SIZECHANGE, 104 * SIZECHANGE, 1, 2);

	//���W
	resultBg->m_pos = { 0.0f,0.0f,0.4f };
	uiResult->m_pos = { 0.0f,3.1f* SIZECHANGE,0.3f };
	Result_score->m_pos = { -4.0f * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
	Result_stepcount->m_pos = { -2.5f * SIZECHANGE,0.0f,0.3f };
	Button_again->m_pos = { 2.0f * SIZECHANGE,-1.5f * SIZECHANGE,0.3f };
	Button_next->m_pos = { -2.3f * SIZECHANGE,-1.5f * SIZECHANGE,0.3f };
	Button_return->m_pos = { 0.0f,-3.0f* SIZECHANGE,0.3f };

	//�A�j���[�V����
	Button_again->m_anime->SetAnimePattern(0);
	Button_next->m_anime->SetAnimePattern(0);
	Button_return->m_anime->SetAnimePattern(0);

	for (int i = 0; i < 5; i++)
	{
		star[i] = new CanvasUI();
		starShadow[i] = new CanvasUI();

		//�e�N�X�`���ǂݍ��݁E���f���쐬
		star[i]->CreateModel(g_Assets->star, 88 * SIZECHANGE, 85 * SIZECHANGE, 1, 1);
		starShadow[i]->CreateModel(g_Assets->starShadow, 88 * SIZECHANGE, 85 * SIZECHANGE, 1, 1);

		//���W
		star[i]->m_pos = { -2.1f * SIZECHANGE + 1.5f*i * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
		starShadow[i]->m_pos = { -2.1f * SIZECHANGE + 1.5f * i * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
	}

	//�w�i


	buttonnum = 0;
}

void Result::Update()
{
	//�X�^�[�̏���
	//�����P�F�X�e�[�W�I�����̃X�e�b�v���@�����Q�F�X�e�b�v���ɂ���Đ��̐���ύX���邽�߂̐���
	StarEvent(ResultScore(SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep(), Starnum));
	//�L�[�̏���
	DoResultKeyEvent();
	//�{�^���̏���
	ButtonEvent();

	uiResult->Update();
	resultBg->Update();
	Result_score->Update();
	Result_stepcount->Update();
	Button_again->Update();
	Button_next->Update();
	Button_return->Update();
	for (int i = 0; i < AllStar; i++)
	{
		star[i]->Update();
	}
	for (int i = 4; i+1 > AllStar; i--)
	{
		starShadow[i]->Update();
	}
}

void Result::Draw()
{
	//�w�i
	resultBg->Draw();
	uiResult->Draw();
	Result_score->Draw();
	Result_stepcount->Draw();
	Button_again->Draw();
	Button_next->Draw();
	Button_return->Draw();
	for (int i = 0; i < AllStar; i++)
	{
		star[i]->Draw();
	}
	for (int i = 4; i + 1 > AllStar; i--)
	{
		starShadow[i]->Draw();
	}

	//�X�e�[�W�I�����̃X�e�b�v����\��
	
	processor->PrintDebugLogLeft(SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep());//
}

void Result::DoResultKeyEvent()
{
	// �{�^��
	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW))
	{
		buttonnum = RETURN;
	}
	if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW))
	{
		buttonnum = AGAIN;
	}
	if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW))
	{
		buttonnum = NEXT;
	}
}

void Result::ButtonEvent()
{
	switch (buttonnum)
	{
	case AGAIN://������x�����X�e�[�W��
		Button_again->m_anime->SetAnimePattern(1);
		Button_next->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);

		//�X�y�[�X���������Ƃ��ɂ�����x�����X�e�[�W�ɑJ�ڂ���
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			//�����X�e�[�W������A���ڏ�������������������炢��
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
			//Game::Get()->InitStage();
			buttonnum = NEXT;
		}
		break;
	case RETURN://�^�C�g����
		Button_return->m_anime->SetAnimePattern(1);
		Button_again->m_anime->SetAnimePattern(0);
		Button_next->m_anime->SetAnimePattern(0);

		//�X�y�[�X���������Ƃ��Ƀ^�C�g���ɑJ�ڂ���
		if (Input::Get()->GetKeyPress(DIK_SPACE))
		{
			SceneManager::Get()->ChangeScene(SCENENAME::STAGESELECT);
			buttonnum = NEXT;
			XA_Play(BGM_SelectStage);// �Z���N�g��ʂɖ߂�������BGM�Đ�
		}
		break;
	case NEXT://���̃X�e�[�W��
		Button_next->m_anime->SetAnimePattern(1);
		Button_again->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);

		//�X�y�[�X���������Ƃ��Ɏ��̃X�e�[�W�ɑJ�ڂ���
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			//�X�e�[�W�ɖ߂�
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
	

			//���������s��
			//Game::Get()->InitStage();
			
			buttonnum = NEXT;
		}
		break;
	default:
		Button_again->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);
		Button_next->m_anime->SetAnimePattern(1);
		break;
	}
}

void Result::StarEvent(int StarScore)
{
	switch (StarScore)
	{
	case STARONE://���P
		AllStar = STARONE;
		break;
	case STARTWO://���Q
		AllStar = STARTWO;
		break;
	case STARTHREE://���R
		AllStar = STARTHREE;
		break;
	case STARFOUR://���S
		AllStar = STARFOUR;
		break;
	case STARFIVE://���T
		AllStar = STARFIVE;
		break;
	default://�Œᐯ1
		AllStar = STARONE;
		break;
	}
}

int Result::ResultScore(int resultStep, std::vector<int> StarNum)
{
	//���T�̔���
	if (resultStep <= StarNum[0])
	{
		return STARFIVE;//���T
	}
	//���S�̔���
	else if (resultStep <= StarNum[1])
	{
		return STARFOUR;//���S
	}
	//���R�̔���
	else if (resultStep <= StarNum[2])
	{
		return STARTHREE;//���R
	}
	//���Q�̔���
	else if (resultStep <= StarNum[3])
	{
		return STARTWO;//���Q
	}
	//���P�̔���
	else
	{
		return STARONE;//���P
	}

	return 0;
}