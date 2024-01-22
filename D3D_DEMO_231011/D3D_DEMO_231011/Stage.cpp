#include "Stage.h"

void Stage::Init(void)
{
	//ステージをクリアしてない状態をセットする
	isClear = false;

	//ご褒美の金額をリセット
	m_rewardGold=0;

	//移動数をリセットする
	m_moveStep = 0;

}

void Stage::Update(void)
{
	
}

void Stage::StepCount(void)
{
	m_moveStep++;
}
