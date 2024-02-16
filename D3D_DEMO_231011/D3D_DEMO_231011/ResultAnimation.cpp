#include "ResultAnimation.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"
#include "Game.h"
extern Assets* g_Assets;

ResultAnimation::ResultAnimation()
{
	clear1_1_1 = new CanvasUI();
	clear1_1_2 = new CanvasUI();
	clear1_1_3 = new CanvasUI();
}

ResultAnimation::~ResultAnimation()
{
	delete clear1_1_1;
	delete clear1_1_2;
	delete clear1_1_3;
}

void ResultAnimation::Init()
{
	//ƒeƒNƒXƒ`ƒƒ“Ç‚Ýž‚ÝEƒ‚ƒfƒ‹ì¬
	clear1_1_1->CreateModel(g_Assets->clear1_1_1, 485, 319, 1, 1);
	clear1_1_2->CreateModel(g_Assets->clear1_1_2, 483, 316, 1, 1);
	clear1_1_3->CreateModel(g_Assets->clear1_1_3, 538 / 1.1, 692/1.05, 1, 1);

	// ‰æ‘œ‚P`‚R‚ÌˆÚ“®‘O‚Ì‰ŠúˆÊ’u
	clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
	clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
	clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

	// ‰æ‘œ‚P`‚R‚ÌˆÚ“®Œã‚ÌˆÊ’u
	//clear1_1_1->m_pos = { -3.3f,2.1f,0.3f };
	//clear1_1_2->m_pos = { -3.3f,-2.1f,0.3f };
	//clear1_1_3->m_pos = { 3.1f,0.0f,0.3f };
}

void ResultAnimation::Update()
{

		// ‰æ‘œ‚ÌˆÚ“®‚ªŠ®—¹‚µ‚½‚©Aˆê“xƒNƒŠƒA‚µ‚½ƒXƒe[ƒW‚©‚Å”»’è
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			// ƒXƒy[ƒX‚ð‰Ÿ‚·‚ÆƒŠƒUƒ‹ƒg‰æ–Ê‚É‘JˆÚ‚·‚é
			if (Input::Get()->GetKeyTrigger(DIK_SPACE))
			{
				// ‰æ‘œ‚P‚©‚ç‚R‚ÌˆÊ’u‚ð‰Šú’li‰æ–ÊŠOj‚É–ß‚·
				clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
				clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
				clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

				// ƒXƒe[ƒW‚ðˆê“xƒNƒŠƒA‚µ‚½”»’è‚É‚·‚é
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetCompleted(true);
				//‰‰oI—¹ŒãŽŸ‚Ì’iŠK‚É“ü‚é
				Game::Get()->SetResultAnime(false);

			}
		}

		clear1_1_1->Update();
		clear1_1_2->Update();
		clear1_1_3->Update();
	
}

void ResultAnimation::Draw()
{
	clear1_1_1->Draw();
	clear1_1_2->Draw();
	clear1_1_3->Draw();

}

bool ResultAnimation::Move()
{
	// ‰æ‘œ‚P`‚R‚ð‡”Ô‚ÉˆÚ“®‚·‚é‚æ‚¤‚É‚³‚¹‚é
	// ‰æ‘œ‚P‚ªã‚©‚ç‰º‚É~‚è‚Ä‚­‚é
	clear1_1_3->m_pos.x -= 0.1f;


	if (clear1_1_3->m_pos.x < 3.1f)
	{
		// ‰æ‘œ‚R‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
		clear1_1_3->m_pos.x = 3.1f;

		// ‰æ‘œ1‚ð¶‚©‚ç‰E‚ÉˆÚ“®‚³‚¹‚é
		clear1_1_1->m_pos.y -= 0.1f;

		if (clear1_1_1->m_pos.y < 2.1f)
		{
			// ‰æ‘œ‚P‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
			clear1_1_1->m_pos.y = 2.1f;

			// ‰æ‘œ‚Q‚ð¶‚©‚ç‰E‚ÉˆÚ“®‚³‚¹‚é
			clear1_1_2->m_pos.x += 0.15f;

			if (clear1_1_2->m_pos.x > -3.3f)
			{
				// ‰æ‘œ‚Q‚ðŽw’è‚ÌˆÊ’u‚ÉŽ~‚ß‚é
				clear1_1_2->m_pos.x = -3.3f;

				// ‰æ‘œ‚ÌˆÚ“®‚ªŠ®—¹
				return true;
			}

		}
	}

	// ‰æ‘œ‚ÌˆÚ“®‚ª“r’†
	return false;
}
