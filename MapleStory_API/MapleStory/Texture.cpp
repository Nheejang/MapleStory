#include "Texture.h"
#include "Core.h"
#include "PathManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	// ����� ���� DC�� ������ �����Ǿ� �ִ� ��Ʈ���� �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBmp);

	// ��Ʈ�� ������ �����ش�.
	DeleteObject(m_hBmp);

	// �޸� DC�� �����ش�.
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(const string& strKey, const TCHAR* pFileName,
	const string& strPathKey)
{
	// �޸� DC�� �����Ѵ�.
	m_hMemDC = CreateCompatibleDC(WINDOWDC);

	// ���ڷ� ���� ���� ��ε��� �����ؼ� ���� ���� ��θ� ���´�.
	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);
	wstring	strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	m_strPathKey = strPathKey;
	m_strKey = strKey;
	lstrcpy(m_strFileName, pFileName);
	lstrcpy(m_strFullPath, strFullPath.c_str());

	// �̹����� �о�´�.
	m_hBmp = (HBITMAP)LoadImage(WINDOWINSTANCE, strFullPath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);

	// �о�� �̹����� DC�� �������ش�.
	// ������ DC�� �����Ǿ� �ִ� �̹����� ������ ������ ���־�� �Ѵ�.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBmp);

	// �̹��� ������ ���´�.
	GetObject(m_hBmp, sizeof(m_tBmp), &m_tBmp);

	return true;
}
