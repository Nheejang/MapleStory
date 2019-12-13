#pragma once
#include "SceneComponent.h"
class CtestScene :
	public CSceneComponent
{
	friend class CScene;

private:
	CtestScene();
	~CtestScene();

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);

public:

};

