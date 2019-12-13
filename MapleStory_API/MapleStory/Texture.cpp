#include "Texture.h"
#include "Core.h"
#include "PathManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	// 지우기 전에 DC에 기존에 장착되어 있던 비트맵을 다시 지정해준다.
	SelectObject(m_hMemDC, m_hOldBmp);

	// 비트맵 도구를 지워준다.
	DeleteObject(m_hBmp);

	// 메모리 DC를 지워준다.
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(const string& strKey, const TCHAR* pFileName,
	const string& strPathKey)
{
	// 메모리 DC를 생성한다.
	m_hMemDC = CreateCompatibleDC(WINDOWDC);

	// 인자로 들어온 파일 경로들을 조합해서 최종 파일 경로를 얻어온다.
	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);
	wstring	strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	m_strPathKey = strPathKey;
	m_strKey = strKey;
	lstrcpy(m_strFileName, pFileName);
	lstrcpy(m_strFullPath, strFullPath.c_str());

	// 이미지를 읽어온다.
	m_hBmp = (HBITMAP)LoadImage(WINDOWINSTANCE, strFullPath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);

	// 읽어온 이미지를 DC에 지정해준다.
	// 기존에 DC에 지정되어 있는 이미지는 별도로 저장을 해주어야 한다.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);

	// 이미지 정보를 얻어온다.
	GetObject(m_hBmp, sizeof(m_tBmp), &m_tBmp);

	return true;
}
