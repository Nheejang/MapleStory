#pragma once
#include"Obj.h"
class CMouse :
	public CObj
{
	friend class CObj;
	friend class CInput;

protected:
	CMouse();
	CMouse(const CMouse& mouse);
	~CMouse();

private:
	bool m_bLClick;
	bool m_bRClick;
	bool m_bMClick;

public:
	bool GetLButton() const;
	bool GetRButton() const;
	bool GetMButton() const;

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CMouse* Clone();
};