#pragma once
#include"Obj.h"

class CEffect :
	public CObj
{
	friend class CObj;

protected:
	CEffect();
	CEffect(const CEffect& effect);
	~CEffect();

private:
	float m_fRange;
	CObj* m_pTarget;
	float m_fActiveTime;

public:
	void SetTarget(CObj* pTarget)
	{
		SAFE_RELEASE(m_pTarget);
		m_pTarget = pTarget;
		if (m_pTarget)
			m_pTarget->AddRef();
	}

	void SetRange(float fRange)
	{
		m_fRange = fRange;
	}

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CEffect* Clone();
};