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

	//ƒeƒNƒXƒ`ƒƒ“Ç‚Ýž‚ÝEƒ‚ƒfƒ‹ì¬
	clear1->CreateModel(g_Assets->resultComic1_1_1, 485, 319, 1, 1);
	clear2->CreateModel(g_Assets->resultComic1_1_2, 483, 316, 1, 1);
	clear3->CreateModel(g_Assets->resultComic1_1_3, 538 / 1.1, 692 / 1.05, 1, 1);

	// ‰æ‘œ‚P`‚R‚ÌˆÚ“®‘O‚Ì‰ŠúˆÊ’u
	clear1->m_pos = { -3.3f,6.6f,0.3f };
	clear2->m_pos = { -11.3f,-2.1f,0.3f };
	clear3->m_pos = { 11.1f,0.0f,0.3f };

	// ‰æ‘œ‚P`‚R‚ÌˆÚ“®Œã‚ÌˆÊ’u
	//clear1_1_1->m_pos = { -3.3f,2.1f,0.3f };
	//clear1_1_2->m_pos = { -3.3f,-2.1f,0.3f };
	//clear1_1_3->m_pos = { 3.1f,0.0f,0.3f };
}

void ResultAnimation::Update()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetClear())
	{
		// ‰æ‘œ‚ÌˆÚ“®‚ªŠ®—¹‚µ‚½‚©Aˆê“xƒNƒŠƒA‚µ‚½ƒXƒe[ƒW‚©‚Å”»’è
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			// ƒXƒy[ƒX‚ð‰Ÿ‚·‚ÆƒŠƒUƒ‹ƒg‰æ–Ê‚É‘JˆÚ‚·‚é
			if (Input::Get()->GetKeyTrigger(DIK_SPACE))
			{
				// ‰æ‘œ‚P‚©‚ç‚R‚ÌˆÊ’u‚ð‰Šú’li‰æ–ÊŠOj‚É–ß‚·
				clear1->m_pos = { -3.3f,6.6f,0.3f };
				clear2->m_pos = { -11.3f,-2.1f,0.3f };
				clear3->m_pos = { 11.1f,0.0f,0.3f };

				// ƒXƒe[ƒW‚ðˆê“xƒNƒŠƒA‚µ‚½”»’è‚É‚·‚é
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
	// ‰æ‘œ‚P`‚R‚ð‡”Ô‚ÉˆÚ“®‚·‚é‚æ‚¤‚É‚³‚¹‚é
	// ‰æ‘œ‚R‚ªã‚©‚ç‰º‚É~‚è‚Ä‚­‚é
	clear3->m_pos.x -= 0.1f;


	if (clear3->m_pos.x < 3.1f)
	{
		// ‰æ‘œ‚R‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
		clear3->m_pos.x = 3.1f;

		// ‰æ‘œ1‚ð¶‚©‚ç‰E‚ÉˆÚ“®‚³‚¹‚é
		clear1->m_pos.y -= 0.1f;

		if (clear1->m_pos.y < 2.1f)
		{
			// ‰æ‘œ‚P‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
			clear1->m_pos.y = 2.1f;

			// ‰æ‘œ‚Q‚ð¶‚©‚ç‰E‚ÉˆÚ“®‚³‚¹‚é
			clear2->m_pos.x += 0.15f;

			if (clear2->m_pos.x > -3.3f)
			{
				// ‰æ‘œ‚Q‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
				clear2->m_pos.x = -3.3f;

				// ‰æ‘œ‚ÌˆÚ“®‚ªŠ®—¹
				return true;
			}

		}
	}

	// ‰æ‘œ‚ÌˆÚ“®‚ª“r’†
	return false;
}
