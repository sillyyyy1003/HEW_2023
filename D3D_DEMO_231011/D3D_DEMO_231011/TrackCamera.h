#pragma once
#include "Object.h"


class TrackCamera :public Camera
{

public:

	void Update() override;

	void SetTarget(Object* _targetObejct);


private:
	Object* m_targetObject;

};

