#pragma once

#include"Collider.h"

class CCollisionManager
{
private:
	typedef struct _tagCollisionGroup
	{
		string strName;
		CCollider** pList;
		int iCapacity; //전체 배열 크기
		int iSize;//채워진 크기

		_tagCollisionGroup() :
			iCapacity(100),
			iSize(0)
		{
			pList = new CCollider * [iCapacity];
		}

		~_tagCollisionGroup()
		{
			SAFE_DELETE_ARRAY(pList);
		}
	}COLLISIONGROUP,*PCOLLISIONGROUP;

private:
	unordered_map<string, PCOLLISIONGROUP>m_mapGroup;

public:
	bool CreateCollisionGroup(const string& strGroup);
	PCOLLISIONGROUP FindCollisionGroup(const string& strGroup);
	void AddCollider(class CObj* pObj);

public:
	bool Init();
	void Collision(float fTime);

	DECLARE_SINGLE(CCollisionManager)
};