#include "TrackCamera.h"
#include "StaticObject.h"



void TrackCamera::Update()
{
	//追跡用の部分
	if (m_targetObject != nullptr) //追跡する場合
	{

		
		//平面との垂直ベクトルを計算する
		DirectX::XMFLOAT3 planeNormal = GenerateTargetNormal();

		//ターゲットオブジェクトの位置を獲得する
		DirectX::XMFLOAT3 planePosition = m_targetObject->m_sprite->m_pos;

		//カメラ/注視点の位置
		DirectX::XMFLOAT3 newCameraPos;
		DirectX::XMFLOAT3 newCameraFocus;

		//カメラから平面の中心の距離を計算する
		//float distance = 0.0f;//変数に変えてほしい

		//回転がない時
		if (m_targetObject->m_sprite->m_rotation.x == 0) {
			
			//カメラの位置を設定する
			newCameraPos.x = m_targetObject->m_sprite->m_pos.x;
			newCameraPos.y = m_targetObject->m_sprite->m_pos.y;
			newCameraPos.z = m_targetObject->m_sprite->m_pos.z - distance;
			//カメラの注視点を設定する
			newCameraFocus.x = m_targetObject->m_sprite->m_pos.x;
			newCameraFocus.y = m_targetObject->m_sprite->m_pos.y;
			newCameraFocus.z = m_targetObject->m_sprite->m_pos.z + 2.0f;

			SetCameraPos(newCameraPos);
			SetFocusPos(newCameraFocus);


		}
		else {

			distance = 9.0f;
			//カメラの位置を設定する
			newCameraPos.x = m_targetObject->m_sprite->m_pos.x;
			newCameraPos.y = distance * planeNormal.y;
			newCameraPos.y = m_targetObject->m_sprite->m_pos.y + newCameraPos.y;
			newCameraPos.z = distance * planeNormal.z;
			newCameraPos.z = m_targetObject->m_sprite->m_pos.z + newCameraPos.z;
			
			//カメラから追跡ターゲット中心点のベクトルを計算する
			DirectX::XMFLOAT3 cameraToPlane;
			cameraToPlane.x = m_targetObject->m_sprite->m_pos.x - newCameraPos.x;
			cameraToPlane.y = m_targetObject->m_sprite->m_pos.y - newCameraPos.y;
			cameraToPlane.z = m_targetObject->m_sprite->m_pos.z - newCameraPos.z;

			//ベクトルを正規化する
			XMVECTOR cameraVector = XMLoadFloat3(&cameraToPlane);
			cameraVector = XMVector3Normalize(cameraVector);
			XMStoreFloat3(&cameraToPlane, cameraVector);

			newCameraFocus.x = newCameraPos.x;
			newCameraFocus.y = 2.0f * cameraToPlane.y;
			newCameraFocus.y = m_targetObject->m_sprite->m_pos.y + newCameraFocus.y;
			newCameraFocus.z = 2.0f * cameraToPlane.z;
			newCameraFocus.z = m_targetObject->m_sprite->m_pos.z + newCameraFocus.z;

			//カメラの注視点を設定する

			SetCameraPos(newCameraPos);
			SetFocusPos(newCameraFocus);

		}

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

void TrackCamera::RomoveTarget(void)
{
	m_targetObject = nullptr;
}

void TrackCamera::SetDistance(float _distance)
{
	distance = _distance;
}

DirectX::XMFLOAT3 TrackCamera::GenerateTargetNormal(void)
{
	//オブジェクトの中心位置と回転角度を獲得する
	DirectX::XMFLOAT3 planePos = m_targetObject->m_sprite->m_pos;
	DirectX::XMFLOAT3 rotateDegrees = m_targetObject->m_sprite->m_rotation;

	//回転を表す四元数
	DirectX::XMVECTOR rotateRadian = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(rotateDegrees.x), XMConvertToRadians(rotateDegrees.y), XMConvertToRadians(rotateDegrees.z));

	//四元数をマトリクスに変換
	DirectX::XMMATRIX matrixRotate = XMMatrixRotationQuaternion(rotateRadian);

	//平面の初期法線ベクトルを設定->左手座標系なので、初期値は(0,0,-1)
	XMVECTOR normalVector = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);

	//平面の実際の回転マトリクスを計算する
	DirectX::XMVECTOR rotatedNormalVector = XMVector3Transform(normalVector, matrixRotate);
	
	//ベクトルを正規化にする
	rotatedNormalVector = XMVector3Normalize(rotatedNormalVector);

	//マトリクスから法線ベクトルに戻る
	DirectX::XMFLOAT3 planeNormal;
	XMStoreFloat3(&planeNormal, rotatedNormalVector);

	//法線ベクトルを正規化にする
	return planeNormal;
}
