#pragma once
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


private:
	//追跡対象オブジェクト
	//Object* m_targetObject;
	StaticObject* m_targetObject;

};

