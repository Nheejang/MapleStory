#pragma once

#include "Game.h"

class CResourceManager
{
private:
	unordered_map<string, class CTexture*>	m_mapTexture;

public:
	bool Init();
	class CTexture* LoadTexture(const string& strKey, const TCHAR* pFileName,
		const string& strPathKey = TEXTURE_PATH);
	class CTexture* FindTexture(const string& strKey);

	DECLARE_SINGLE(CResourceManager)
};

