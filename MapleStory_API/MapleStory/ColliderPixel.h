#pragma once
#include"Collider.h"
class CColliderPixel :
	public CCollider
{
	friend class CObj;
	friend class CCollisionManager;

private:
	CColliderPixel();
	CColliderPixel(const CColliderPixel& coll);
	~CColliderPixel();

private:
	PIXELINFO m_tRelative;
	PIXELINFO m_tWorldInfo;

public:
	PIXELINFO GetInfo()const
	{
		return m_tWorldInfo;
	}

	PIXEL32 GetCollisionPixel()const
	{
		return m_tRelative.tCollisionPixel;
	}

public:
	void SetCollisionPixel(unsigned char r, unsigned char g, unsigned b)
	{
		m_tRelative.tCollisionPixel.r = r;
		m_tRelative.tCollisionPixel.g = g;
		m_tRelative.tCollisionPixel.b = b;
	}

	void SetCollisionPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_tRelative.tCollisionPixel.r = r;
		m_tRelative.tCollisionPixel.g = g;
		m_tRelative.tCollisionPixel.b = b;
		m_tRelative.tCollisionPixel.a = a;
	}
	void SetPixelCollisionInfo(const char* pFileName, const string& strPathkey = TEXTURE_PATH);
	bool CheckPixelCollision(int x, int y);
	bool CheckPixelCollision(const POSITION& tPos);

public:
	virtual bool Init();
	virtual int Update(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CColliderPixel* Clone()const;
	virtual bool Collision(CCollider* pDest);
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};