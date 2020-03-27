#pragma once

#include "Ref.h"

class CCollider :
	public CRef
{
	friend class CObj;
	friend class CCollisionManager;

protected:
	CCollider();
	CCollider(const CCollider& coll);
	virtual ~CCollider() = 0;

protected:
	COLLIDER_TYPE  m_eCollType;
	POSITION m_tPivot;
	class CObj* m_pObj;
	string m_strGroup;
	list<function<void(CCollider*, CCollider*, float)>>m_Callback[CCT_END];
	list<CCollider*> m_PrevCollider;//이전에 충돌했던 목록
	string m_strCollisionType;
	POSITION m_tIntersect;
	bool m_bUI;

public:

	POSITION GetIntersectPosition() const
	{
		return m_tIntersect;
	}

	bool GetUI() const
	{
		return m_bUI;
	}

public:
	void SetUI(bool bUI)
	{
		m_bUI = bUI;
	}
	void SetIntersectPos(const POSITION& tPos)
	{
		m_tIntersect = tPos;
	}

	void SetCollisionType(const string& strType)
	{
		m_strCollisionType = strType;
	}

	void AddPrevCollider(CCollider* pCollider)
	{
		m_PrevCollider.push_back(pCollider);
	}

	void DeletePrevCollider()
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_PrevCollider.end();

		for (iter = m_PrevCollider.begin(); iter != iterEnd; ++iter)
		{
			(*iter)->DeletePrevCollider(this);
			OnCollisionLeave(*iter, 0.f);
			(*iter)->OnCollisionLeave(this, 0.f);
		}
		m_PrevCollider.clear();
	}

	void DeletePrevCollider(CCollider* pCollider)
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_PrevCollider.end();

		for (iter = m_PrevCollider.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider)
			{
				m_PrevCollider.erase(iter);
				return;
			}
		}
	}

	bool CheckPrevCollider(CCollider* pCollider)
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_PrevCollider.end();

		for (iter = m_PrevCollider.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pCollider)
				return true;
		}
		return false;
	}

public:
	string GetCollisionType() const;
	COLLIDER_TYPE GetColliderType() const;
	string GetCollisionGroup() const
	{
		return m_strGroup;
	}
	class CObj* GetObj() const;


public:
	void SetCollisionGroup(const string& strGroup)
	{
		m_strGroup = strGroup;
	}

	void SetObj(class CObj* pObj)
	{
		m_pObj = pObj;
	}

	void SetPivot(const POSITION& tPivot)
	{
		m_tPivot = tPivot;
	}
	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

public:
	virtual bool Init();
	virtual int Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CCollider* Clone() const;
	virtual bool Collision(CCollider* pDest) = 0;
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

protected:
	bool CollisionRectToRect(const RECTINFO& tSrc, const RECTINFO& tDest);
	bool CollisionSphereToSphere(const SPHEREINFO& tSrc, const SPHEREINFO& tDest);
	bool CollisionRectToSphere(const RECTINFO& tRC, const SPHEREINFO& tSphere);
	bool CollisionRectToPoint(const RECTINFO& tRC, const POSITION& tPos);
	bool CollisionPointToPoint(const POSITION& tSrc, const POSITION& tDest);
	bool CollisionSphereToPoint(const SPHEREINFO& tSphere, const POSITION& tPos);
	bool CollisionRectToPixel(const RECTINFO& tRC, const PIXELINFO& tPixel);

public:
	void OnCollisionEnter(CCollider* pDest, float fTime);
	void OnCollision(CCollider* pDest, float fTime);
	void OnCollisionLeave(CCollider* pDest, float fTime);

public:
	void SetCallback(void(*pFunc)(CCollider*, CCollider*, float), COLLISION_CALLBACK_TYPE eType)
	{
		m_Callback[eType].push_back(bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3));
	}

	template<typename T>
	void SetCallback(T* pObj, void(T::* pFunc)(CCollider*, CCollider*, float),
		COLLISION_CALLBACK_TYPE eType)
	{
		m_Callback[eType].push_back(bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3));
	}
};