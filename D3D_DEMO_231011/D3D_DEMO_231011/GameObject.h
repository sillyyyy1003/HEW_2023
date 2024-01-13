#pragma once
#include "Direct3D/Direct3D.h"

class Object;
class ShadowObject;

class GameObject
{
private:

	DirectX::XMFLOAT3 m_lightPos = {};

public:
	//----------------------------//
	// 変数
	//----------------------------//
	//オブジェクトの図形情報
	Object* m_obj;
		
	//影の図形情報
	ShadowObject* m_shadow;



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


	/// <summary>
	/// 影の生成位置を計算する関数
	/// </summary>
	/// <param name="lightPos">光源の位置</param>
	/// <param name="objPos">オブジェクトの位置</param>
	/// <returns>影の位置</returns>
	DirectX::XMFLOAT3 GenerateShadowPos(DirectX::XMFLOAT3 lightPos);

	void SetLightPos(DirectX::XMFLOAT3 _lightPos);

	//毎回ゲームループで呼び出せれてる
	void Update(void);

	//コライダーのデータを更新する
	
	void UpdateObjectColliderData(void);

	void UpdateShadowColliderData(void);

	//オブジェクトを描画する
	void Draw(void);

	~GameObject();



};

