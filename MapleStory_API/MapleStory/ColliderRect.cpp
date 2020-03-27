#include"ColliderRect.h"
#include"Obj.h"
//#include"ColliderSphere.h"
//#include"ColliderPoint.h"
#include"ColliderPixel.h"
#include"Camera.h"


CColliderRect::CColliderRect()
{
	SetTag("Rect");
	m_eCollType = CT_RECT;

	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

CColliderRect::CColliderRect(const CColliderRect& coll) :
	CCollider(coll)
{
	m_tRelative = coll.m_tRelative;
	m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	m_hBrush = m_hGreenBrush;
}

CColliderRect::~CColliderRect()
{
	DeleteObject(m_hGreenBrush);
	DeleteObject(m_hRedBrush);
}

bool CColliderRect::Init()
{
	return true;
}

int CColliderRect::Update(float fTime)
{
	m_tSize.x = m_tRelative.r - m_tRelative.l;
	m_tSize.y = m_tRelative.b - m_tRelative.t;

	//상대 정보를 이용하여 월드 정보를 만들어 낸다.
	POSITION tPos = m_pObj->GetPos();

	if (m_bUI && m_pObj->GetObjType() != OT_UI)
		tPos -= CAMERAPOS;

	m_tWorldInfo.l = tPos.x + m_tRelative.l - m_tSize.x * m_tPivot.x;
	m_tWorldInfo.t = tPos.y + m_tRelative.t - m_tSize.y * m_tPivot.y;
	m_tWorldInfo.r = m_tWorldInfo.l + m_tSize.x;
	m_tWorldInfo.b = m_tWorldInfo.t + m_tSize.y;

	return 0;
}

void CColliderRect::Render(HDC hDC, float fTime)
{
#ifdef _DEBUG
	if (m_PrevCollider.empty())
		m_hBrush = m_hGreenBrush;
	else
		m_hBrush = m_hRedBrush;

	RECTINFO tInfo = m_tWorldInfo;

	if (!m_bUI)
	{
		POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();

		tInfo.l -= tCameraPos.x;
		tInfo.r -= tCameraPos.x;
		tInfo.t -= tCameraPos.y;
		tInfo.b -= tCameraPos.y;
	}

	m_hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);

	RECT rc = { tInfo.l,tInfo.t,tInfo.r,tInfo.b };
	FrameRect(hDC, &rc, m_hBrush);


	SelectObject(hDC, m_hOldBrush);
#endif
	
}

CColliderRect* CColliderRect::Clone() const
{
	return new CColliderRect(*this);
}

bool CColliderRect::Collision(CCollider* pDest)
{
	if(m_bUI != pDest->GetUI())
		return false;

	//충돌체 타입에 따라 충돌처리를 한다.
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CColliderRect*)pDest)->m_tWorldInfo);
	/*case CT_SPHERE:
		return CollisionRectToSphere(m_tWorldInfo, ((CColliderSphere*)pDest)->GetInfo());
	case CT_POINT:
		return CollisionRectToPoint(m_tWorldInfo, ((CColliderPoint*)pDest)->GetInfo());*/
	case CT_PIXEL:
		return CollisionRectToPixel(m_tWorldInfo, ((CColliderPixel*)pDest)->GetInfo());
	}

	return false;
}

void CColliderRect::Save(FILE* pFile)
{
	CCollider::Save(pFile);

	fwrite(&m_tRelative, sizeof(RECTINFO), 1, pFile);
	fwrite(&m_tSize, sizeof(_SIZE), 1, pFile);
}

void CColliderRect::Load(FILE* pFile)
{
	CCollider::Load(pFile);

	fread(&m_tRelative, sizeof(RECTINFO), 1, pFile);
	fread(&m_tSize, sizeof(_SIZE), 1, pFile);
}