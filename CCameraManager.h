#pragma once

class CObject;
class CCameraManager :
	public CSingleton<CCameraManager>
{
private:
	D3DXMATRIX m_matProj, m_matView;

	Vector2 m_vCameraPos;
	Vector2 m_vViewSize;

	Vector3 m_vScale;
	Vector3 m_vEndScale;
	Vector3 m_vTarget;

	CObject* m_pFollowObj;
	bool m_bFollowActive;
	
	float m_fAngle;
	float m_ShakeTime;

	void Init();
	void Release();

public:
	void SetTransform();

	void SetFollowObj(CObject* pFollow);
	void MoveCamera(const D3DXVECTOR2& vPlusPos);
	void SetCamera(const D3DXVECTOR2& vSetPos);

	D3DXVECTOR2& GetCameraPos() { return m_vCameraPos; }
	D3DXVECTOR3& GetCameraScale() { return m_vScale; }

	float GetCameraAngle() { return m_fAngle; }

	void Update();
	void Reset();

	void CameraShake(float _time) { m_ShakeTime = _time + timeGetTime(); }
public:
	CCameraManager();
	~CCameraManager();
};

#define CAMERA CCameraManager::GetInst()

#define CAMERASIZEX	CAMERA->GetCameraWidth()
#define CAMERASIZEY CAMERA->GetCameraHeight()