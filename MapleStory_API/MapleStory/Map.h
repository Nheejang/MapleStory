#pragma once
#include"Obj.h"
class CMap :
	public CObj
{
	friend class CObj;
	friend class CScene;

protected:
	CMap();
	CMap(const CMap& map);
	~CMap();

private:
	MAP_TYPE m_eMapType;
	MAP_OPTION m_eMapOption;
	int m_iIndex;
	_SIZE m_MapSize;
	int m_XNumber;
	int m_YNumber;
	_SIZE m_TileSize;
	MAP_TYPE* arrTile;

public:
	MAP_TYPE GetMapType() const
	{
		return m_eMapType;
	}

	MAP_OPTION GetMapOption() const
	{
		return m_eMapOption;
	}
	
public:
	void SetMapType(MAP_TYPE eType);
	void SetMap(MAP_TYPE eType, MAP_OPTION eMapOption, _SIZE MapSize, int xNum, int yNum,_SIZE TileSize);
	void SetTile(MAP_TYPE eType, POSITION pos);
	
public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CMap* Clone();
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

public:
	void RenderGrid(HDC hDC, float fTime);
};