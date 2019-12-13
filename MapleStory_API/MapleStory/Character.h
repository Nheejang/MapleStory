#pragma once
#include"Obj.h"

class CCharacter :
	public CObj
{
protected:
	CCharacter();
	CCharacter(const CCharacter& character);
	virtual ~CCharacter();

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CCharacter* Clone() = 0;
};