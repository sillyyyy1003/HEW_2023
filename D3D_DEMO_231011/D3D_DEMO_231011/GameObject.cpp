#include "GameObject.h"
#include "ShadowObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PolygonCollider.h"
#include "StaticAnimation.h"
#include "DInput.h"
#include "Game.h"
#include "CameraShaker.h"
#include "RailManager.h"
#include "SceneManager.h"
#include <math.h>


extern Camera* g_WorldCamera;

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

GameObject* GameObject::Get()
{
	static GameObject instance;
	return& instance;
}

void GameObject::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateObject(texture, _width, _height, splitX, splitY);
}

void GameObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY, COLLISION_TYPE type)
{
	m_shadow->CreateObject(texture, _width, _height, splitX, splitY);

	//コライダーの初期化処理を行う
	switch (type)
	{
	//triangleは個別で初期化をする
	case SPHERE:

		m_shadowCollider = new SphereCollider();
		m_shadowCollider->InitCollider(m_shadow->m_sprite->m_pos, m_shadow->m_sprite->GetCollide());

		break;
	case SQUARE:

		m_shadowCollider = new BoxCollider();
		m_shadowCollider->InitCollider(m_shadow->m_sprite->m_pos, m_shadow->m_sprite->GetCollide());

		break;
	case IDLE:
		//
		m_shadowCollider = nullptr;
		break;
	default:
		break;
	}
}

void GameObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY, COLLISION_TYPE type, TRIANGLE_TYPE _type)
{
	m_shadow->CreateObject(texture, _width, _height, splitX, splitY);

	//コライダーの初期化処理を行う
	m_shadowCollider = new PolygonCollider();
	//dynamic_castを使って、PolygonColliderの初期化を行う
	dynamic_cast<PolygonCollider*>(m_shadowCollider)->InitCollider(m_shadow->m_sprite->m_pos, m_shadow->m_sprite->GetCollide(),_type);
}

void GameObject::InitAnimation(void)
{
	m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);
	m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);
}

void GameObject::InitCollision(void)
{
}

void GameObject::GenerateShadowPos(float center,float interval)
{
	float pos[5] = {
		center - 2 * interval,
		center - interval,
		center,
		center + interval,
		center + 2 * interval,
	};

	float moveSpeed = interval / 25;

	switch (m_moveDir)
	{
	case UP:
		break;
	case UPRIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case RIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case DOWNRIGHT:
		m_shadow->m_sprite->m_pos.x += moveSpeed;
		break;
	case DOWN:
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
		//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
		m_shadow->m_sprite->m_pos.x = pos[m_railPos.horizontalPos];
		break;
	default:
		break;
	}

}


void GameObject::GenerateShadowSize(float speed)
{
	if (isActive) {
		switch (m_moveDir)
		{
		case UP:
			m_shadow->m_sprite->m_scale.x -= speed;
			m_shadow->m_sprite->m_scale.y -= speed;

			break;
		case UPRIGHT:
			m_shadow->m_sprite->m_scale.x -= speed;
			m_shadow->m_sprite->m_scale.y -= speed;

			break;
		case RIGHT:

			break;
		case DOWNRIGHT:
			m_shadow->m_sprite->m_scale.x += speed;
			m_shadow->m_sprite->m_scale.y += speed;

			break;
		case DOWN:
			m_shadow->m_sprite->m_scale.x += speed;
			m_shadow->m_sprite->m_scale.y += speed;
			break;
		case DOWNLEFT:
			m_shadow->m_sprite->m_scale.x += speed;
			m_shadow->m_sprite->m_scale.y += speed;

			break;
		case LEFT:

			break;
		case UPLEFT:
			m_shadow->m_sprite->m_scale.x -= speed;
			m_shadow->m_sprite->m_scale.y -= speed;

			break;
		case STILL:

			switch (m_railPos.verticalPos) {

			case 0:
				m_shadow->m_size = ShadowObject::SIZE::SMALL;//当たり判定用
				m_shadow->m_sprite->m_scale.x = 1.0f;
				m_shadow->m_sprite->m_scale.y = 1.0f;
				break;

			case 1:
				m_shadow->m_size = ShadowObject::SIZE::MEDIUM;//当たり判定用
				m_shadow->m_sprite->m_scale.x = 1.5f;
				m_shadow->m_sprite->m_scale.y = 1.5f;
				break;

			case 2:
				m_shadow->m_size = ShadowObject::SIZE::LARGE;//当たり判定用
				m_shadow->m_sprite->m_scale.x = 2.0f;
				m_shadow->m_sprite->m_scale.y = 2.0f;
				break;

			}

			break;
		default:
			break;
		}



	}
		



}

void GameObject::ShadowUpdate(float center, float interval)
{
	//位置の変更
	GenerateShadowPos(center, interval);

	//大きさの変更
	GenerateShadowSize(0.01); //0.5/50frame=0.01

	//本体の変更
	m_shadow->Update();

	//当たり判定の変更
	if (m_shadowCollider != nullptr) {
		UpdateShadowColliderData();
	}




}


void GameObject::SetRailPos(int horPos, int verPos)
{
	m_railPos.horizontalPos = horPos;
	m_railPos.verticalPos = verPos;


	//ここでオブジェクトの大きさの初期値を調整する
	switch (m_railPos.verticalPos)
	{
	case 0://BACK
		m_obj->m_sprite->m_scale = { 0.8f,0.8f,1.0f };
		m_shadow->m_sprite->m_scale.x = 1.0f;
		m_shadow->m_sprite->m_scale.y = 1.0f;
		m_shadow->m_size = ShadowObject::SMALL;
	
		break;
	case 1://MIDDLE
		m_obj->m_sprite->m_scale = { 0.9f,0.9f,1.0f };
		m_shadow->m_sprite->m_scale.x = 1.5f;
		m_shadow->m_sprite->m_scale.y = 1.5f;
		m_shadow->m_size = ShadowObject::MEDIUM;
		break;
	case 2:
		m_obj->m_sprite->m_scale = { 1.0f,1.0f,1.0f };
		m_shadow->m_sprite->m_scale.x = 2.0f;
		m_shadow->m_sprite->m_scale.y = 2.0f;
		m_shadow->m_size = ShadowObject::LARGE;
		break;
	default:
		break;

	}


}

void GameObject::Update()
{

	//入力処理
	if (isActive) {
		//八方向の入力処理
		if (m_moveDir != STILL) {
			ObjectMove();
			//移動中
		
		}
		else {
			//入力
			DoKeyInput();

			if (isGetInput) {
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

		//オブジェクトが移動中なら、
		if (m_moveDir != STILL) {
			//切り替えを不可にする
			Game::Get()->SetIsControl(false);
		}
		else {
			Game::Get()->SetIsControl(true);
		}

	}

	//自動移動の場合
	if (isAutoMove) {
	
		//自動移動
		//AutoMove();
	
	}


	//オブジェクト情報更新
	m_obj->Update();
	

	////影の情報更新
	//m_shadow->Update();

	////Collider情報更新
	//if (m_shadowCollider) {
	//	UpdateShadowColliderData();
	//}


	
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

			//MessageBoxA(NULL, "point計算エラー！", "エラー", MB_OK | MB_ICONERROR);
			//return false;
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
	//OVERLOADで、コライダーのデータを更新する
	DirectX::XMFLOAT3 center = m_shadow->m_sprite->m_pos;
	center.z = 0.0f;
	DirectX::XMFLOAT3 rotation = m_shadow->m_sprite->m_rotation;
	DirectX::XMFLOAT3 extents = m_shadow->Object::GetExtents();

	m_shadowCollider->Update(center, rotation, extents);
}

void GameObject::ObjectMove()
{
	DirectX::XMFLOAT3 moveSpeed = { 0,0,0 };
	switch (m_moveDir) {
	case UP:

		//moveSpeed.z = 0.1f;
		moveSpeed.z = 0.1;
		if (m_moveCount * moveSpeed.z <= 2.5) {

			m_obj->m_sprite->m_pos.z += moveSpeed.z;
			m_obj->m_sprite->m_scale.x -= 0.004;
			m_obj->m_sprite->m_scale.y -= 0.004;
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case UPRIGHT:
		moveSpeed.x = 0.18f;
		moveSpeed.z = 0.1f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			
			m_obj->m_sprite->m_pos.z += moveSpeed.z;
			//大きさを調整する
			m_obj->m_sprite->m_scale.x -= 0.004;
			m_obj->m_sprite->m_scale.y -= 0.004;

			if (m_obj->m_sprite->m_pos.x >= -0.10 && m_obj->m_sprite->m_pos.x < 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x += moveSpeed.x;
			}
			
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case RIGHT:

		moveSpeed.x = 0.18f;
		if ((m_moveCount * moveSpeed.x) <= 4.5f) {

			if (m_obj->m_sprite->m_pos.x >= -0.10 && m_obj->m_sprite->m_pos.x < 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x += moveSpeed.x;
			}
			
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
	
		}
		m_moveCount++;
		break;

	case DOWNRIGHT:

		moveSpeed.x = 0.18f;
		moveSpeed.z = 0.1f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			
			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
			//大きさを調整する
			m_obj->m_sprite->m_scale.x += 0.004;
			m_obj->m_sprite->m_scale.y += 0.004;

			if (m_obj->m_sprite->m_pos.x >= -0.10 && m_obj->m_sprite->m_pos.x < 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x += moveSpeed.x;
			}

			
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case DOWN:

		moveSpeed.z= 0.1f;

		if (m_moveCount * moveSpeed.z <= 2.5f) {

			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
			//大きさを調整する
			m_obj->m_sprite->m_scale.x += 0.004;
			m_obj->m_sprite->m_scale.y += 0.004;
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case DOWNLEFT:
		moveSpeed.x = 0.18f;
		moveSpeed.z = 0.1f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) {
			m_obj->m_sprite->m_pos.z -= moveSpeed.z;
			//大きさを調整する
			m_obj->m_sprite->m_scale.x += 0.004;
			m_obj->m_sprite->m_scale.y += 0.004;

			if (m_obj->m_sprite->m_pos.x <= 0.10 && m_obj->m_sprite->m_pos.x > 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x -= moveSpeed.x;

			}
		
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case LEFT:

		moveSpeed.x = 0.18f;
		if (m_moveCount * moveSpeed.x <= 4.5) {

			if (m_obj->m_sprite->m_pos.x <= 0.10 && m_obj->m_sprite->m_pos.x > 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x -= moveSpeed.x;
			}

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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case UPLEFT:

		moveSpeed.x = 0.18f;
		moveSpeed.z = 0.1f;
		if (m_moveCount * moveSpeed.z <= 2.5f && m_moveCount * moveSpeed.x <= 4.5) 
		{
			m_obj->m_sprite->m_pos.z += moveSpeed.z;
			//大きさを調整する
			m_obj->m_sprite->m_scale.x -= 0.004;
			m_obj->m_sprite->m_scale.y -= 0.004;

			if (m_obj->m_sprite->m_pos.x <= 0.10 && m_obj->m_sprite->m_pos.x > 0) {
				m_obj->m_sprite->m_pos.x = 0;
			}
			else {
				m_obj->m_sprite->m_pos.x -= moveSpeed.x;
			}
			
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
			//移動完成後ステップ加算
			int stageInfo = SceneManager::Get()->GetActiveStage();
			SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();
		}
		m_moveCount++;
		break;

	case STILL:

		break;
		}
}

void GameObject::ObjectVibration()
{
	//振動スタート
	if (!Game::Get()->GetCameraShaker()->GetShaker()) {
		Game::Get()->GetCameraShaker()->SetShaker(true);
	}
	

}

void GameObject::MoveObject(Object* _target)
{

}

void GameObject::Draw(void)
{

	//オブジェクトを描画する
	m_obj->Draw();
}

GameObject::~GameObject()
{
	delete m_obj;
	delete m_shadow;
	delete m_shadowCollider;

}

