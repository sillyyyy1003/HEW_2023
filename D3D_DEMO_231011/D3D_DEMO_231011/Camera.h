#pragma once
#include "Direct3D/Direct3D.h"


class Camera
{
private:
	//----------------------------//
	// 変数
	//----------------------------//
	//カメラ用の行列
	DirectX::XMMATRIX m_MatrixView;
	//カメラの位置
	XMFLOAT3 m_CameraPos = XMFLOAT3(0.0f, 0.0f, -2.0f);
	//注視点
	XMFLOAT3 m_FocusPos = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//カメラの上方向
	XMFLOAT3 m_UpDir = XMFLOAT3(0.0f, 1.0f, 0.0f);

private:
	
	//コンストラクタ
	Camera() = default;

	//唯一のインスタンスを定義
	static Camera* m_camera;


public:
	
	
	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//
	
	/// <summary>
	/// View変換行列の作成＝カメラ用の行列
	/// </summary>
	/// <returns>作成下カメラ用行列を返す関数</returns>
	DirectX::XMMATRIX GetMatrixView(void);
	
	/// <summary>
	/// 唯一のインスタンスを返す関数
	/// </summary>
	/// <returns>m_camera->WorldCamera</returns>
	Camera* GetCamera(void);

	virtual void Update();

	/// <summary>
	/// カメラ位置変更を行う関数
	/// </summary>
	void SetCameraPos(XMFLOAT3 _cameraPos);
	//カメラ位置を返す関数
	DirectX::XMFLOAT3 GetCameraPos(void);


	/// <summary>
	/// カメラ位置変更を行う関数
	/// </summary>
	void SetFocusPos(XMFLOAT3 _focusPos);
	//注視点位置を返す関数
	DirectX::XMFLOAT3 GetFocusPos(void);
	
	/// <summary>
	/// カメラの上方向変更を行う関数
	/// </summary>
	void SetUpDir(XMFLOAT3 _Updir);
	//カメラの上方向を返す関数
	DirectX::XMFLOAT3 GetUpDir(void);

};

