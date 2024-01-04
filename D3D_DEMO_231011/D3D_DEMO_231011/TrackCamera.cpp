#include "TrackCamera.h"
#include "StaticObject.h"

void TrackCamera::Update()
{
	if (m_targetObject != nullptr) //追跡する場合
	{

	}
	
	
	
	Camera::Update();

}

void TrackCamera::SetTarget(Object* _targetObject)
{
	m_targetObject = _targetObject;
}

void TrackCamera::SetTarget(StaticObject* _targetObject)
{
	m_targetObject = _targetObject;
}
