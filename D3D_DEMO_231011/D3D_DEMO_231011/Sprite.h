#pragma once
#include "Material.h"
#include "Camera.h"
#include "Animation.h"



/// <summary>
/// 頂点データを表す構造体
/// </summary>
struct VERTEX
{
	float x, y, z;		//頂点の位置座標
	float u, v;			//テクスチャのUV座標
	float nx, ny, nz;	//法線ベクトルの座標
	
};


//定数バッファ用構造体
struct CONSTBUFFER
{

	DirectX::XMMATRIX matrixUV;		//UV座標移動行列
	DirectX::XMMATRIX matrixProj;		//投影行列
	DirectX::XMMATRIX matrixWorld;		//ワールド変換行列
	DirectX::XMMATRIX matrixRotate;
	DirectX::XMFLOAT4 materialDiffuse;	//マテリアル色
	
};

/// <summary>
/// 画像の処理と描画
/// </summary>
class Sprite :public Material
{

public:
	//----------------------------//
	// 変数
	//----------------------------//

	//仮想世界のワールド座標
	DirectX::XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };

	//回転
	DirectX::XMFLOAT3 m_rotation = { 0.0f, 0.0f, 0.0f };

	//画像の大きさ(Default Data:1.0)
	DirectX::XMFLOAT3 m_scale = { 1.0, 1.0f, 1.0f };

	//縦横分割->描画用
	DirectX::XMINT2 m_split = { 1,1 };

	//このキャラクターのマテリアル色(DEFAULT COLOR:WHITE)
	DirectX::XMFLOAT4 m_materialDiffuse = { 1.0f,1.0f,1.0f,1.0f };

	//カメラに関する変数
	Camera* m_camera = nullptr;
	bool isUseCamera = true;	//カメラを使うかどうか？

	//アニメーション
	Animation* m_anime = nullptr;

//TEST
	// 右ベクトル
	DirectX::XMFLOAT3 right = {1,0,0};
	float moveSpeed = 0.0f;

public:

	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	// モデルの作成->廃棄
	//Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);
	
	///コンストラクタ
	Sprite(void);

	/// <summary>
	/// モデルの作成
	/// </summary>
	/// <param name="texture">テクスチャ</param>
	/// <param name="_width">画面に描画する幅</param>
	/// <param name="_height">画面に描画する高さ</param>
	/// <param name="splitX">横分割</param>
	/// <param name="splitY">縦分割</param>
	virtual void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	/// <summary>
	/// 位置の初期化
	/// </summary>
	void InitPos(float x, float y, float z);

	/// <summary>
	/// シェーダーに渡す行列の処理を行う関数(回転/拡大縮小)
	/// 平行投影用
	/// </summary>
	/// <param name="cb">シェーダーに渡す行列</param>
	void GenerateMatrix(CONSTBUFFER& cb);


	/// <summary>
	/// マウスの操作でオブジェクトを回転させる処理の関数(途中）
	/// </summary>
	/// <param name="rot">オブジェクトの回転</param>
	void RotateObj(XMFLOAT3& rot);

	// *TEST* 移動の関数
	void SetMoveSpeed(float speed);
	float GetMoveSpeed();
	// 右ベクトル
	DirectX::XMFLOAT3 GetRight();

	/// <summary>
	/// 描画を行う関数
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// 後片付け
	/// </summary>
	~Sprite(void);

};

