#pragma once
#include"Obj.h"
class CMap :
	public CObj
{
	friend class CObj;
	friend class CStage;

protected:
	CMap();
	CMap(const CMap& map);
	~CMap();

private:
	MAP_TYPE m_eMapType;
	MAP_OPTION m_eMapOption;
	int m_iIndex;
	class CTexture* m_pTypeTex;

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