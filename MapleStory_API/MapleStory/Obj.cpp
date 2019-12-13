#include "Obj.h"
#include "Layer.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Math.h"

#include "Camera.h"
#include "PathManager.h"

unordered_map<string, class CObj*> CObj::m_mapPrototype;
unordered_multimap<string, class CObj*> CObj::m_mapSceneObj;
list<CObj*>	CObj::m_FindList;

CObj* CObj::FindPrototype(const string& strKey)
{
	unordered_map<string, class CObj*>::iterator	iter = m_mapPrototype.find(strKey);

	if (iter == m_mapPrototype.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

CObj* CObj::CreateCloneObject(const string& strTag, CLayer* pLayer)
{
	CObj* pPrototype = FindPrototype(strTag);

	if (!pPrototype)
		return nullptr;

	CObj* pObj = pPrototype->Clone();

	SAFE_RELEASE(pPrototype);

	if (pLayer)
		pLayer->AddObject(pObj);

	pObj->AddRef();
	m_mapSceneObj.insert(make_pair(strTag, pObj));

	return pObj;
}

void CObj::ErasePrototype(CScene* pScene)
{
	unordered_map<string, class CObj*>::iterator	iter;
	unordered_map<string, class CObj*>::iterator	iterEnd = m_mapPrototype.end();

	for (iter = m_mapPrototype.begin(); iter != iterEnd;)
	{
		if (iter->second->m_pScene == pScene)
		{
			SAFE_RELEASE(iter->second);
			iter = m_mapPrototype.erase(iter);
			iterEnd = m_mapPrototype.end();
		}

		else
			++iter;
	}
}

void CObj::EraseSceneObject(CScene* pScene)
{
	unordered_multimap<string, class CObj*>::iterator	iter;
	unordered_multimap<string, class CObj*>::iterator	iterEnd = m_mapSceneObj.end();

	for (iter = m_mapSceneObj.begin(); iter != iterEnd;)
	{
		if (iter->second->m_pScene == pScene)
		{
			SAFE_RELEASE(iter->second);
			iter = m_mapSceneObj.erase(iter);
			iterEnd = m_mapSceneObj.end();
		}

		else
			++iter;
	}
}

void CObj::EraseSceneObject(const string& strKey, CObj* pObj)
{
	auto pair = m_mapSceneObj.equal_range(strKey);

	unordered_multimap<string, class CObj*>::iterator	iter = pair.first;
	unordered_multimap<string, class CObj*>::iterator	iterEnd = pair.second;

	while (iter != iterEnd)
	{
		if (iter->second == pObj)
		{
			SAFE_RELEASE(pObj);
			m_mapSceneObj.erase(iter);
			break;
		}

		++iter;
	}
}

void CObj::EraseFindList()
{
	Safe_Release_VecList(m_FindList);
}

CObj* CObj::FindObject(const string& strKey)
{
	unordered_multimap<string, class CObj*>::iterator	iter = m_mapSceneObj.find(strKey);

	if (iter == m_mapSceneObj.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

const list<CObj*>* CObj::FindObjects(const string& strKey)
{
	EraseFindList();

	/*pair<unordered_multimap<string, class CObj*>::iterator,
		unordered_multimap<string, class CObj*>::iterator> pair =
		m_mapSceneObj.equal_range(strKey);*/
		// auto : 무조건 선언과 동시에 초기화 해야 한다. 지정하는 값 타입으로 변수타입이 설정된다.
		// 중간에 다른값을 넣으면 안된다.
	auto pair = m_mapSceneObj.equal_range(strKey);

	unordered_multimap<string, class CObj*>::iterator	iter = pair.first;
	unordered_multimap<string, class CObj*>::iterator	iterEnd = pair.second;

	while (iter != iterEnd)
	{
		iter->second->AddRef();
		m_FindList.push_back(iter->second);
		++iter;
	}

	return &m_FindList;
}

CObj::CObj() :
	m_pTexture(nullptr),
	m_fAngle(0.f),
	m_fMoveSpeed(0.f),
	m_fRotSpeed(0.f),
	m_dwColorKey(0),
	m_bColorKey(false),
	m_bGravity(false),
	m_fForce(0.f),
	m_fForceOrigin(0.f),
	m_fGravityTime(0.f),
	m_bCameraEnable(true)
{
}

CObj::CObj(const CObj& obj)
{
	*this = obj;
	m_iRefCount = 1;

	if (m_pTexture)
		m_pTexture->AddRef();

	
}


CObj::~CObj()
{

	SAFE_RELEASE(m_pTexture);
}

CScene* CObj::GetScene() const
{
	if (m_pScene)
		m_pScene->AddRef();
	return m_pScene;
}

CLayer* CObj::GetLayer() const
{
	if (m_pLayer)
		m_pLayer->AddRef();
	return m_pLayer;
}


bool CObj::SetTexture(const string& strKey, const TCHAR* pFileName, const string& strPathKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, pFileName, strPathKey);

	return true;
}

bool CObj::SetTexture(const string& strKey)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strKey);

	return true;
}

bool CObj::SetTexture(CTexture* pTexture)
{
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;

	if (m_pTexture)
		m_pTexture->AddRef();

	return true;
}



void CObj::Move(float x, float y)
{
	m_tMove += POSITION(x, y);
	m_tPos.x += x;
	m_tPos.y += y;
}

void CObj::Move(float x, float y, float fTime)
{
	m_tMove += (POSITION(x, y) * fTime);
	m_tPos.x += x * fTime;
	m_tPos.y += y * fTime;
}

void CObj::Move(const POSITION& tDir)
{
	m_tMove += tDir;
	m_tPos += tDir;
}

void CObj::Move(const POSITION& tDir, float fTime)
{
	m_tMove += tDir * fTime;
	m_tPos += tDir * fTime;
}

void CObj::MoveByAngle(float fTime)
{
	m_tMove.x += cosf(CMath::DegreeToRadian(m_fAngle)) * m_fMoveSpeed * fTime;
	m_tMove.y += sinf(CMath::DegreeToRadian(m_fAngle)) * m_fMoveSpeed * fTime;

	m_tPos.x += cosf(CMath::DegreeToRadian(m_fAngle)) * m_fMoveSpeed * fTime;
	m_tPos.y += sinf(CMath::DegreeToRadian(m_fAngle)) * m_fMoveSpeed * fTime;
}

void CObj::Rotation(float fTime)
{
	m_fAngle += m_fRotSpeed * fTime;
}

bool CObj::Init()
{
	return true;
}

int CObj::Input(float fTime)
{
	return 0;
}

int CObj::Update(float fTime)
{
	if (m_bGravity)
	{
		m_fGravityTime += fTime;

		m_fForce -= GRAVITY * m_fGravityTime * m_fGravityTime;
		m_tPos.y -= m_fForce * fTime;
		m_tMove.y -= m_fForce * fTime;
	}

	
	return 0;
}

int CObj::LateUpdate(float fTime)
{
	

	return 0;
}

void CObj::Collision(float fTime)
{

}

void CObj::Render(HDC hDC, float fTime)
{
	if (m_pTexture)
	{
		POSITION	tCameraPos = GET_SINGLE(CCamera)->GetPos();

		POSITION	tLT = m_tPos - m_tSize * m_tPivot;

		if (m_bCameraEnable)
			tLT -= tCameraPos;

		int	iFrameX = 0, iFrameY = 0;
		_SIZE	tSize = m_tSize;

		

		iFrameX += m_tOffset.x;
		iFrameY += m_tOffset.y;

		if (!m_bColorKey)
		{
			// BitBlt : 이미지를 출력해주는 함수이다.
			// 1번인자 : 어디 출력할지 DC를 지정한다.
			// 2번, 3번인자 : 1번인자에 지정한 DC에서 어느 위치에 출력할지
			// 좌표를 지정한다.
			// 4번, 5번인자 : 1번인자에 지정한 DC에 출력할 크기를 지정한다.
			// 6번인자 : 출력할 대상 DC를 지정한다.
			// 7번, 8번인자 : 출력할 대상DC에서 어디부터 출력할지 좌표를 지정한다.
			BitBlt(hDC, tLT.x, tLT.y, tSize.x, tSize.y,
				m_pTexture->GetDC(), iFrameX, iFrameY, SRCCOPY);
		}

		else
		{
			TransparentBlt(hDC, tLT.x, tLT.y, tSize.x, tSize.y, m_pTexture->GetDC(),
				iFrameX, iFrameY, tSize.x, tSize.y, m_dwColorKey);
		}
	}


	m_tMove = POSITION(0.f, 0.f);
}

void CObj::SaveFile(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(strPathKey);

	string	strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	SaveFromFullPath(strFullPath.c_str());
}

void CObj::SaveFromFullPath(const char* pFileName)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFileName, "wb");

	if (!pFile)
		return;

	Save(pFile);

	fclose(pFile);
}

void CObj::Save(FILE* pFile)
{
	int	iTagLength = m_strTag.length();
	fwrite(&iTagLength, sizeof(int), 1, pFile);
	fwrite(m_strTag.c_str(), sizeof(char), iTagLength, pFile);

	fwrite(&m_eType, sizeof(OBJECT_TYPE), 1, pFile);
	fwrite(&m_tPos, sizeof(POSITION), 1, pFile);
	fwrite(&m_tSize, sizeof(_SIZE), 1, pFile);
	fwrite(&m_tPivot, sizeof(POSITION), 1, pFile);
	fwrite(&m_tOffset, sizeof(POSITION), 1, pFile);

	fwrite(&m_fAngle, sizeof(float), 1, pFile);
	fwrite(&m_fMoveSpeed, sizeof(float), 1, pFile);
	fwrite(&m_fRotSpeed, sizeof(float), 1, pFile);
	fwrite(&m_dwColorKey, sizeof(DWORD), 1, pFile);
	fwrite(&m_bColorKey, sizeof(bool), 1, pFile);
	fwrite(&m_bGravity, sizeof(bool), 1, pFile);
	fwrite(&m_fForce, sizeof(float), 1, pFile);
	fwrite(&m_fForceOrigin, sizeof(float), 1, pFile);
	fwrite(&m_fGravityTime, sizeof(float), 1, pFile);

	bool	bTexture = false;

	if (m_pTexture)
		bTexture = true;

	fwrite(&bTexture, sizeof(bool), 1, pFile);

	if (bTexture)
	{
		string	strKey = m_pTexture->GetKey();
		const TCHAR* pFileName = m_pTexture->GetFileName();
		string	strPathKey = m_pTexture->GetPathKey();

		int	iLength = strKey.length();
		fwrite(&iLength, sizeof(int), 1, pFile);
		fwrite(strKey.c_str(), sizeof(char), iLength, pFile);

		iLength = lstrlen(pFileName);
		fwrite(&iLength, sizeof(int), 1, pFile);
		fwrite(pFileName, sizeof(TCHAR), iLength, pFile);

		iLength = strPathKey.length();
		fwrite(&iLength, sizeof(int), 1, pFile);
		fwrite(strPathKey.c_str(), sizeof(char), iLength, pFile);
	}

	
	// 애니메이션은 파일 따로 만든다. 보류

	/*
	list<class CCollider*>	m_ColliderList;
	class CAnimation*	m_pAnim*/
}

void CObj::LoadFromFullPath(const char* pFileName)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFileName, "rb");

	if (!pFile)
		return;

	Load(pFile);

	fclose(pFile);
}

void CObj::LoadFile(const char* pFileName, const string& strPathKey)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(strPathKey);

	string	strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	LoadFromFullPath(strFullPath.c_str());
}

void CObj::Load(FILE* pFile)
{
	int	iTagLength = 0;
	char	strTag[256] = {};
	fread(&iTagLength, sizeof(int), 1, pFile);
	fread(strTag, sizeof(char), iTagLength, pFile);
	m_strTag = strTag;

	fread(&m_eType, sizeof(OBJECT_TYPE), 1, pFile);
	fread(&m_tPos, sizeof(POSITION), 1, pFile);
	fread(&m_tSize, sizeof(_SIZE), 1, pFile);
	fread(&m_tPivot, sizeof(POSITION), 1, pFile);
	fread(&m_tOffset, sizeof(POSITION), 1, pFile);

	fread(&m_fAngle, sizeof(float), 1, pFile);
	fread(&m_fMoveSpeed, sizeof(float), 1, pFile);
	fread(&m_fRotSpeed, sizeof(float), 1, pFile);
	fread(&m_dwColorKey, sizeof(DWORD), 1, pFile);
	fread(&m_bColorKey, sizeof(bool), 1, pFile);
	fread(&m_bGravity, sizeof(bool), 1, pFile);
	fread(&m_fForce, sizeof(float), 1, pFile);
	fread(&m_fForceOrigin, sizeof(float), 1, pFile);
	fread(&m_fGravityTime, sizeof(float), 1, pFile);

	bool	bTexture = false;

	fread(&bTexture, sizeof(bool), 1, pFile);

	SAFE_RELEASE(m_pTexture);

	if (bTexture)
	{
		int	iLength = 0;
		char	strKey[256] = {};
		TCHAR	strFileName[MAX_PATH] = {};
		char	strPathKey[256] = {};

		fread(&iLength, sizeof(int), 1, pFile);
		fread(strKey, sizeof(char), iLength, pFile);

		fread(&iLength, sizeof(int), 1, pFile);
		fread(strFileName, sizeof(TCHAR), iLength, pFile);

		fread(&iLength, sizeof(int), 1, pFile);
		fread(strPathKey, sizeof(char), iLength, pFile);

		m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName, strPathKey);
	}

	

}

