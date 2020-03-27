#include"ColliderPixel.h"
#include"Obj.h"
#include"ColliderRect.h"
//#include"ColliderSphere.h"
#include"PathManager.h"

CColliderPixel::CColliderPixel()
{
	SetTag("Pixel");
	m_eCollType = CT_PIXEL;
}

CColliderPixel::CColliderPixel(const CColliderPixel& coll) :
	CCollider(coll)
{
	m_tRelative = coll.m_tRelative;

	m_tRelative.pPixel = new char[m_tRelative.iPixelCount * m_tRelative.iPixelSize];
	memcpy(m_tRelative.pPixel, coll.m_tRelative.pPixel,
		m_tRelative.iPixelCount * m_tRelative.iPixelSize);

}

CColliderPixel::~CColliderPixel()
{
	SAFE_DELETE_ARRAY(m_tRelative.pPixel);
}

void CColliderPixel::SetPixelCollisionInfo(const char* pFileName, const string& strPathKey)
{
	FILE* pFile = nullptr;

	//전체 경로를 만들어 준다.
	const char* pPath = GET_SINGLE(CPathManager)->FindPathFromMultibyte(strPathKey);

	string strPath;
	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	fopen_s(&pFile, strPath.c_str(), "rb");

	if (pFile)
	{
		BITMAPFILEHEADER bh;
		BITMAPINFOHEADER ih;

		fread(&bh, sizeof(bh), 1, pFile);
		fread(&ih, sizeof(ih), 1, pFile);

		int iByte = 1;

		switch (ih.biBitCount)
		{
		case 8:
			iByte = 1;
			break;
		case 24:
			iByte = 3;
			break;
		case 32:
			iByte = 4;
			break;
		}

		void* pPixel = new char[iByte * ih.biWidth * ih.biHeight];

		fread(pPixel, iByte, ih.biWidth * ih.biHeight, pFile);

		m_tRelative.pPixel = pPixel;
		m_tRelative.iPixelCount = ih.biWidth * ih.biHeight;
		m_tRelative.iWidth = ih.biWidth;
		m_tRelative.iHeight = ih.biHeight;
		m_tRelative.iPixelSize = iByte;

		//BMP 파일의 특성상 픽셀정보가 위 아래가 반전되어 있기 때문에 다시 반전시켜준다.
		void* pLine = new char[iByte * ih.biWidth];
		for (int i = 0; i < m_tRelative.iHeight / 2; ++i)
		{
			int iBottom = (m_tRelative.iHeight - 1) - i;

			memcpy(pLine, &((char*)pPixel)[i * m_tRelative.iWidth * iByte], iByte * m_tRelative.iWidth);
			memcpy(&((char*)pPixel)[i * m_tRelative.iWidth * iByte],
				&((char*)pPixel)[iBottom * m_tRelative.iWidth * iByte], iByte * m_tRelative.iWidth);
			memcpy(&((char*)pPixel)[iBottom * m_tRelative.iWidth * iByte], pLine, iByte * m_tRelative.iWidth);

		}

		SAFE_DELETE_ARRAY(pLine);

		fclose(pFile);

	}
}

bool CColliderPixel::CheckPixelCollision(int x, int y)
{
	PIXEL32 tPixel = {};
	tPixel.r = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize];
	tPixel.g = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize + 1];
	tPixel.b = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize + 2];

	return tPixel.r == m_tRelative.tCollisionPixel.r &&
		tPixel.g == m_tRelative.tCollisionPixel.g &&
		tPixel.b == m_tRelative.tCollisionPixel.b;
}

bool CColliderPixel::CheckPixelCollision(const POSITION& tPos)
{
	PIXEL32 tPixel = {};

	int x = tPos.x;
	int y = tPos.y;
	tPixel.r = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize];
	tPixel.g = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize + 1];
	tPixel.b = ((char*)m_tRelative.pPixel)[(y * m_tRelative.iWidth + x) * m_tRelative.iPixelSize + 2];

	return tPixel.r == m_tRelative.tCollisionPixel.r &&
		tPixel.g == m_tRelative.tCollisionPixel.g &&
		tPixel.b == m_tRelative.tCollisionPixel.b;
}

bool CColliderPixel::Init()
{
	return true;
}

int CColliderPixel::Update(float fTime)
{
	m_tWorldInfo = m_tRelative;
	m_tWorldInfo.tWorldPos.x = m_pObj->GetPos().x - m_tPivot.x * m_tRelative.iWidth;
	m_tWorldInfo.tWorldPos.y = m_pObj->GetPos().y - m_tPivot.y * m_tRelative.iHeight;

	return 0;
}

void CColliderPixel::Render(HDC hDC, float fTime)
{

}

CColliderPixel* CColliderPixel::Clone()const
{
	return new CColliderPixel(*this);
}

bool CColliderPixel::Collision(CCollider* pDest)
{
	switch (pDest->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPixel(((CColliderRect*)pDest)->GetInfo(), m_tWorldInfo);
	}

	return false;
}

void CColliderPixel::Save(FILE* pFile)
{
	CCollider::Save(pFile);

	fwrite(&m_tRelative.iPixelSize, sizeof(unsigned int), 1, pFile);
	fwrite(&m_tRelative.iPixelCount, sizeof(unsigned int), 1, pFile);
	fwrite(&m_tRelative.iWidth, sizeof(unsigned int), 1, pFile);
	fwrite(&m_tRelative.iHeight, sizeof(unsigned int), 1, pFile);
	fwrite(&m_tRelative.tWorldPos, sizeof(POSITION), 1, pFile);
	fwrite(&m_tRelative.tCollisionPixel, sizeof(PIXEL32), 1, pFile);

	fwrite(m_tRelative.pPixel, m_tRelative.iPixelSize, m_tRelative.iPixelCount, pFile);
}

void CColliderPixel::Load(FILE* pFile)
{

	CCollider::Load(pFile);

	fread(&m_tRelative.iPixelSize, sizeof(unsigned int), 1, pFile);
	fread(&m_tRelative.iPixelCount, sizeof(unsigned int), 1, pFile);
	fread(&m_tRelative.iWidth, sizeof(unsigned int), 1, pFile);
	fread(&m_tRelative.iHeight, sizeof(unsigned int), 1, pFile);
	fread(&m_tRelative.tWorldPos, sizeof(POSITION), 1, pFile);
	fread(&m_tRelative.tCollisionPixel, sizeof(PIXEL32), 1, pFile);

	m_tRelative.pPixel = new char[m_tRelative.iPixelSize * m_tRelative.iPixelCount];
	fread(m_tRelative.pPixel, m_tRelative.iPixelSize, m_tRelative.iPixelCount, pFile);
}