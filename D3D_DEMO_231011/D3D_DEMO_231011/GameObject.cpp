#include "GameObject.h"
#include "ShadowObject.h"
#include "SphereCollider.h"
#include "StaticAnimation.h"
#include "DInput.h"
#include "RailManager.h"
#include "SceneManager.h"
#include <math.h>

extern Camera* g_WorldCamera;

#define BOXMEDIUM 1.5f
#define BOXLARGE 2.1f

#define SPHEREMEDIUM 1.8f
#define SPHERELARGE 2.5f

#define POLYGONMEDIUM 1.5f
#define POLYGONLARGE 2.1f

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

void GameObject::InitCollision(void)
{
	switch (m_shadowCollider->GetColliderType())
	{
	case POLYGON:
		SpolygonCollider = m_shadowCollider->GetPolygonCollider();
		break;
	case SPHERE:
		SsphereCollider = m_shadowCollider->GetSphereCollider();
		break;
	case SQUARE:
		SboxCollider = m_shadowCollider->GetBoxCollider();
		break;
	}
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
	m_railPos.verticalPos = verPos; m_railPos.horizontalPos = horPos;
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
		if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
		
			if (isMoveable(UP))//前に移動できるかを判断
			{
				m_moveDir = UP;//return UP signal

			}
	
		}

		if (m_moveDir == UP) {

		}

		//移動完成後
		int stageInfo = SceneManager::Get()->GetActiveStage();
		SceneManager::Get()->m_stageHolder[stageInfo]->StepCount();

	}
	//オブジェクト情報更新
	

	//影情報更新

	if (m_shadowCollider)
	{
		m_shadowCollider->Update(m_shadow->m_sprite->m_pos, m_shadow->m_sprite->m_rotation);
	}


	//位置を更新
	m_shadow->m_sprite->m_pos = GenerateShadowPos();

	// オブジェクトの位置によって影の大きさを調整
	if (m_obj->m_sprite->m_pos.z <= -2)
	{
		// SMALL
		m_railPos.verticalPos = 0;
	}
	if (m_obj->m_sprite->m_pos.z <= -4)
	{
		// MIDDLE
		m_railPos.verticalPos = 1;
	}
	if (m_obj->m_sprite->m_pos.z <= -8)
	{
		// LARGE
		m_railPos.verticalPos = 2;
	}

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

	if (GetActive())
	{
		// 影の大きさによって当たり判定の調整
		switch (m_shadow->m_size)
		{
		case ShadowObject::SIZE::SMALL:
			// 円の半径（小）
			m_shadowCollider->SetSphereCollider(SsphereCollider.Radius);
			// 三角の半径（小）
			m_shadowCollider->SetPolygonCollider(SpolygonCollider.Radius);
			// 四角の幅（小）
			m_shadowCollider->SetBoxCollider({ SboxCollider.Extents.x,SboxCollider.Extents.y,SboxCollider.Extents.z });
			break;
		case ShadowObject::SIZE::MEDIUM:
			// 円の半径（中）
			m_shadowCollider->SetSphereCollider(SsphereCollider.Radius* SPHEREMEDIUM);
			// 三角の半径（中）
			m_shadowCollider->SetPolygonCollider(SpolygonCollider.Radius*POLYGONMEDIUM);//1.5
			// 四角の幅（中）
			//DirectX::XMFLOAT3 medium = { SboxCollider.Extents.x * SCALEMEDIUM,0,0 };
			m_shadowCollider->SetBoxCollider({ SboxCollider.Extents.x* BOXMEDIUM,SboxCollider.Extents.y * BOXMEDIUM,SboxCollider.Extents.z * BOXMEDIUM });
			break;
		case ShadowObject::SIZE::LARGE:
			// 円の半径（大）
			m_shadowCollider->SetSphereCollider(SsphereCollider.Radius* SPHERELARGE);
			// 三角の半径（大）
			m_shadowCollider->SetPolygonCollider(SpolygonCollider.Radius* POLYGONLARGE);//2.1
			// 四角の幅（大）
			m_shadowCollider->SetBoxCollider({ SboxCollider.Extents.x * BOXLARGE,SboxCollider.Extents.y * BOXLARGE,SboxCollider.Extents.z * BOXLARGE });
			break;
		}
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

	//影
	m_shadow->Update();

	if (GetActive())
	{
		m_shadow->m_sprite->m_pos.x = m_obj->m_sprite->m_pos.x;
		//m_shadow->m_sprite->m_pos.y = m_obj->m_sprite->m_pos.y;

		SetSize(m_shadow->m_size);
	}
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
	
	//switch (m_obj->m_collider->GetColliderType()) {
	//case SPHERE:
	//	//位置と半径をリアルタイムで更新する
	//	//dynamic_cast<SphereCollider*>(m_objCollider)->m_center = { 0.0f,0.0f,0.0f };
	//	//dynamic_cast<SphereCollider*>(m_objCollider)->m_radius = 1.0f;
	// //更新したデータを本体のColliderに更新する
	// m_objCollider->Update();
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

