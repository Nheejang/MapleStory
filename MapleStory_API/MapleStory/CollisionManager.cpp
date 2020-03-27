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
	//���콺 �� UI�� ���� �浹�ؼ� UI�� �浹�ɰ�� ���콺�� ��������� ������Ʈ����
	//�浹ó���� ���Ѵ�.
	bool bCollision = false;

	//���콺 ������� �浹ü�� ���´�.
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

			//�浹 ���� ���
			if (pMouse->Collision(pDest))
			{

				bCollision = true;
				pDest->SetIntersectPos(pMouse->GetIntersectPosition());

				//������ �浹�ߴ� ��Ͽ� Dest�� ���ٸ� ó�� �浹�Ѵٴ� ��
				if (!pMouse->CheckPrevCollider(pDest))
				{
					//������ ���콺�� �浹�ƴ� �ٸ� ������Ʈ���� ��� Leaveó���Ѵ�.
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

			//�浹 �ȵ��� ���
			else
			{

				//�浹�� �ȵɶ� ���� ���� �浹��Ͽ� ��밡 �����Ѵٸ�
				//�浹�ϴٰ� �������ٴ� ���̴�.
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

	//���콺�� �Ϲ� ������Ʈ �浹ó��. ���⼭�� UI�� �浹�� �ȵ������� ó���Ѵ�.
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

				//�浹 ���� ���
				if (pMouseWorld->Collision(pDest))
				{
					bCollision = true;
					pDest->SetIntersectPos(pMouseWorld->GetIntersectPosition());

					//������ �浹�ƴ� ��Ͽ� Dest�� ���ٸ� ó�� �浹�Ѵ�.
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

				//�浹 �ȵ��� ���
				else
				{

					//�浹�� �ȵɶ� ���� ���� �浹��Ͽ� ��밡 �����Ѵٸ�
					//�浹 �ϴٰ� �������ٴ� ��
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

		//�����浹ü ����ŭ �ݺ�. ��,�浹ü ���� 1�� ������ ��� �浹ó�� ���ص���
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
				//�浹ó���� �Ѵ�. ��, ���� ������Ʈ�� �����ִ� �浹ü������ ó�������ʴ´�.

				CCollider* pDest = pGroup->pList[j];

				if (pSrc->GetCollisionType() == pDest->GetCollisionType())
					continue;

				//�浹ü�� ������ �ִ� ������Ʈ�� ���´�.
				CObj* pDestObj = pDest->GetObj();

				if (pSrcObj == pDestObj)
				{
					SAFE_RELEASE(pDestObj);
					continue;
				}

				SAFE_RELEASE(pDestObj);

				//�浹 ���� ���
				if (pSrc->Collision(pDest))
				{
					pDest->SetIntersectPos(pSrc->GetIntersectPosition());

					//������ �浹�ߴ� ��Ͽ� Dest�� ���ٸ� ó�� �浹�Ѵٴ� ��.
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

				//�浹 �ȵ��� ���
				else
				{
					//�浹�� �ȵɶ� ���� �����浹��Ͽ� ��밡 �����Ѵٸ�
					//�浹�ϴٰ� �������ٴ� ���̴�.
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