#pragma once

#include "Ref.h"

class CSceneComponent :
	public CRef
{
	friend class CScene;

protected:
	CSceneComponent();
	virtual ~CSceneComponent() = 0;

protected:
	class CScene* m_pScene;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

public:
	virtual bool Init() = 0;
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
};

