#pragma once

#include "Ref.h"

class CScene :
	public CRef
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	list<class CLayer*>	m_LayerList;
	class CSceneComponent* m_pSceneComponent;
	int MyClientID = 0;

public:
	class CLayer* CreateLayer(const string& strTag, int iZOrder = 0);
	class CLayer* FindLayer(const string& strTag);
	class CSceneComponent* GetCurrentComponent();
public:
	bool Init();
	int Input(float fTime);
	int Update(float fTime);
	int LateUpdate(float fTime);
	void Render(HDC hDC, float fTime);

private:
	static bool LayerSort(class CLayer* pSrc, class CLayer* pDest);

public:
	template <typename T>
	T* CreateSceneComponent(const string& strTag)
	{
		T* pCom = new T;

		pCom->SetTag(strTag);
		pCom->SetScene(this);

		if (!pCom->Init())
		{
			SAFE_RELEASE(pCom);
			return nullptr;
		}

		pCom->AddRef();
		m_pSceneComponent = pCom;

		return pCom;
	}
};

