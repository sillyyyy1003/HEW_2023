#pragma once
#include <DirectXCollision.h>
#include "SatCollider.h"
#include "SatCollider.h"
#include "Material.h"

enum COLLISION_TYPE {
	TRIANGLE,		//三角形
	SPHERE,			//球体
	SQUARE,			//BOX
	IDLE,			//NULL
};

enum COLLISION_DIR {
	INI_STATE,	//初期状態
	COL_UP,		//上
	COL_DOWN,	//下
	COL_LEFT,	//左
	COL_RIGHT,	//右
	OVERLAP,	//重なる
	
};

struct Collider_Dir {
	
	COLLISION_DIR horizontal;//左右
	COLLISION_DIR vertical;//上下

	bool operator==(const Collider_Dir& other) const {
		return (vertical == other.vertical) && (horizontal == other.horizontal);
	}
};

class BoxCollider;
class SphereCollider;
class PolygonCollider;

class Collider
{
protected:

	COLLISION_TYPE m_collisionType = COLLISION_TYPE::IDLE;

protected:

	struct Point {
		float x, y;
	};

	struct Triangle {//時計周り
		Point A;//頂点
		Point B;//右
		Point C;//左
	};

	//左上から
	struct SQUARE {//時計周り
		Point A;//左上
		Point B;//右上
		Point C;//右下
		Point D;//左下
	};


public:

	//コライダーは起動しているか
	bool isActive = true;
	//中心点の位置
	DirectX::XMFLOAT3 m_center = { 0,0,0 };
	//xyz軸の半辺長
	DirectX::XMFLOAT3 m_extents = { 0,0,0 };
	//半径
	float m_radius = 0.0f;




public:

	Collider();

	//virtual std::vector<Vector3> GetVerticies();

	//コライダーのタイプを設定
	virtual void InitColliderType(COLLISION_TYPE _type);

	virtual void InitCollider(XMFLOAT3 center, Collide collider);

	//コライダーの初期化を億なう変数
	/*virtual void InitCollider(DirectX::XMFLOAT3 center, Collide collider);*/

	COLLISION_TYPE GetColliderType(void) { return m_collisionType; };

	//コライダーの更新を行う
	virtual void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents);


	virtual bool isCollision(BoxCollider* boxColliser) { return false;};
	virtual bool isCollision(SphereCollider* sphereCollider) { return false;  };
	virtual bool isCollision(PolygonCollider* polygonCollider) { return false;  };
	virtual bool isCollision(Collider* collider) { return false;  };

	//virtual void Update();

	//対象オブジェクトはこのオブジェクトのどこにあるか
	Collider_Dir GetCollisionDir(Collider* collider);

	//virtual bool isClearCollision(Collider* polygoncollider, float verNum) { return false; };

	//DirectX::BoundingSphere GetSphereCollider(void) { return m_sphereCollider; };
	//void SetSphereCollider(float radius) { m_sphereCollider.Radius = radius; };

	//DirectX::BoundingSphere GetPolygonCollider(void) { return m_polygonCollider; };
	//void SetPolygonCollider(float radius) { m_polygonCollider.Radius = radius; };

	//DirectX::BoundingBox GetBoxCollider(void) { return m_boxCollider; };
	//void SetBoxCollider(DirectX::XMFLOAT3 extens) { m_boxCollider.Extents = extens; };


	~Collider(void);

};

