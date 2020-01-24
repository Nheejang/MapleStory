#pragma once
#include"Character.h"

class CPlayer :
	public CCharacter
{
	friend class CObj;

protected:
	CPlayer();
	CPlayer(const CPlayer& player);
	~CPlayer();

public:
	int id = -1;
public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC,float fTime);
	virtual CPlayer* Clone();
};