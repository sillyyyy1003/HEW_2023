#include "GameObject.h"
#include "ShadowObject.h"
#include "SphereCollider.h"
#include "StaticAnimation.h"
#include "BoxCollider.h"
#include "DInput.h"
#include "RailManager.h"
#include "SceneManager.h"
#include <math.h>
#include "DInput.h"

//#define MOVEDISTANCEZ 2.5
#define MOVEDISTANCEZ 1
//#define MOVEDISTANCEX 4.4
#define MOVEDISTANCEX 1
#define BOXMEDIUM 1.5f
#define BOXLARGE 2.1f
#define SPHEREMEDIUM 1.8f
#define SPHERELARGE 2.5f
#define POLYGONMEDIUM 1.5f
#define POLYGONLARGE 2.1f

extern Camera* g_WorldCamera;

#define BOXMEDIUM 1.5f
#define BOXLARGE 2.1f

#define SPHEREMEDIUM 1.8f
#define SPHERELARGE 2.5f

#define POLYGONMEDIUM 1.5f
#define POLYGONLARGE 2.1f

void GameObject::DoKeyInput(void)
{
	m_inputCount++;

	if ((Input::Get()->GetKeyPress(DIK_DOWNARROW) || Input::Get()->GetKeyPress(DIK_UPARROW) || Input::Get()->GetKeyPress(DIK_RIGHTARROW) || Input::Get()->GetKeyPress(DIK_LEFTARROW))) {
		if (!isInputCount) {
			//時間測定開始
			isInputCount = true;
			m_lastPressTime = m_inputCount;
		}

	}
	//カウト開始
	if (isInputCount) {
		if (m_inputCount <= m_lastPressTime + 5) {
			//处理垂直方向输入
			if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW) && !Input::Get()->GetKeyTrigger(DIK_UPARROW))
			{
				m_nowInput.verInput = INPUT_DOWN;
			}
			if (Input::Get()->GetKeyTrigger(DIK_UPARROW) && !Input::Get()->GetKeyTrigger(DIK_DOWNARROW))
			{
				m_nowInput.verInput = INPUT_UP;
			}

			// 处理水平方向输入
			if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW) && !Input::Get()->GetKeyTrigger(DIK_RIGHTARROW))
			{
				m_nowInput.horInput = INPUT_LEFT;
			}
			if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW) && !Input::Get()->GetKeyTrigger(DIK_LEFTARROW))
			{
				m_nowInput.horInput = INPUT_RIGHT;
			}

		}
		else {
			isGetInput = true;
			isInputCount = false;
		}
	}
	else {
		//方向を初期化にする
		m_nowInput.horInput = INPUT_NONE;
		m_nowInput.verInput = INPUT_NONE;
	}

}

GameObject::GameObject()
{
	//オブジェクトの初期化
	m_obj = new Object();

	//オブジェクトの原点を設定する
	m_obj->m_sprite->m_spriteType = Sprite::OBJECT;

	//影の初期化
	m_shadow = new ShadowObject();
}

void GameObject::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateObject(texture, _width, _height, splitX, splitY);
}

void GameObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_shadow->CreateObject(texture, _width, _height, splitX, splitY);
}

void GameObject::InitAnimation(void)
{
	m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);
	m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);
}

void GameObject::GenerateShadowPos(float moveSpeed, float posX)
{
	/*
	//単位ベクトル化する
	//オブジェクトの位置取得
	const XMFLOAT3 objPos = m_obj->m_sprite->m_pos; 

	//ベクトル計算用の型に入れる
	XMVECTOR objVector = XMLoadFloat3(&objPos);
	XMVECTOR lightVector = XMLoadFloat3(&m_lightPos);
	//光からオブジェクトのベクトルを計算する
	XMVECTOR directionVector = XMVectorSubtract(objVector, lightVector);


	// 壁と地面の角度が90度(假设墙壁垂直于地面，沿Z轴)
	float wallZ = m_shadow->m_sprite->m_pos.z;  // 墙壁的Z坐标

	// 距離比率を計算する(计算交点的Z值等于墙壁的Z值时的t)
	float t = (wallZ - m_lightPos.z) / XMVectorGetZ(directionVector);

	//影の位置を計算する
	XMFLOAT3 shadowPosition;
	shadowPosition.x = m_lightPos.x + t * XMVectorGetX(directionVector);
	shadowPosition.y = m_lightPos.y + t * XMVectorGetY(directionVector);
	shadowPosition.z = wallZ;  //影のｚ軸
	*/

	//
	switch (m_moveDir)
	{
	case UPRIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case RIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case DOWNRIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case DOWNLEFT:
		m_shadow->m_sprite->m_pos.x -= moveSpeed;
		break;
	case LEFT:
		m_shadow->m_sprite->m_pos.x -= moveSpeed;
		break;
	case UPLEFT:
		m_shadow->m_sprite->m_pos.x -= moveSpeed;
		break;
	case STILL:
		switch(m_railPos.horizontalPos){
		case 0:
			m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x - posX;
			break;
		case 1:
			m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x - posX*2;
			break;
		case 2:
			m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x;
			break;
		case 3:
			m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x + posX;
			break;
		case 4:
			m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x + posX*2;
			break;
		}
		break;
	default:
		break;
	}


}


void GameObject::GenerateShadowRotate()
{
	
}

void GameObject::SetRailPos(int horPos, int verPos)
{
	m_railPos.horizontalPos = horPos;
	m_railPos.verticalPos = verPos;
}

void GameObject::Update()
{

	//入力処理
	if (isActive) {
		//八方向の入力処理
		if (m_moveDir != STILL) {
			ObjectMove();
		}
		else {
			//入力
			if (!isAutoMove) {
				DoKeyInput();

				if(isGetInput){
					switch (m_nowInput.horInput) {
						//左
					case INPUT_LEFT:
						switch (m_nowInput.verInput)
						{
						case INPUT_UP:
							if (isMoveable(UPLEFT)) { m_moveDir = UPLEFT; }
							else { ObjectVibration(); }
	
							break;
						case INPUT_DOWN:
							if (isMoveable(DOWNLEFT)) { m_moveDir = DOWNLEFT; }
							else { ObjectVibration(); }

							break;
						case INPUT_NONE:
							if (isMoveable(LEFT)) { m_moveDir = LEFT; }
							else { ObjectVibration(); }

							break;
						default:
							break;
						}
						break;
						//右
					case INPUT_RIGHT:
						switch (m_nowInput.verInput)
						{
						case INPUT_UP:
							if (isMoveable(UPRIGHT)) { m_moveDir = UPRIGHT; }
							else { ObjectVibration(); }

							break;
						case INPUT_DOWN:
							if (isMoveable(DOWNRIGHT)) { m_moveDir = DOWNRIGHT; }
							else { ObjectVibration(); }

							break;
						case INPUT_NONE:
							if (isMoveable(RIGHT)) { m_moveDir = RIGHT; }
							else { ObjectVibration(); }
							break;
						default:
							break;
						}
						break;
						//左右STILL
					case INPUT_NONE:
						switch (m_nowInput.verInput)
						{
						case INPUT_UP:
							if (isMoveable(UP)) { m_moveDir = UP; }
							else { ObjectVibration(); }
							break;
						case INPUT_DOWN:
							if (isMoveable(DOWN)) { m_moveDir = DOWN; }
							else { ObjectVibration(); }
							break;
						case INPUT_NONE:
							break;
						default:
							break;
						}
						break;
					}
					isGetInput = false;
					
				}
			}
			else{
				//今いる位置を獲得

				//次の移動方向を獲得


				//次の移動方向を判定
				//m_moveDir=
			}

		}
		//移動完成後
		int stageInfo = SceneManager::Get()->GetActiveStage();
		SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
	}
	
	//オブジェクト情報更新
	m_obj->Update();
	
	//位置を更新
	GenerateShadowPos(0.08f, 0.1);
	//GenerateShadowSize();

	//影の情報更新
	m_shadow->Update();

	//Collider情報更新
	if (m_shadowCollider) {
		UpdateShadowColliderData();
	}
	

	// オブジェクトの位置によって影の大きさを調整

	//大きさを更新
	switch (m_railPos.verticalPos)
	{
	case 0:	//back
		m_shadow->m_size = ShadowObject::SIZE::SMALL;
		break;
	case 1:
		m_shadow->m_size = ShadowObject::SIZE::MEDIUM;
		break;
	case 2:
		m_shadow->m_size = ShadowObject::SIZE::LARGE;
		break;
	}
}

bool GameObject::isMoveable(DIR dir)
{
		int point = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
		PointInfo info = RailManager::Get()->m_info[point];
		
		//移動先
		int movePos = 0;
		int moveDir = 0;
		//移動先の位置を計算
		switch (dir) {
		case UP:
			movePos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos;
			moveDir = UP;
			break;

		case UPRIGHT:
			movePos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos + 1;
			moveDir = UPRIGHT;
			break;

		case RIGHT:
			movePos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos + 1;
			moveDir = RIGHT;
			break;

		case DOWNRIGHT:
			movePos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos + 1;
			moveDir = DOWNRIGHT;
			break;

		case DOWN:
			movePos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos;
			moveDir = DOWN;
			break;

		case DOWNLEFT:
			movePos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos - 1;
			moveDir = DOWNLEFT;
			break;

		case LEFT:
			movePos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos - 1;
			moveDir = LEFT;
			break;

		case UPLEFT:
			movePos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos - 1;
			moveDir = UPLEFT;
			break;
		case STILL:
			break;
		}

		
		//There may be some bugs,So Limit the boundary
		if (movePos < 0 || movePos>14) {

			MessageBoxA(NULL, "point計算エラー！", "エラー", MB_OK | MB_ICONERROR);
			return false;
		}

		//その方向に移動できるか
		if (info.isMoveable[moveDir]) {
						
			//目標位置は空いてるか？
			if (RailManager::Get()->m_info[movePos].isVacant) {

					return true;

			}
			else {
					return false;
			}
		}
		else {
			return false;
		}
}

void GameObject::UpdateShadowColliderData(void)
{
	//dynamic_castを使って、コライダーのデータを更新する
	
	switch (m_shadowCollider->GetColliderType()) {
	case SPHERE:
	
	
		dynamic_cast<SphereCollider*>(m_shadowCollider)->m_center = m_shadow->m_sprite->m_pos;
		dynamic_cast<SphereCollider*>(m_shadowCollider)->m_radius = 1.0f;
		//dynamic_cast<SphereCollider*>(m_shadowCollider)->Update(Collider::m_center, rotation, extents);

	//更新したデータを本体のColliderに更新する
	//m_shadowCollider->Update();
	break;





	case SQUARE:
		DirectX::XMFLOAT3 center = m_shadow->m_sprite->m_pos;
		DirectX::XMFLOAT3 extents = m_shadow->m_sprite->GetExtents();
		DirectX::XMFLOAT3 rotation = m_shadow->m_sprite->m_rotation;
		//dynamic_cast<BoxCollider*>(m_shadowCollider)->Update(center, rotation, extents);

	break;

	//default:

	break;
	}




}

void GameObject::ObjectMove()
{
	DirectX::XMFLOAT3 moveSpeed = { 0,0,0 };

	switch (m_moveDir) {
	case UP:
		m_moveCount++;
		moveSpeed.z = 0.05f;
		if (m_moveCount * moveSpeed.z <= 2.5f) {

			m_obj->m_sprite->m_pos.z += moveSpeed.z;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット

			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.verticalPos -= 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
		}

		break;

	case UPRIGHT:
		m_moveCount++;
		moveSpeed.x = 0.09f;
		moveSpeed.z = 0.05f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			m_obj->m_sprite->m_pos.z += moveSpeed.z;
			m_obj->m_sprite->m_pos.x += moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット

			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos += 1;
			m_railPos.verticalPos -= 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
		}

		break;

	case RIGHT:

		moveSpeed.x = 0.09f;
		m_moveCount++;

		if (m_moveCount * moveSpeed.x <= 4.5f) {

			m_obj->m_sprite->m_pos.x += moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット

			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos += 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = false;
	
		}

		break;

	case DOWNRIGHT:

		m_moveCount++;
		moveSpeed.x = 0.09f;
		moveSpeed.z = 0.05f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
			m_obj->m_sprite->m_pos.x += moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット
			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos += 1;
			m_railPos.verticalPos += 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = false;
		}

		break;

	case DOWN:

		moveSpeed.z= 0.05f;
		m_moveCount++;

		if (m_moveCount * moveSpeed.z <= 2.5f) {

			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット
			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.verticalPos += 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = false;
		}
		break;

	case DOWNLEFT:
		m_moveCount++;
		moveSpeed.x = 0.09f;
		moveSpeed.z = 0.05f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
			m_obj->m_sprite->m_pos.x -= moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット

			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos -= 1;
			m_railPos.verticalPos += 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
		}
		break;

	case LEFT:

		moveSpeed.x = 0.09f;

		m_moveCount++;

		if (m_moveCount * moveSpeed.x <= 4.5) {

			m_obj->m_sprite->m_pos.x -= moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット
			//いち
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos -= 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = false;
			//isGetInput = false;
		}

		break;

	case UPLEFT:

		m_moveCount++;
		moveSpeed.x = 0.09f;
		moveSpeed.z = 0.05f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			m_obj->m_sprite->m_pos.z += moveSpeed.z;
			m_obj->m_sprite->m_pos.x -= moveSpeed.x;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_moveCount = 0;//カウンターをリセット

			//移動終了後レールの情報更新
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動前の情報更新
			RailManager::Get()->m_info[pos].isVacant = true;
			//Pointの情報を更新する
			m_railPos.horizontalPos -= 1;
			m_railPos.verticalPos -= 1;
			pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
		}
		break;

	case STILL:

		break;
		}
}

void GameObject::ObjectVibration()
{
}

void GameObject::MoveObject(Object* _target)
{
	//移動入力
	//WASD上下左右移動
	if (Input::Get()->GetKeyTrigger(DIK_W)) {

		//_target->m_sprite->m_pos.y += MOVEDISTANCEZ /2;
		_target->m_sprite->m_pos.z += MOVEDISTANCEZ;
	}

	if (Input::Get()->GetKeyTrigger(DIK_A)) {

		_target->m_sprite->m_pos.x -= MOVEDISTANCEX;

	}

	if (Input::Get()->GetKeyTrigger(DIK_D)) {

		_target->m_sprite->m_pos.x += MOVEDISTANCEX;

	}

	if (Input::Get()->GetKeyTrigger(DIK_S)) {

		//_target->m_sprite->m_pos.y -= MOVEDISTANCEZ / 2;
		_target->m_sprite->m_pos.z -= MOVEDISTANCEZ;

	}
	//↑キー/↓キーで前後移動

	if (Input::Get()->GetKeyTrigger(DIK_UPARROW))
	{
		_target->m_sprite->m_pos.y += MOVEDISTANCEZ;
	}

	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW))
	{
		_target->m_sprite->m_pos.y -= MOVEDISTANCEZ;
	}


	if (Input::Get()->GetKeyPress(DIK_LEFTARROW))
	{
		_target->m_sprite->m_rotation.x += 1.0f;
	}

	//←キー/→キーで角度の調整
	if (Input::Get()->GetKeyPress(DIK_RIGHTARROW))
	{
		_target->m_sprite->m_rotation.x -= 1.0f;
	}


	//RESET
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		_target->m_sprite->m_rotation.x = 0.0f;
		_target->m_sprite->m_pos.x = 0.0f;
	}
}

void GameObject::Draw(void)
{

	//影を描画する
	m_shadow->Draw();

	//オブジェクトを描画する
	m_obj->Draw();
}

GameObject::~GameObject()
{
	delete m_obj;
	delete m_shadow;
	delete m_shadowCollider;

}

