#pragma once
#include"Character.h"

class CMonster :
	public CCharacter
{
	friend class CObj;

protected:
	CMonster();
	CMonster(const CMonster& monster);
	~CMonster();

private:
	//int m_iMoveDir;
//	float m_fFireTime;
//	float m_fTraceRange;
//	float m_fAttackRange;
	CObj* m_pTarget;

public:
	void SetTarget(CObj* pTarget)
	{
		SAFE_RELEASE(m_pTarget);
		m_pTarget = pTarget;
		if (m_pTarget)
			m_pTarget->AddRef();
	}

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CMonster* Clone();

};