#include "Layer.h"
#include "Obj.h"


CLayer::CLayer() :
	m_pScene(nullptr),
	m_iZOrder(0)
{
}

CLayer::~CLayer()
{
	Safe_Release_VecList(m_ObjList);
}

void CLayer::AddObject(CObj* pObj)
{
	pObj->SetScene(m_pScene);
	pObj->SetLayer(this);
	pObj->AddRef();

	m_ObjList.push_back(pObj);
}

void CLayer::EraseObject(CObj* pObj)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		if (*iter == pObj)
		{
			SAFE_RELEASE((*iter));
			m_ObjList.erase(iter);
			return;
		}
	}
}

bool CLayer::Init()
{
	return true;
}

int CLayer::Input(float fTime)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			CObj::EraseSceneObject((*iter)->GetTag(), *iter);
			SAFE_RELEASE((*iter));
			// 리스트에서 지워준다. 지워주게 되면 지운 iterator의 다음
			// iterator 를 반환한다.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Input(fTime);

		++iter;
	}

	return 0;
}

int CLayer::Update(float fTime)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			CObj::EraseSceneObject((*iter)->GetTag(), *iter);
			SAFE_RELEASE((*iter));
			// 리스트에서 지워준다. 지워주게 되면 지운 iterator의 다음
			// iterator 를 반환한다.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(fTime);

		++iter;
	}

	return 0;
}

int CLayer::LateUpdate(float fTime)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			CObj::EraseSceneObject((*iter)->GetTag(), *iter);
			SAFE_RELEASE((*iter));
			// 리스트에서 지워준다. 지워주게 되면 지운 iterator의 다음
			// iterator 를 반환한다.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fTime);

		++iter;
	}

	return 0;
}

void CLayer::Collision(float fTime)
{

}
void CLayer::Render(HDC hDC, float fTime)
{
	list<CObj*>::iterator	iter;
	list<CObj*>::iterator	iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			CObj::EraseSceneObject((*iter)->GetTag(), *iter);
			SAFE_RELEASE((*iter));
			// 리스트에서 지워준다. 지워주게 되면 지운 iterator의 다음
			// iterator 를 반환한다.
			iter = m_ObjList.erase(iter);
			iterEnd = m_ObjList.end();
			continue;
		}

		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render(hDC, fTime);

		++iter;
	}

}
