#include "Scene.h"
#include "Layer.h"
#include "Obj.h"
#include"SceneComponent.h"
CScene::CScene() :
	m_pSceneComponent(nullptr)
{
}

CScene::~CScene()
{
	CObj::EraseSceneObject(this);
	CObj::EraseFindList();
	CObj::ErasePrototype(this);
	SAFE_RELEASE(m_pSceneComponent);
	Safe_Release_VecList(m_LayerList);
}

CLayer* CScene::CreateLayer(const string& strTag, int iZOrder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetScene(this);
	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);

	if (!pLayer->Init())
	{
		SAFE_RELEASE(pLayer);
		return nullptr;
	}

	// �⺻ ������ RefCount�� 1�̰� ���⼭ Add�� ���ָ� 2�� �ȴ�.
	pLayer->AddRef();
	m_LayerList.push_back(pLayer);

	// ���̾ 2�� �̻� �߰��Ǿ��� ��� �����Ѵ�.
	if (m_LayerList.size() >= 2)
	{
		m_LayerList.sort(CScene::LayerSort);
	}

	return pLayer;
}

CLayer* CScene::FindLayer(const string& strTag)
{
	list<CLayer*>::iterator	iter;
	list<CLayer*>::iterator	iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetTag() == strTag)
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

bool CScene::Init()
{
	// �⺻ ���̾� ����
	CLayer* pLayer = CreateLayer("BackGround", INT_MIN);

	SAFE_RELEASE(pLayer);

	pLayer = CreateLayer("UI", INT_MAX);

	SAFE_RELEASE(pLayer);

	pLayer = CreateLayer("Default", 0);

	SAFE_RELEASE(pLayer);

	return true;
}

int CScene::Input(float fTime)
{
	m_pSceneComponent->Input(fTime);

	list<CLayer*>::iterator	iter;
	list<CLayer*>::iterator	iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			SAFE_RELEASE((*iter));
			// ����Ʈ���� �����ش�. �����ְ� �Ǹ� ���� iterator�� ����
			// iterator �� ��ȯ�Ѵ�.
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
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

int CScene::Update(float fTime)
{
	m_pSceneComponent->Update(fTime);

	list<CLayer*>::iterator	iter;
	list<CLayer*>::iterator	iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			SAFE_RELEASE((*iter));
			// ����Ʈ���� �����ش�. �����ְ� �Ǹ� ���� iterator�� ����
			// iterator �� ��ȯ�Ѵ�.
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
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

int CScene::LateUpdate(float fTime)
{
	m_pSceneComponent->LateUpdate(fTime);

	list<CLayer*>::iterator	iter;
	list<CLayer*>::iterator	iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			SAFE_RELEASE((*iter));
			// ����Ʈ���� �����ش�. �����ְ� �Ǹ� ���� iterator�� ����
			// iterator �� ��ȯ�Ѵ�.
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
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

void CScene::Render(HDC hDC, float fTime)
{
	m_pSceneComponent->Render(hDC, fTime);

	list<CLayer*>::iterator	iter;
	list<CLayer*>::iterator	iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			SAFE_RELEASE((*iter));
			// ����Ʈ���� �����ش�. �����ְ� �Ǹ� ���� iterator�� ����
			// iterator �� ��ȯ�Ѵ�.
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
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

bool CScene::LayerSort(CLayer* pSrc, CLayer* pDest)
{
	return pSrc->m_iZOrder < pDest->m_iZOrder;
}
