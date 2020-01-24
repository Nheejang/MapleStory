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
	m_tPos = m_pTarget->GetPos();
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
			//m_tPos=m_pTarget->GetPos();
			m_tPos.x = m_pTarget->GetPos().x - m_tResolution.x;
			m_tPos.y = m_pTarget->GetPos().y - m_tResolution.y;

			if (m_tPos.x <= 0)
				m_tPos.x = m_tPrePos.x;
			if (m_tPos.x > m_tWorldSize.x - (m_tResolution.x / 2))
				m_tPos.x = m_tPrePos.x;

			m_tPrePos = m_tPos;
			//if (m_tPos.x < 200.f)
			//	m_tPos.x =m_tResolution.x/2;
			//	m_tPos.y = m_tResolution.y / 2;

			//POSITION	tTargetPos = m_pTarget->GetPos();
			//m_tPos = tTargetPos - m_tTargetPivot * m_tResolution;

			//if (m_tPos.x < 0.f)
			//	m_tPos.x = 0.f;

			//else if (m_tPos.x + m_tResolution.x >= m_tWorldSize.x)
			//	m_tPos.x = m_tWorldSize.x - m_tResolution.x;

			//if (m_tPos.y < 0.f)
			//	m_tPos.y = 0.f;

			//else if (m_tPos.y + m_tResolution.y >= m_tWorldSize.y)
			//	m_tPos.y = m_tWorldSize.y - m_tResolution.y;
		}
	

}
