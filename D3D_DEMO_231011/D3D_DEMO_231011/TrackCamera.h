#pragma once
#include "Object.h"


class TrackCamera :public Camera
{

public:

	void Update() override;

	//追跡対象オブジェクトを設定
	void SetTarget(Object* _targetObejct);


private:
	//追跡対象オブジェクト
	Object* m_targetObject;

};

