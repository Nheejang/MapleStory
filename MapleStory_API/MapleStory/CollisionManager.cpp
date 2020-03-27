#include"CollisionManager.h"
#include"Obj.h"
#include"Input.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{

}
CCollisionManager::~CCollisionManager()
{
	Safe_Delete_Map(m_mapGroup);
}

bool CCollisionManager::CreateCollisionGroup(const string& strGroup)
{
	PCOLLISIONGROUP pGroup = FindCollisionGroup(strGroup);

	if (pGroup)
		return false;

	pGroup = new COLLISIONGROUP;

	m_mapGroup.insert(make_pair(strGroup, pGroup));

	return true;
}

CCollisionManager::PCOLLISIONGROUP CCollisionManager::FindCollisionGroup(const string& strGroup)
{
	unordered_map<string, PCOLLISIONGROUP>::iterator iter = m_mapGroup.find(strGroup);

	if (iter == m_mapGroup.end())
		return nullptr;

	return iter->second;
}

void CCollisionManager::AddCollider(CObj* pObj)
{
	const list<CCollider*>* pColliderList = pObj->GetColliderList();

	if (pColliderList->empty())
		return;

	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = pColliderList->end();

	for (iter = pColliderList->begin(); iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsEnable())
		{
			(*iter)->DeletePrevCollider();
			continue;
		}

		PCOLLISIONGROUP pGroup = FindCollisionGroup((*iter)->GetCollisionGroup());

		if (!pGroup)
			continue;

		if (pGroup->iSize == pGroup->iCapacity)
		{
			pGroup->iCapacity *= 2;
			CCollider** pList = new CCollider * [pGroup->iCapacity];

			memcpy(pList, pGroup->pList, sizeof(CCollider*) * pGroup->iSize);
			SAFE_DELETE_ARRAY(pGroup->pList);

			pGroup->pList = pList;
		}

		pGroup->pList[pGroup->iSize] = *iter;
		++pGroup->iSize;
	}
}

bool CCollisionManager::Init()
{
	CreateCollisionGroup("Default");
	CreateCollisionGroup("UI");

	return true;
}

void CCollisionManager::Collision(float fTime)
{
	//마우스 대 UI를 먼저 충돌해서 UI가 충돌될경우 마우스와 월드공간의 오브젝트와의
	//충돌처리를 안한다.
	bool bCollision = false;

	//마우스 월드공간 충돌체를 얻어온다.
	CObj* pMouseObj = (CObj*)GET_SINGLE(CInput)->GetMouseObj();
	CCollider* pMouse = pMouseObj->GetCollider("MouseUI");

	CCollider* pMouseWorld = pMouseObj->GetCollider("Mouse");

	PCOLLISIONGROUP pCollGroup = FindCollisionGroup("UI");

	if (pCollGroup)
	{
		for (int i = 0; i < pCollGroup->iSize; ++i)
		{
			if (bCollision)
				break;

			CCollider* pDest = pCollGroup->pList[i];

			//충돌 됬을 경우
			if (pMouse->Collision(pDest))
			{

				bCollision = true;
				pDest->SetIntersectPos(pMouse->GetIntersectPosition());

				//이전에 충돌했던 목록에 Dest가 없다면 처음 충돌한다는 것
				if (!pMouse->CheckPrevCollider(pDest))
				{
					//기존에 마우스와 충돌됐던 다른 오브젝트들은 모두 Leave처리한다.
					pMouseWorld->DeletePrevCollider();

					pMouse->AddPrevCollider(pDest);
					pDest->AddPrevCollider(pMouse);

					pMouse->OnCollisionEnter(pDest, fTime);
					pDest->OnCollisionEnter(pMouse, fTime);
				}
				else
				{
					pMouse->OnCollision(pDest, fTime);
					pDest->OnCollision(pMouse, fTime);
				}
			}

			//충돌 안됐을 경우
			else
			{

				//충돌이 안될때 만약 이전 충돌목록에 상대가 존재한다면
				//충돌하다가 떨어진다는 것이다.
				if (pMouse->CheckPrevCollider(pDest))
				{

					pMouse->DeletePrevCollider(pDest);
					pDest->DeletePrevCollider(pMouse);

					pMouse->OnCollisionLeave(pDest, fTime);
					pDest->OnCollisionLeave(pMouse, fTime);
				}
			}

		}
	}

	SAFE_RELEASE(pMouse);

	//마우스와 일반 오브젝트 충돌처리. 여기서는 UI와 충돌이 안됐을때만 처리한다.
	if (!bCollision)
	{
		unordered_map<string, PCOLLISIONGROUP>::iterator iter;
		unordered_map<string, PCOLLISIONGROUP>::iterator iterEnd = m_mapGroup.end();

		for (iter = m_mapGroup.begin(); iter != iterEnd; ++iter)
		{
			if (iter->first == "UI")
				continue;

			pCollGroup = iter->second;

			for (int i = 0; i < pCollGroup->iSize; ++i)
			{
				if (bCollision)
					break;

				CCollider* pDest = pCollGroup->pList[i];

				//충돌 됐을 경우
				if (pMouseWorld->Collision(pDest))
				{
					bCollision = true;
					pDest->SetIntersectPos(pMouseWorld->GetIntersectPosition());

					//이전에 충돌됐던 목록에 Dest가 없다면 처음 충돌한다.
					if (!pMouseWorld->CheckPrevCollider(pDest))
					{
						pMouseWorld->AddPrevCollider(pDest);
						pDest->AddPrevCollider(pMouseWorld);

						pMouseWorld->OnCollisionEnter(pDest, fTime);
						pDest->OnCollisionEnter(pMouseWorld, fTime);
					}
					else
					{
						pMouseWorld->OnCollision(pDest, fTime);
						pDest->OnCollision(pMouseWorld, fTime);
					}
				}

				//충돌 안됐을 경우
				else
				{

					//충돌이 안될때 만약 이전 충돌목록에 상대가 존재한다면
					//충돌 하다가 떨어진다는 것
					if (pMouseWorld->CheckPrevCollider(pDest))
					{
						pMouseWorld->DeletePrevCollider(pDest);
						pDest->DeletePrevCollider(pMouseWorld);

						pMouseWorld->OnCollisionLeave(pDest, fTime);
						pDest->OnCollisionLeave(pMouseWorld, fTime);
					}

				}
			}
		}
	}
	SAFE_RELEASE(pMouseWorld);
	SAFE_RELEASE(pMouse);

	unordered_map<string,PCOLLISIONGROUP>::iterator iter;
	unordered_map<string, PCOLLISIONGROUP>::iterator iterEnd = m_mapGroup.end();

	for (iter = m_mapGroup.begin(); iter != iterEnd; ++iter)
	{

		//실제충돌체 수만큼 반복. 단,충돌체 수가 1개 이하일 경우 충돌처리 안해도됨
		PCOLLISIONGROUP pGroup = iter->second;
		if (pGroup->iSize < 2)
		{
			pGroup->iSize = 0;
			continue;
		}

		for (int i = 0; i < pGroup->iSize - 1; ++i)
		{
			CCollider* pSrc = pGroup->pList[i];
			CObj* pSrcObj = pSrc->GetObj();

			for (int j = i + 1; j < pGroup->iSize; ++j)
			{
				//충돌처리를 한다. 단, 같은 오브젝트에 속해있는 충돌체끼리는 처리하지않는다.

				CCollider* pDest = pGroup->pList[j];

				if (pSrc->GetCollisionType() == pDest->GetCollisionType())
					continue;

				//충돌체를 가지고 있는 오브젝트를 얻어온다.
				CObj* pDestObj = pDest->GetObj();

				if (pSrcObj == pDestObj)
				{
					SAFE_RELEASE(pDestObj);
					continue;
				}

				SAFE_RELEASE(pDestObj);

				//충돌 됐을 경우
				if (pSrc->Collision(pDest))
				{
					pDest->SetIntersectPos(pSrc->GetIntersectPosition());

					//이전에 충돌했던 목록에 Dest가 없다면 처음 충돌한다는 것.
					if (!pSrc->CheckPrevCollider(pDest))
					{
						pSrc->AddPrevCollider(pDest);
						pDest->AddPrevCollider(pSrc);

						pSrc->OnCollisionEnter(pDest, fTime);
						pDest->OnCollisionEnter(pSrc, fTime);
					}

					else
					{
						pSrc->OnCollision(pDest, fTime);
						pDest->OnCollision(pSrc, fTime);
					}

				}

				//충돌 안됐을 경우
				else
				{
					//충돌이 안될때 만약 이전충돌목록에 상대가 존재한다면
					//충돌하다가 떨어진다는 것이다.
					if (pSrc->CheckPrevCollider(pDest))
					{
						pSrc->DeletePrevCollider(pDest);
						pDest->DeletePrevCollider(pSrc);

						pSrc->OnCollisionLeave(pDest, fTime);
						pDest->OnCollisionLeave(pSrc, fTime);
					}
				}
			}

			SAFE_RELEASE(pSrcObj);
		}

		pGroup->iSize = 0;
	}
}