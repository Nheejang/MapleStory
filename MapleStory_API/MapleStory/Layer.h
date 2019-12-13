#pragma once

#include "Ref.h"

class CLayer :
	public CRef
{
	friend class CScene;

private:
	CLayer();
	~CLayer();

private:
	class CScene* m_pScene;
	int				m_iZOrder;
	list<class CObj*>	m_ObjList;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

public:
	void AddObject(class CObj* pObj);
	void EraseObject(class CObj* pObj);

public:
	bool Init();
	int Input(float fTime);
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Collision(float fTime);
	void Render(HDC hDC, float fTime);
};

