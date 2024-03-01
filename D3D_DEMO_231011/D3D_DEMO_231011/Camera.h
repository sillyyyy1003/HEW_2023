#pragma once
#include "Direct3D.h"

#define ROTATEX		(0.360022f)	//カメラの回転角度tan19.8°

class Camera
{
private:
	//----------------------------//
	// 変数
	//----------------------------//
	//カメラ用の行列
	DirectX::XMMATRIX m_MatrixView;

protected:

	//distance Y= 7.119
	//distance Z= -21.626
	//rotation X= 19.8°
	
	//カメラの位置
	XMFLOAT3 m_CameraPos = XMFLOAT3(0.0f, 7.119f, -21.626f);
	//注視点
	XMFLOAT3 m_FocusPos = XMFLOAT3(0.0f, 0.0f, -(21.626f - 7.0f / ROTATEX));
	//カメラの上方向
	XMFLOAT3 m_UpDir = XMFLOAT3(0.0f,1.0f,0.0f);


public:
	//唯一のインスタンスを定義
	static Camera* m_camera;

public:
	
	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//
	//Camera();

	/// <summary>
	/// View変換行列の作成＝カメラ用の行列
	/// </summary>
	/// <returns>作成下カメラ用行列を返す関数</returns>
	DirectX::XMMATRIX GetMatrixView(void);
	
	//カメラの位置と注視点の更新を行う
	virtual void Update();

	/// <summary>
	/// カメラ位置変更を行う関数
	/// </summary>
	void SetCameraPos(XMFLOAT3 _cameraPos);
	//カメラ位置を返す関数
	DirectX::XMFLOAT3 GetCameraPos(void);


	/// <summary>
	/// 注視点位置変更を行う関数
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

