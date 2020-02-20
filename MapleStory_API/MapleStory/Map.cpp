#include"Map.h"
#include"ResourceManager.h"
#include"Camera.h"
#include"Texture.h"

CMap::CMap()
{
	m_eMapType = MT_MOVE;
	m_eMapOption = MO_NONE;


	SetColorKey(255, 255, 255);
}
CMap::CMap(const CMap& Map) :
	CObj(Map)
{
	m_eMapType = Map.m_eMapType;
	m_eMapOption = Map.m_eMapOption;

	m_pTexture = Map.m_pTexture;
	arrTile = Map.arrTile;
	if (m_pTexture)
		m_pTexture->AddRef();
}
CMap::~CMap()
{
	SAFE_RELEASE(m_pTexture);
	for (int i = 0; i <4; i++)
		SAFE_RELEASE(m_pTypeTexArray[i]);
	delete[] arrTile;
}

void CMap::SetMapType(MAP_TYPE eType)
{
	m_eMapType = eType;

//	SAFE_RELEASE(m_pTexture);

	//switch (m_eMapType)
	//{
	//case MT_MOVE:
	//	m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));
	//	break;
	//case MT_NOMOVE:
	//	m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove", TEXT("OptionNoMove.bmp"));
	//	break;
	//}
}

void CMap::SetMap(MAP_TYPE eType, MAP_OPTION eMapOption, _SIZE MapSize, int xNum, int yNum, _SIZE TileSize)
{
	m_eMapType= eType;
	m_eMapOption = eMapOption;
	m_MapSize = MapSize;
	m_XNumber = xNum;
	m_YNumber = yNum;
	m_TileSize = TileSize;
	//switch (m_eMapType)
	//{
	//case MT_MOVE:
	//	m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));
	//	break;
	//case MT_NOMOVE:
	//	m_pTypeTex = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove", TEXT("OptionNoMove.bmp"));
	//	break;
	//}
	arrTile = new MAP_TYPE[m_XNumber * m_YNumber]{MT_MOVE};
}
void CMap::SetTile(MAP_TYPE type, POSITION pos)
{
	int x = 0 , y=0;
	for (x; x < m_XNumber; x++)
	{
		if (m_TileSize.x * x <= pos.x && m_TileSize.x * (x + 1) >= pos.x)
		{
			break;
		}
	}

	for (y; y < m_YNumber; y++)
	{
		if (m_TileSize.y * y <= pos.y && m_TileSize.y * (y + 1) >= pos.y)
		{
			break;
		}
	}

	if (0 == x)
		arrTile[y * m_XNumber] = type;
	else if (0 == y)
		arrTile[x] = type;
	else
		arrTile[y * m_XNumber + x] = type;
}
bool CMap::Init()
{
	
		m_pTypeTexArray[0] = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeMove", TEXT("OptionNone.bmp"));
		m_pTypeTexArray[1] = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove", TEXT("NoMove.bmp"));
		m_pTypeTexArray[2] = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeNoMove2", TEXT("NoMove2.bmp"));
		m_pTypeTexArray[3] = GET_SINGLE(CResourceManager)->LoadTexture("MapTypeUnEven", TEXT("UnEvenUp.bmp"));
	
	
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
	RenderGrid(hDC, fTime);
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
	//fwrite(&m_iIndex, sizeof(int), 1, pFile);

	fwrite(&m_MapSize, sizeof(_SIZE),1,pFile);
	fwrite(&m_XNumber, sizeof(int), 1, pFile);
	fwrite(&m_YNumber, sizeof(int), 1, pFile);
	fwrite(&m_TileSize, sizeof(_SIZE), 1, pFile);
	fwrite(arrTile, sizeof(MAP_TYPE), (m_XNumber * m_YNumber), pFile);
	
}

void CMap::Load(FILE* pFile)
{
	CObj::Load(pFile);

	fread(&m_eMapType, sizeof(MAP_TYPE), 1, pFile);
	fread(&m_eMapOption, sizeof(MAP_OPTION), 1, pFile);
	//fwrite(&m_iIndex, sizeof(int), 1, pFile);

	fread(&m_MapSize, sizeof(_SIZE), 1, pFile);
	fread(&m_XNumber, sizeof(int), 1, pFile);
	fread(&m_YNumber, sizeof(int), 1, pFile);
	fread(&m_TileSize, sizeof(_SIZE), 1, pFile);
	if (arrTile)
		delete[] arrTile;
	//MAP_TYPE* temp = new MAP_TYPE[m_XNumber * m_YNumber]{};
	arrTile = new MAP_TYPE[m_XNumber * m_YNumber]{};
	fread(arrTile, sizeof(MAP_TYPE), (m_XNumber * m_YNumber), pFile);
//	memcpy(arrTile, temp, sizeof(MAP_TYPE) * (m_XNumber * m_YNumber));
	
}

void CMap::RenderGrid(HDC hDC, float fTime)
{
	POSITION tCameraPos = GET_SINGLE(CCamera)->GetPos();
	//POSITION tLT = m_tPos - m_tSize * m_tPivot;

	m_tSize = m_TileSize;
	for (int i = 0; i < m_XNumber; i++)
	{
		for (int j = 0; j < m_YNumber; j++)
		{
			switch (arrTile[j * m_XNumber + i])
			{
			case MT_MOVE:
				this->SetTexture(m_pTypeTexArray[0]);
				SetColorKey(255, 0, 255);
				TransparentBlt(hDC, m_TileSize.x * i - tCameraPos.x, m_TileSize.y * j - tCameraPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
					0, 0, 52, 52, m_dwColorKey);
				break;
			case MT_NOMOVE:
				this->SetTexture(m_pTypeTexArray[1]);
				SetColorKey(255, 255, 255);
				TransparentBlt(hDC, m_TileSize.x * i - tCameraPos.x, m_TileSize.y * j - tCameraPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
					0, 0, m_TileSize.x, m_TileSize.y, m_dwColorKey);
			//	SAFE_RELEASE(m_pTexture);
				break;
			case MT_NOMOVE2:
				this->SetTexture(m_pTypeTexArray[2]);
				SetColorKey(255, 255, 255);
				TransparentBlt(hDC, m_TileSize.x * i - tCameraPos.x, m_TileSize.y * j - tCameraPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
					0, 0, m_TileSize.x, m_TileSize.y, m_dwColorKey);
			//	SAFE_RELEASE(m_pTexture);
				break;
			case MT_UNEVEN:
				this->SetTexture(m_pTypeTexArray[3]);
				SetColorKey(255, 255, 255);
				TransparentBlt(hDC, m_TileSize.x * i - tCameraPos.x, m_TileSize.y * j - tCameraPos.y, m_tSize.x, m_tSize.y, m_pTexture->GetDC(),
					0, 0, m_TileSize.x, m_TileSize.y, m_dwColorKey);
				break;
			}
			
		}
	}
	//if (m_bCameraEnable)
	//	tLT -= tCameraPos;

	/*TransparentBlt(hDC, tLT.x, tLT.y, m_tSize.x, m_tSize.y, m_pTypeTex->GetDC(),
		0, 0, m_tSize.x, m_tSize.y, m_dwColorKey);*/
}