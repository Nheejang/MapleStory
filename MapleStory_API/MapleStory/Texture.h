#pragma once
#include "Ref.h"

class CTexture :
	public CRef
{
	friend class CResourceManager;

private:
	CTexture();
	~CTexture();

private:
	HDC		m_hMemDC;
	HBITMAP	m_hBmp;	// 비트맵 그리기 도구이다. 파일로부터 픽셀을 읽어와서 설정한다.
	HBITMAP	m_hOldBmp;
	BITMAP	m_tBmp;
	string	m_strKey;
	string	m_strPathKey;
	TCHAR	m_strFullPath[MAX_PATH];
	TCHAR	m_strFileName[MAX_PATH];

public:
	const TCHAR* GetFullPath()	const
	{
		return m_strFullPath;
	}

	const TCHAR* GetFileName()	const
	{
		return m_strFileName;
	}

	string GetPathKey()	const
	{
		return m_strPathKey;
	}

	string GetKey()	const
	{
		return m_strKey;
	}

	HDC GetDC()	const
	{
		return m_hMemDC;
	}

	unsigned int GetWidth()	const
	{
		return (unsigned int)m_tBmp.bmWidth;
	}

	unsigned int GetHeight()	const
	{
		return (unsigned int)m_tBmp.bmHeight;
	}

public:
	bool LoadTexture(const string& strKey, const TCHAR* pFileName,
		const string& strPathKey = TEXTURE_PATH);
};

