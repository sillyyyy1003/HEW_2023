#include "GameObject.h"
#include "ShadowObject.h"
#include "SphereCollider.h"
#include "StaticAnimation.h"
#include "DInput.h"
#include "RailManager.h"
#include "SceneManager.h"
#include <math.h>
#include "DInput.h"

//#define MOVEDISTANCEZ 2.5
#define MOVEDISTANCEZ 1
//#define MOVEDISTANCEX 4.4
#define MOVEDISTANCEX 1

extern Camera* g_WorldCamera;

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


DirectX::XMFLOAT3 GameObject::GenerateShadowPos()
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

	DirectX::XMFLOAT3 shadowPosition = m_shadow->m_sprite->m_pos;

	//
	switch (m_railPos.horizontalPos) {

	case 0:
		//m_shadow->m_sprite->m_pos.x
		break;

	case 1:

		break;

	case 2:
		break;


	case 3:
		break;

	case 4:

		break;

	}
	return shadowPosition;
}

void GameObject::SetRailPos(int horPos, int verPos)
{
	m_railPos.horizontalPos = horPos;
	m_railPos.verticalPos = verPos;
}

void GameObject::SetLightPos(DirectX::XMFLOAT3 _lightPos)
{
	m_lightPos = _lightPos;
}

void GameObject::Update()
{
	//入力処理
	if (isActive) {
		//八方向の入力処理
		//上
		if (m_moveDir == STILL)
		{

			if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {

				if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {

					if (isMoveable(UPRIGHT))//移動先に移動できるかを判断
					{
						m_moveDir = UPRIGHT;//移動方向を変える

					}
					else {
						//移動できないの表示
						ObjectVibration();
					}
				}
				else if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {

					if (isMoveable(UPLEFT)) {
						m_moveDir = UPLEFT;
					}

				}
				else if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {

					m_moveDir = STILL;
				}
				else {
					if (isMoveable(UP)) {
						m_moveDir = UP;
					}
				}

			}
			//下
			if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {

				if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {

					if (isMoveable(DOWNRIGHT))//移動先に移動できるかを判断
					{
						m_moveDir = DOWNRIGHT;//移動方向を変える

					}
				}
				else if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {

					if (isMoveable(DOWNLEFT)) {
						m_moveDir = DOWNLEFT;
					}

				}
				else if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {

					m_moveDir = STILL;
				}
				else {
					if (isMoveable(DOWN)) {
						m_moveDir = DOWN;
					}
				}

			}

			//右
			if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {

				if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {

					if (isMoveable(UPRIGHT))//移動先に移動できるかを判断
					{
						m_moveDir = UPRIGHT;//移動方向を変える

					}
				}
				else if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {

					m_moveDir = STILL;

				}
				else if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {


					if (isMoveable(DOWNRIGHT))//移動先に移動できるかを判断
					{
						m_moveDir = DOWNRIGHT;//移動方向を変える

					}
				}
				else {

					if (isMoveable(RIGHT)) {
						m_moveDir = RIGHT;
					}
				}
			}

			//左
			if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {

				if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {

					if (isMoveable(UPLEFT))//移動先に移動できるかを判断
					{
						m_moveDir = UPLEFT;//移動方向を変える

					}
				}
				else if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {

					m_moveDir = STILL;

				}
				else if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {


					if (isMoveable(DOWNLEFT))//移動先に移動できるかを判断
					{
						m_moveDir = DOWNLEFT;//移動方向を変える

					}
				}
				else {
					if (isMoveable(LEFT)) {
						m_moveDir = LEFT;
					}
				}
			}

		}else 
		{
			ObjectMove();
		}
		

		//移動完成後
		int stageInfo = SceneManager::Get()->GetActiveStage();
		SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
	}
	//オブジェクト情報更新
	

	//影情報更新




	//位置を更新
	m_shadow->m_sprite->m_pos = GenerateShadowPos();
	
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
	


	
	////本体更新した後
	//if (m_obj->m_collider != nullptr) {
	//	
	//	//ここで具体的なCollisionのセンターやスケールを更新する
	//	UpdateObjectColliderData();

	//}

	////影更新した後
	//if (m_shadow->m_collider != nullptr) {
	//	
	//	//ここで具体的なCollisionのセンターやスケールを更新する
	//	UpdateShadowColliderData();

	//}

	

	//オブジェクト本体
	m_obj->Update();

	//Collider データ更新
	m_shadowCollider->Update(m_obj->m_sprite->m_pos, m_obj->m_sprite->m_rotation);

	m_shadow->Update();
}

bool GameObject::isMoveable(DIR dir)
{
		int num = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
		PointInfo info = RailManager::Get()->m_info[num];

		int pos = 0;
		//移動先の位置を計算
		switch (dir) {
		case UP:
			pos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos;
			break;

		case UPRIGHT:
			pos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos + 1;
			break;

		case RIGHT:
			pos = m_railPos.horizontalPos + 1;
			break;

		case DOWNRIGHT:
			pos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos + 1;
			break;

		case DOWN:
			pos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos;
			break;

		case DOWNLEFT:
			pos = (m_railPos.verticalPos + 1) * 5 + m_railPos.horizontalPos - 1;
			break;

		case LEFT:
			pos = m_railPos.horizontalPos - 1;
			break;

		case UPLEFT:
			pos = (m_railPos.verticalPos - 1) * 5 + m_railPos.horizontalPos - 1;
			break;
		case STILL:
			break;
		}

		//There may be some bugs,So Limit the boundary
		if (pos < 0 || pos>14) {

			MessageBoxA(NULL, "point計算エラー！", "エラー", MB_OK | MB_ICONERROR);
			return false;
		}

		//その方向に移動できるか
		if (info.isMoveable[dir]) {
						
			//目標位置は空いてるか？
			if (RailManager::Get()->m_info[pos].isVacant) {

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

void GameObject::UpdateObjectColliderData(void)
{
	//dynamic_castを使って、コライダーのデータを更新する
	//
	//switch (m_shadowCollider->GetColliderType()) {
	//case SPHERE:
	//	//位置と半径をリアルタイムで更新する
	//	dynamic_cast<SphereCollider*>(m_shadowCollider)->m_center = { 0.0f,0.0f,0.0f };
	//	dynamic_cast<SphereCollider*>(m_shadowCollider)->m_radius = 1.0f;
	//	//更新したデータを本体のColliderに更新する
	//	m_shadowCollider->Update()
	//	break;

	//case POLYGON:

	//	break;

	//case SQUARE:

	//	break;

	//default:

	//}






}

void GameObject::UpdateShadowColliderData(void)
{
	//dynamic_castを使って、コライダーのデータを更新する
	
	//switch (m_shadow->m_collider->GetColliderType()) {
	//case SPHERE:
	
	//	
	//	//dynamic_cast<SphereCollider*>(m_shadowCollider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_shadowCollider)->m_radius = 1.0f;
	
	
	////更新したデータを本体のColliderに更新する
	// 	m_shadowCollider->Update();
	//	break;

	//case POLYGON:

	//	break;

	//case SQUARE:

	//	break;

	//default:

	//}




}

void GameObject::ObjectMove()
{
	float moveSpeed = 0;

	switch (m_moveDir) {
	case UP:


		break;

	case UPRIGHT:

		break;

	case RIGHT:

		moveSpeed = 0.05f;
		m_count++;

		if (m_count * moveSpeed <= 5.0f) {

			m_obj->m_sprite->m_pos.x += moveSpeed;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_count = 0;//カウンターをリセット
			//Pointの情報を更新する


			if (m_railPos.horizontalPos <= 3) {//制限を加えて
				m_railPos.horizontalPos += 1;
			}

			//
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
			//移動前の情報更新
			RailManager::Get()->m_info[(pos - 1)].isVacant = true;
		}


		break;

	case DOWNRIGHT:

		break;

	case DOWN:
		moveSpeed = 0.04f;
		m_count++;
		if (this->m_railPos.verticalPos == 0) {
		
			if (m_count * moveSpeed <= 4.0f) {
				
				m_obj->m_sprite->m_pos.z -= moveSpeed;
			}
			else {
				//移動終了
				m_moveDir = STILL;
				m_count = 0;//カウンターをリセット
				//Pointの情報を更新する

				if (m_railPos.verticalPos < 2) {//制限を加えて
					m_railPos.verticalPos += 1;
				}

				//
				int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
				//移動したの情報更新する
				RailManager::Get()->m_info[pos].isVacant = false;
				//移動前の情報更新
				RailManager::Get()->m_info[(pos - 5)].isVacant = true;
			}
		
		
		}
		else if (this->m_railPos.verticalPos == 1) {
			moveSpeed = 0.03f;
			if (m_count * moveSpeed <= 3.0f) {
				
				m_obj->m_sprite->m_pos.z -= moveSpeed;
			}
			else {
				//移動終了
				m_moveDir = STILL;
				m_count = 0;//カウンターをリセット
				//Pointの情報を更新する


				if (m_railPos.verticalPos < 2) {//制限を加えて
					m_railPos.verticalPos += 1;
				}

				//
				int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
				//移動したの情報更新する
				RailManager::Get()->m_info[pos].isVacant = false;
				//移動前の情報更新
				RailManager::Get()->m_info[(pos - 5)].isVacant = true;
			}
		}




		break;

	case DOWNLEFT:

		break;

	case LEFT:

		moveSpeed = 0.05f;
		m_count++;

		if (m_count * moveSpeed <= 5.0f) {

			m_obj->m_sprite->m_pos.x -= moveSpeed;
		}
		else {
			//移動終了
			m_moveDir = STILL;
			m_count = 0;//カウンターをリセット
			//Pointの情報を更新する


			if (m_railPos.horizontalPos >0 ) {//制限を加えて
				m_railPos.horizontalPos -= 1;
			}

			//いち
			int pos = m_railPos.verticalPos * 5 + m_railPos.horizontalPos;
			//移動したの情報更新する
			RailManager::Get()->m_info[pos].isVacant = false;
			//移動前の情報更新
			RailManager::Get()->m_info[(pos + 1)].isVacant = true;
		}

		break;

	case UPLEFT:

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

}

