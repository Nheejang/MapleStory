#include"Collider.h"
#include"Obj.h"
#include"Math.h"

CCollider::CCollider()
{
	m_strGroup = "Default";
	m_bUI = false;
}

CCollider::CCollider(const CCollider& coll)
{
	*this = coll;
}

CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd  =m_PrevCollider.end();

	for (iter = m_PrevCollider.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->DeletePrevCollider(this);
		(*iter)->OnCollisionLeave(this, 0.f);
	}
}

string CCollider::GetCollisionType() const
{
	return m_strCollisionType;
}

COLLIDER_TYPE CCollider::GetColliderType()const
{
	return m_eCollType;
}

CObj* CCollider::GetObj()const
{
	m_pObj->AddRef();
	return m_pObj;
}

bool CCollider::Init()
{
	return false;
}

int CCollider::Update(float fTime)
{
	return 0;
}

void CCollider::Render(HDC hDC, float fTime)
{

}

CCollider* CCollider::Clone()const
{
	return nullptr;
}

void CCollider::Save(FILE* pFile)
{
	fwrite(&m_tPivot, sizeof(POSITION), 1, pFile);
	int iLength = m_strGroup.length();
	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_strGroup.c_str(), sizeof(char), iLength, pFile);

	iLength = m_strCollisionType.length();
	fwrite(&iLength, sizeof(int), 1, pFile);
	fwrite(m_strCollisionType.c_str(), sizeof(char), iLength, pFile);

	fwrite(&m_bUI, sizeof(bool), 1, pFile);
}

void CCollider::Load(FILE* pFile)
{
	fread(&m_tPivot, sizeof(POSITION), 1, pFile);
	int iLength = 0;
	fread(&iLength, sizeof(int), 1, pFile);
	char strText[256] = {};
	fread(strText, sizeof(char), iLength, pFile);
	m_strGroup = strText;

	memset(strText, 0, sizeof(char) * 256);
	fread(&iLength, sizeof(int), 1, pFile);
	fread(strText, sizeof(char), iLength, pFile);
	m_strCollisionType = strText;

	fread(&m_bUI, sizeof(bool), 1, pFile);
}

bool CCollider::CollisionRectToRect(const RECTINFO& tSrc, const RECTINFO& tDest)
{
	if (tSrc.l > tDest.r)
		return false;

	else if (tSrc.r < tDest.l)
		return false;
	else if (tSrc.t > tDest.b)
		return false;
	else if (tSrc.b < tDest.t)
		return false;

	RECTINFO tIntersect;

	if (tSrc.l > tDest.l)
		tIntersect.l = tSrc.l;

	else
		tIntersect.l = tDest.l;

	if (tSrc.r > tDest.r)
		tIntersect.r = tDest.r;
	else
		tIntersect.r = tDest.r;

	if (tSrc.t > tDest.t)
		tIntersect.t = tSrc.t;
	else
		tIntersect.t = tDest.t;

	if (tSrc.b > tDest.b)
		tIntersect.b = tDest.b;
	else
		tIntersect.b = tSrc.b;

	m_tIntersect.x = (tIntersect.l + tIntersect.r) / 2.f;
	m_tIntersect.y = (tIntersect.t + tIntersect.b) / 2.f;
	
	return true;
}

bool CCollider::CollisionSphereToSphere(const SPHEREINFO& tSrc, const SPHEREINFO& tDest)
{
	float fDist = CMath::GetDistance(tSrc.tCenter, tDest.tCenter);
	bool bResult = fDist <= tSrc.fRadius + tDest.fRadius;

	if (bResult)
	{
		fDist = (fDist - tDest.fRadius) / fDist;
		m_tIntersect = tSrc.tCenter + (tDest.tCenter - tSrc.tCenter) * fDist;
	}
	
	return bResult;
}

bool CCollider::CollisionRectToSphere(const RECTINFO& tRC, const SPHEREINFO& tSphere)
{
	//원의 중점이 사각형의 왼쪽, 오른쪽 사이에 있거나 위, 아래 사이에있을경우
	//사각형을 원의 반지름만큼 확장해서 원의 중점이 사각형 안에 있는짖를 판단한다.
	if ((tRC.l <= tSphere.tCenter.x && tSphere.tCenter.x <= tRC.r) ||
		(tRC.t <= tSphere.tCenter.y && tSphere.tCenter.y <= tRC.b))
	{
		RECTINFO tRect = RECTINFO(tRC.l - tSphere.fRadius, tRC.t - tSphere.fRadius,
			tRC.r + tSphere.fRadius, tRC.b + tSphere.fRadius);

		if (tRect.l > tSphere.tCenter.x)
			return false;
		else if (tRect.r < tSphere.tCenter.x)
			return false;
		else if (tRect.t > tSphere.tCenter.y)
			return false;
		else if (tRect.b < tSphere.tCenter.y)
			return false;
		return true;
	}

	//사각형의 4개의 점이 원안에 들어오는지 판단한다.
	POSITION tPos;
	tPos = POSITION(tRC.l, tRC.t);

	//원의 중점과 점의 거리를 구해서 이 거리고 반지름보다 작거나 같을 경우 충돌이다.
	float fDist = CMath::GetDistance(tPos, tSphere.tCenter);

	if (fDist <= tSphere.fRadius)
		return true;

	tPos = POSITION(tRC.r, tRC.t);

	//원의 중점과 점의 거리를 구해서 이 거리고 반지름보다 작거나 같을 경우 충돌이다.
	fDist = CMath::GetDistance(tPos, tSphere.tCenter);
	
	if (fDist <= tSphere.fRadius)
		return true;

	tPos = POSITION(tRC.l, tRC.b);

	//원의 중점과 점의 거리를 구해서 이 거리고 반지름보다 작거나 같을 경우 충돌이다.
	fDist = CMath::GetDistance(tPos, tSphere.tCenter);

	if (fDist <= tSphere.fRadius)
		return true;

	tPos = POSITION(tRC.r, tRC.b);

	//원의 중점과 점의 거리를 구해서 이 거리고 반지름보다 작거나 같을 경우 충돌이다.
	fDist = CMath::GetDistance(tPos, tSphere.tCenter);

	if (fDist <= tSphere.fRadius)
		return true;

	return false;

}

bool CCollider::CollisionRectToPoint(const RECTINFO& tRC, const POSITION& tPos)
{
	if (tRC.l > tPos.x)
		return false;

	else if (tRC.r < tPos.x)
		return false;
	else if (tRC.t > tPos.y)
		return false;
	else if (tRC.b < tPos.y)
		return false;

	return true;

}
bool CCollider::CollisionPointToPoint(const POSITION& tSrc, const POSITION& tDest)
{
	return tSrc.x == tDest.x && tSrc.y == tDest.y;
}

bool CCollider::CollisionSphereToPoint(const SPHEREINFO& tSphere, const POSITION& tPos)
{
	return CMath::GetDistance(tSphere.tCenter, tPos) <= tSphere.fRadius;
}

bool CCollider::CollisionRectToPixel(const RECTINFO& tRC, const PIXELINFO& tPixel)
{
	//렉트의 크기만큼 반복하며 충돌처리한다.
	RECTINFO tRCInfo = tRC;
	tRCInfo.l -= tPixel.tWorldPos.x;
	tRCInfo.r -= tPixel.tWorldPos.x;
	tRCInfo.t -= tPixel.tWorldPos.y;
	tRCInfo.b -= tPixel.tWorldPos.y;

	unsigned char* pPixel = (unsigned char*)tPixel.pPixel;

	if (tRCInfo.l <= tPixel.iWidth && 0 <= tRCInfo.r &&
		tRCInfo.t <= tPixel.iHeight && 0 <= tRCInfo.b)
	{
		int iStartX, iStartY, iEndX, iEndY;
		iStartX = tRCInfo.l < 0.f ? 0 : tRCInfo.l;
		iStartY = tRCInfo.t < 0.f ? 0 : tRCInfo.t;
		iEndX = tRCInfo.r >= tPixel.iWidth ? tPixel.iWidth : tRCInfo.r;
		iEndY = tRCInfo.b >= tPixel.iHeight ? tPixel.iHeight : tRCInfo.b;

		for (int i = iStartY; i < iEndY; ++i)
		{
			for (int j = iStartX; j < iEndX; ++j)
			{
				int iIndex = (i * tPixel.iWidth + j) * tPixel.iPixelSize;
				if (pPixel[iIndex] == tPixel.tCollisionPixel.r &&
					pPixel[iIndex + 1] == tPixel.tCollisionPixel.g &&
					pPixel[iIndex + 2] == tPixel.tCollisionPixel.b)
					return true;
			}
		}
	}
	return false;
}

void CCollider::OnCollisionEnter(CCollider* pDest, float fTime)
{
	list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
	list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_Callback[CCT_ENTER].end();

	for (iter = m_Callback[CCT_ENTER].begin(); iter != iterEnd; ++iter)
	{
		(*iter)(this, pDest, fTime);
	}
}

void CCollider::OnCollision(CCollider* pDest, float fTime)
{
	list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
	list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_Callback[CCT_STAY].end();

	for (iter = m_Callback[CCT_STAY].begin(); iter != iterEnd; ++iter)
	{
		(*iter)(this, pDest, fTime);
	}
}

void CCollider::OnCollisionLeave(CCollider* pDest, float fTime)
{
	list<function<void(CCollider*, CCollider*, float)>>::iterator iter;
	list<function<void(CCollider*, CCollider*, float)>>::iterator iterEnd = m_Callback[CCT_LEAVE].end();

	for (iter = m_Callback[CCT_LEAVE].begin(); iter != iterEnd; ++iter)
	{
		(*iter)(this, pDest, fTime);
	}
}