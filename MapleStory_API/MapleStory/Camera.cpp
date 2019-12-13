#include "Camera.h"
#include "Obj.h"

DEFINITION_SINGLE(CCamera)

CCamera::CCamera() :
	m_pTarget(nullptr)
{
}

CCamera::~CCamera()
{
	SAFE_RELEASE(m_pTarget);
}

void CCamera::SetTarget(CObj* pTarget)
{
	SAFE_RELEASE(m_pTarget);

	if (pTarget)
		pTarget->AddRef();

	m_pTarget = pTarget;
}

bool CCamera::Init()
{
	return true;
}

void CCamera::Update(float fTime)
{
	// 타겟이 있을경우 타겟을 중심으로 타겟피봇과 해상도를 이용하여 카메라의 좌상단 위치를
	// 잡아준다.
	if (m_pTarget)
	{
		POSITION	tTargetPos = m_pTarget->GetPos();
		m_tPos = tTargetPos - m_tTargetPivot * m_tResolution;

		if (m_tPos.x < 0.f)
			m_tPos.x = 0.f;

		else if (m_tPos.x + m_tResolution.x >= m_tWorldSize.x)
			m_tPos.x = m_tWorldSize.x - m_tResolution.x;

		if (m_tPos.y < 0.f)
			m_tPos.y = 0.f;

		else if (m_tPos.y + m_tResolution.y >= m_tWorldSize.y)
			m_tPos.y = m_tWorldSize.y - m_tResolution.y;
	}
}
