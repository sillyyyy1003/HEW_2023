#pragma once
#include "Direct3D.h"
#include "RailManager.h"
#include "Collider.h"
#include <string>
#include "Object.h"

class Object;
class ShadowObject;

struct RailPos {

	int verticalPos=0;	//縦	 0:BACK 1:MIDDLE 2:FRONT
	int horizontalPos=0;	//横 0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2
};

class GameObject
{
private:

	DirectX::XMFLOAT3 m_lightPos = {};

	//レールにいる位置
	RailPos m_railPos;

	//移動の方向
	DIR	m_moveDir = STILL;

	//操作中かどうか？
	bool isActive = false;

	//移動用のカウンター
	int m_moveCount = 0;

	//入力待ちカウンター
	int m_inputCount = 0;

	//入力
	int m_lastPressTime = 0;

	//時間測定開始
	bool isInputCount = false;

	//方向を受ける
	bool isGetInput = false;

	//移動しているかどうか？
	bool isMove = false;

	enum INPUT {
		INPUT_UP,
		INPUT_RIGHT,
		INPUT_DOWN,
		INPUT_LEFT,
		INPUT_NONE
	};

	struct InputCom {
		INPUT verInput;
		INPUT horInput;
	};
	bool isInit = true; //前回の記録スタートしたかどうか？

	//入力の結果
	InputCom m_nowInput = { INPUT_NONE,INPUT_NONE };

	//入力の時間計算
	int m_countTime = 0;

	//自動移動しているObjectかどうか
	bool isAutoMove = false;

	//今影の大きさ
	int m_size = 0;

	

public:

	//----------------------------//
	// 変数
	//----------------------------//
	//オブジェクトの図形情報
	Object* m_obj;

	//影の図形情報
	ShadowObject* m_shadow;

	//影の当たり判定を扱う
	Collider* m_shadowCollider = nullptr;

	//光があるかどうか
	bool isLit = false;

	std::string m_name;//名前　デバッグ用



private:

	//入力の判定
	void DoKeyInput(void);

	bool isPlayer = false;



public:
	//コンストラクタ
	GameObject();

	static GameObject* Get();

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
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY, COLLISION_TYPE type);

	/// <summary>
	/// 三角形だけに使う
	/// </summary>
	/// <param name=""></param>
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY, COLLISION_TYPE type,TRIANGLE_TYPE _type);


	// アニメーションの初期化処理
	void InitAnimation(void);

	// Collisionの初期化(スケールの変化に対応するために必要)
	void InitCollision(void);

	/// <summary>
	/// 影の位置移動
	/// </summary>
	/// <param name="moveSpeed">移動のスビート</param>
	/// <param name="posX">中心点の位置を設定</param>
	/// <param name="interval">ポイントとポイントの間隔</param>
	void GenerateShadowPos(float center, float interval);
	//void GenerateShadowPos(void);

	//影の大きさの変更
	void GenerateShadowSize(float speed);

	/// <summary>
	/// 影の更新
	/// </summary>
	/// <param name="center">中心点</param>
	/// <param name="interval">間隔</param>
	void ShadowUpdate(float center, float interval);
	

	/// <summary>
	/// レール上も位置を設定する
	/// </summary>
	/// <param name="horPos">横　0:LEFT1 1:LEFT2 2:MIDDLE 3:RIGHT1 4:RIGHT2</param>
	/// <param name="verPos">縦　0:BACK 1:MIDDLE 2:FRONT</param>
	void SetRailPos(int horPos, int verPos);
	RailPos GetRailPos() { return m_railPos; };

	//オブジェクトの操作状態
	void SetActive(bool isActive) { this->isActive = isActive; };
	bool GetActive() { return isActive; };

	int GetSize() { return m_size; };
	void SetSize(int size) { m_size = size; };

	void SetName(std::string Name) { m_name = Name; };
	std::string GetName(void) { return m_name; };

	//自動移動稼働か状態を設定
	void SetAutoMove(bool isAutoMove) { this->isAutoMove = isAutoMove; };
	bool GetAutoMove(void) { return isAutoMove; };

	//移動しているかどうか？
	bool GetIsMove(void){return isMove;};

	//毎回ゲームループで呼び出せれてる
	void Update(void);

	//移動先に移動できるかどうかの判定を行う
	bool isMoveable(DIR dir);
	bool GetDir(void) { return m_moveDir; };

	//コライダーのデータを更新する
	void UpdateShadowColliderData(void);

	//一定距離の移動
	void ObjectMove(void);

	//自動移動を行う
	void AutoMove(void);


	//移動できないのエフェクト
	void ObjectVibration();

	//今移動中かどうか？
	bool GetStill() { if (m_moveDir == STILL) { return true; } else { return false; } };

	void ResetMove(void);
	
	DirectX::XMFLOAT3 GetObjectPos() { return m_obj->m_sprite->m_pos; }

	//オブジェクトを描画する
	void Draw(void);

	~GameObject();

	private:
		/// <summary>
		/// オブジェクトの移動をする関数
		/// </summary>
		/// <param name="_lightPos"></param>
		void MoveObject(Object* _target);

};

