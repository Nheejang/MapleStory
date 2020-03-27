#pragma once
#include"Collider.h"
class CColliderRect :
	public CCollider
{
	friend class CObj;
	friend class CCollisionManager;

private:
	CColliderRect();
	CColliderRect(const CColliderRect& coll);
	~CColliderRect();

private:
	RECTINFO m_tRelative;
	RECTINFO m_tWorldInfo;
	_SIZE m_tSize;
	HBRUSH m_hBrush;
	HBRUSH m_hGreenBrush;
	HBRUSH m_hRedBrush;
	HBRUSH m_hOldBrush;

public:
	void MoveWorldInfo(float x, float y)
	{
		m_tWorldInfo.l += x;
		m_tWorldInfo.r += x;
		m_tWorldInfo.t += y;
		m_tWorldInfo.b += y;
	}

	void SetInfo(const RECTINFO& tInfo)
	{
		m_tRelative = tInfo;
		m_tSize.x = tInfo.r - tInfo.l;
		m_tSize.y = tInfo.b - tInfo.t;
	}

	void SetInfo(const _SIZE& tSize)
	{
		m_tRelative.r = tSize.x;
		m_tRelative.b = tSize.y;

		m_tSize = tSize;
	}

	void SetInfo(float fWidth, float fHeight)
	{
		m_tSize = _SIZE(fWidth, fHeight);

		m_tRelative.r = m_tSize.x;
		m_tRelative.b = m_tSize.y;
	}

public:
	RECTINFO GetInfo() const
	{
		return m_tWorldInfo;
	}

public:
	virtual bool Init();
	virtual int Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CColliderRect* Clone()const;
	virtual bool Collision(CCollider* pDest);
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};