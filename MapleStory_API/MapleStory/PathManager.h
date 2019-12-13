#pragma once

#include "Game.h"

class CPathManager
{
private:
	unordered_map<string, MyString>	m_mapPath;
	char	m_strPath[MAX_PATH] = {};

public:
	bool Init();
	bool AddPath(const string& strKey, const MyString& strPath,
		const string& strBaseKey = ROOT_PATH);
	const TCHAR* FindPath(const string& strKey);
	const char* FindPathFromMultibyte(const string& strKey);

	DECLARE_SINGLE(CPathManager)
};

