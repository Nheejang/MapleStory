#include"AnimationClip.h"
#include"Texture.h"
#include"ResourceManager.h"

CAnimationClip::CAnimationClip() :
	m_pTexture(nullptr)
{
}

CAnimationClip::CAnimationClip(const CAnimationClip& clip)
{
	*this = clip;

	if (m_pTexture)
		m_pTexture->AddRef();
}

CAnimationClip::~CAnimationClip()
{
	SAFE_RELEASE(m_pTexture);
}

CAnimationClip* CAnimationClip::Clone()const
{
	return new CAnimationClip(*this);
}

bool CAnimationClip::Load(const char* pFullPath)
{
	FILE* pFile = nullptr;

	fopen_s(&pFile, pFullPath, "rt");

	if (!pFile)
		return false;

	//�̸��о��
	char strLine[256] = {};
	fgets(strLine, 256, pFile);

	m_strName = strLine;
	m_strName.pop_back();

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	int iLength = strlen(strLine);
	strLine[iLength - 1] = 0;

	m_eOption = (ANIMATION_OPTION)atoi(strLine);
	
	//ũ�⸦ �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;

	m_tSize.x = atof(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;

	m_tSize.y = atof(strLine);

	//������ ī��Ʈ�� �о��.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;

	m_iFrameCountX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	
	m_iFrameCountY = atoi(strLine);

	m_iFrameCount = m_iFrameCountX * m_iFrameCountY;

	//��Ʋ���� ��ü x,y�� �о��
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	m_iFrameMaxX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1]=0;
	m_iFrameMaxY = atoi(strLine);

	//��Ʋ���� ���� x,y�� �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	m_iStartX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	m_iStartY = atoi(strLine);

	//�ִϸ��̼� ������ �ð��� ����
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	m_fCompleteTime = atof(strLine);

	m_fAnimationTime = 0.f;

	m_iFrameX = m_iStartX;
	m_iFrameY = m_iStartY;

	//�̹��� Ű�� ��θ� ����.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	string strKey = strLine;

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	fgets(strLine, 256, pFile);

	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;
	TCHAR strFileName[MAX_PATH] = {};

#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, strLine, -1, strFileName, strlen(strLine) * 2);
#else
	strcpy_s(strFileName, strLine);
#endif

	m_pTexture = GET_SINGLE(CResourceManager)->LoadTexture(strKey, strFileName);

	//�÷�Ű�� ����
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);
	iLength = strlen(strLine);
	strLine[iLength - 1] = 0;

	m_bColorKey = (bool)atoi(strLine);

	if (m_bColorKey)
	{
		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);
		iLength = strlen(strLine);
		strLine[iLength - 1] = 0;

		unsigned char r = atoi(strLine);

		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);
		strLine[iLength - 1] = 0;

		unsigned char g = atoi(strLine);

		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);
		iLength = strlen(strLine);
		if (strLine[iLength - 1] == '\n')
			strLine[iLength - 1] = 0;
		unsigned char b = atoi(strLine);

		m_dwColorKey = RGB(r, g, b);
	}
	
	fclose(pFile);

	return true;
}