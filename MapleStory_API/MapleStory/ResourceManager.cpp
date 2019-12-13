#include "ResourceManager.h"
#include "Texture.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	Safe_Release_Map(m_mapTexture);
}

bool CResourceManager::Init()
{
	CTexture* pTex = LoadTexture("BackBuffer", TEXT("BackBuffer.bmp"));

	SAFE_RELEASE(pTex);

	return true;
}

CTexture* CResourceManager::LoadTexture(const string& strKey,
	const TCHAR* pFileName, const string& strPathKey)
{
	CTexture* pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strKey, pFileName, strPathKey))
	{
		SAFE_RELEASE(pTexture);
		return nullptr;
	}

	pTexture->AddRef();
	m_mapTexture.insert(make_pair(strKey, pTexture));

	return pTexture;
}

CTexture* CResourceManager::FindTexture(const string& strKey)
{
	unordered_map<string, CTexture*>::iterator	iter = m_mapTexture.find(strKey);

	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}
