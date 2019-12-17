#pragma once
#include"Obj.h"
class CUI :
	public CObj
{
	friend class CObj;

protected:
	CUI();
	CUI(const CUI& ui);
	~CUI();

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CUI* Clone() = 0;
};