#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>
#include "Camera.h"


class Object;
class StaticObject;

class TrackCamera :public Camera
{

public:
	
	void Update() override;

	//追跡対象オブジェクトを設定
	void SetTarget(Object* _targetObject);
	void SetTarget(StaticObject* _targetObject);

	/// <summary>
	/// 追跡ターゲット法線ベクトルを計算する関数
	/// </summary>
	/// <returns>追跡ターゲットの法線ベクトル</returns>
	DirectX::XMFLOAT3 GenerateTargetNormal(void);

private:
	//追跡対象オブジェクト
	Object* m_targetObject;

};

