#pragma once
#include <vector>
#include "GameObject.h"
#include "Collider.h"
#include "ShadowObject.h"

class ColliderManager
{
private:
	//コンストラクタ&デストラクタ
	ColliderManager() {};
	~ColliderManager();

public:
	//唯一のインスタンスを返す関数
	static ColliderManager* Get();

public:
	void Update(Collider* collider);

	bool isCollide(Collider* collider1, Collider* collider2);

	static void Collision(std::vector<GameObject*> Vobject);

	/// <summary>
	/// ステージ判定用の関数
	/// </summary>
	/// <param name="Vobject">GameObjectを格納するVector</param>
	/// <param name="dir">対象オブジェクトの相対位置</param>
	/// <param name="name1">本体のオブジェクト</param>
	/// <param name="name2">対象オブジェクト</param>
	/// <param name="size">影のサイズ</param>
	/// <returns></returns>
	//bool ClearCollision(Collider_Dir dir, std::string name1, std::string name2, ShadowObject::SIZE size);

	bool ClearCollision(Collider_Dir dir, std::string name1, std::string name12, ShadowObject::SIZE size);
	
};

