#include"Map.h"
#include"Texture.h"
#include"ResourceManager.h"
#include"Camera.h"
//
CMap::CMap()
{
	m_eMapType = MT_MOVE;
	m_eMapOption = MO_NONE;

	m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));

	SetColorKey(255, 0, 255);
}
CMap::CMap(const CMap& Map) :
	CObj(Map)
{
	m_eMapType = Map.m_eMapType;
	m_eMapOption = Map.m_eMapOption;

	m_pTypeTex = Map.m_pTypeTex;
	if (m_pTypeTex)
		m_pTypeTex->AddRef();
}
CMap::~CMap()
{
	SAFE_RELEASE(m_pTypeTex);
}

void CMap::SetMapType(MAP_TYPE eType)
{
	m_eMapType = eType;

	SAFE_RELEASE(m_pTypeTex);

	switch (m_eMapType)
	{
	case MT_MOVE:
		m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));
		break;
	case MT_NOMOVE:
		m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove", TEXT("OptionNoMove.bmp"));
		break;
	}
}

bool CMap::Init()
{
	return true;
}
int CMap::Input(float fTime)
{
	return 0;
}

int CMap::Update(float fTime)
{
	CObj::Update(fTime);
	return 0;
}
int CMap::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);
	return 0;
}

void CMap::Collision(float fTime)
{
	CObj::Collision(fTime);
}
void CMap::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CMap* CMap::Clone()
{
	return new CMap(*this);
}

void CMap::Save(FILE* pFile)
{
	CObj::Save(pFile);

	fwrite(&m_eMapType, sizeof(MAP_TYPE), 1, pFile);
	fwrite(&m_eMapOption, sizeof(MAP_OPTION), 1, pFile);
	fwrite(&m_iIndex, sizeof(int), 1, pFile);
}

void CMap::Load(FILE* pFile)
{
	CObj::Load(pFile);

	fread(&m_eMapType, sizeof(MAP_TYPE), 1, pFile);
	fread(&m_eMapOption, sizeof(MAP_OPTION), 1, pFile);
	fread(&m_iIndex, sizeof(int), 1, pFile);

	switch (m_eMapType)
	{
	case MT_MOVE:
		m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));
		break;
	case MT_NOMOVE:
		m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove", TEXT("OptionNoMove.bmp"));
		break;
	}
}

void CMap::RenderGrid(HDC hDC, float fTime)
{
	POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();
	POSITION tLT = m_tPos - m_tSize * m_tPivot;

	if (m_bCameraEnable)
		tLT -= tCameraPos;

	TransparentBlt(hDC, tLT.x, tLT.y, m_tSize.x, m_tSize.y, m_pTypeTex->GetDC(),
		0, 0, m_tSize.x, m_tSize.y, m_dwColorKey);
}