#pragma once
#include"Character.h"
class CNPC : 
	public CCharacter
{
	friend class CObj;

protected:
	CNPC();
	CNPC(const CNPC* npc);
	~CNPC();

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CNPC* Clone();
};