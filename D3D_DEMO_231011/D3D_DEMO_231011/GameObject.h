#pragma once
#include "Direct3D/Direct3D.h"
#include "RailManager.h"
#include <DirectXCollision.h>

class Object;
class ShadowObject;
class Collider;

struct RailPos {

	int verticalPos = 0;	//縦	 0:BACK 1:MIDDLE 2:FRONT
	int horizontalPos = 0;	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
};

class GameObject
{
private:

	DirectX::XMFLOAT3 m_lightPos = {};

	//レールにいる位置
	RailPos m_railPos = { 0,0 };

	//移動の方向
	DIR	m_moveDir = STILL;

	//操作中かどうか？
	bool isActive = false;

	int m_size = 0;

	DirectX::BoundingSphere SsphereCollider;
	DirectX::BoundingSphere SpolygonCollider;
	DirectX::BoundingBox SboxCollider;

public:
	//----------------------------//
	// 変数
	//----------------------------//
	//オブジェクトの図形情報
	Object* m_obj;
	//本体の当たり判定を扱う
	//Collider* m_objCollider = nullptr;
		
	//影の図形情報
	ShadowObject* m_shadow;

	//影の当たり判定を扱う
	Collider* m_shadowCollider = nullptr;
	

	//光があるかどうか
	bool isLit = false;

	bool isPlayer = false;
	
public:
	//コンストラクタ
	GameObject();

	/// <summary>
	/// オブジェクトのモデルを作る
	/// </summary>
	/// <param name="texture">テキスチャー</param>
	/// <param name="_width">幅</param>
	/// <param name="_height">高さ</param>
	/// <param name="splitX">横分割</param>
	/// <param name="splitY">縦分割</param>
	void CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	/// <summary>
	/// 影のモデルを作る
	/// </summary>
	/// <param name="texture">テキスチャー</param>
	/// <param name="_width">幅</param>
	/// <param name="_height">高さ</param>
	/// <param name="splitX">横分割</param>
	/// <param name="splitY">縦分割</param>
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	// アニメーションの初期化処理
	void InitAnimation(void);

	// Collisionの初期化(スケールの変化に対応するために必要)
	void InitCollision(void);

	/// <summary>
	/// 影の生成位置を計算する関数
	/// </summary>
	/// <param name="lightPos">光源の位置</param>
	/// <param name="objPos">オブジェクトの位置</param>
	/// <returns>影の位置</returns>
	DirectX::XMFLOAT3 GenerateShadowPos();

	//レールの位置
	void SetRailPos(int horPos, int verPos);
	RailPos GetRailPos() { return m_railPos; };

	//オブジェクトの操作状態
	void SetActive(bool isActive) { this->isActive = isActive; };
	bool GetActive() { return isActive; };

	int GetSize() { return m_size; };
	void SetSize(int size) { m_size = size; };

	void SetLightPos(DirectX::XMFLOAT3 _lightPos);

	//毎回ゲームループで呼び出せれてる
	void Update(void);

	//移動先に移動できるかどうかの判定を行う
	bool isMoveable(DIR dir);

	//コライダーのデータを更新する
	void UpdateObjectColliderData(void);

	void UpdateShadowColliderData(void);

	//オブジェクトを描画する
	void Draw(void);

	~GameObject();



};

