#pragma once
#include"Obj.h"

class CBackGround :
	public CObj
{
	friend class CObj;

protected:
	 CBackGround();
	 CBackGround(CBackGround& back);
	 virtual ~CBackGround();



public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CBackGround* Clone();
};