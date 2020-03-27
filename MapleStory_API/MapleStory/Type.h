#pragma once

#include "Flag.h"

#define PI 3.141592f
#define GRAVITY 0.98f

typedef struct _tagResolution
{
	unsigned int iWidth;
	unsigned int iHeight;

	_tagResolution() :
		iWidth(0),
		iHeight(0)
	{
	}
}RESOLUTION,*PRESOLUTION;

typedef struct _tagPosition
{
	float	x, y;

	_tagPosition() :
		x(0.f),
		y(0.f)
	{
	}

	_tagPosition(float _x, float _y) :
		x(_x),
		y(_y)
	{
	}

	_tagPosition(const _tagPosition& tPos)
	{
		x = tPos.x;
		y = tPos.y;
	}

	_tagPosition(const POINT& tPos) :
		x(tPos.x),
		y(tPos.y)
	{
	}

	void operator = (const POINT& tPos)
	{
		x = tPos.x;
		y = tPos.y;
	}

	void operator = (const _tagPosition& tPos)
	{
		x = tPos.x;
		y = tPos.y;
	}

	_tagPosition operator + (const _tagPosition& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x + tPos.x;
		_tPos.y = y + tPos.y;
		return _tPos;
	}

	_tagPosition operator + (const POINT& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x + tPos.x;
		_tPos.y = y + tPos.y;
		return _tPos;
	}

	_tagPosition operator + (int value)	const
	{
		_tagPosition	tPos;
		tPos.x = x + value;
		tPos.y = y + value;
		return tPos;
	}

	_tagPosition operator + (float value)	const
	{
		_tagPosition	tPos;
		tPos.x = x + value;
		tPos.y = y + value;
		return tPos;
	}

	void operator += (const _tagPosition& tPos)
	{
		x += tPos.x;
		y += tPos.y;
	}

	void operator += (const POINT& tPos)
	{
		x += tPos.x;
		y += tPos.y;
	}

	void operator += (int value)
	{
		x += value;
		y += value;
	}

	void operator += (float value)
	{
		x += value;
		y += value;
	}

	// ===============   - ==================
	_tagPosition operator - (const _tagPosition& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x - tPos.x;
		_tPos.y = y - tPos.y;
		return _tPos;
	}

	_tagPosition operator - (const POINT& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x - tPos.x;
		_tPos.y = y - tPos.y;
		return _tPos;
	}

	_tagPosition operator - (int value)	const
	{
		_tagPosition	tPos;
		tPos.x = x - value;
		tPos.y = y - value;
		return tPos;
	}

	_tagPosition operator - (float value)	const
	{
		_tagPosition	tPos;
		tPos.x = x - value;
		tPos.y = y - value;
		return tPos;
	}

	void operator -= (const _tagPosition& tPos)
	{
		x -= tPos.x;
		y -= tPos.y;
	}

	void operator -= (const POINT& tPos)
	{
		x -= tPos.x;
		y -= tPos.y;
	}

	void operator -= (int value)
	{
		x -= value;
		y -= value;
	}

	void operator -= (float value)
	{
		x -= value;
		y -= value;
	}

	// ===============   * ==================
	_tagPosition operator * (const _tagPosition& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x * tPos.x;
		_tPos.y = y * tPos.y;
		return _tPos;
	}

	_tagPosition operator * (const POINT& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x * tPos.x;
		_tPos.y = y * tPos.y;
		return _tPos;
	}

	_tagPosition operator * (int value)	const
	{
		_tagPosition	tPos;
		tPos.x = x * value;
		tPos.y = y * value;
		return tPos;
	}

	_tagPosition operator * (float value)	const
	{
		_tagPosition	tPos;
		tPos.x = x * value;
		tPos.y = y * value;
		return tPos;
	}

	void operator *= (const _tagPosition& tPos)
	{
		x *= tPos.x;
		y *= tPos.y;
	}

	void operator *= (const POINT& tPos)
	{
		x *= tPos.x;
		y *= tPos.y;
	}

	void operator *= (int value)
	{
		x *= value;
		y *= value;
	}

	void operator *= (float value)
	{
		x *= value;
		y *= value;
	}

	// ===============   / ==================
	_tagPosition operator / (const _tagPosition& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x / tPos.x;
		_tPos.y = y / tPos.y;
		return _tPos;
	}

	_tagPosition operator / (const POINT& tPos)	const
	{
		_tagPosition	_tPos;
		_tPos.x = x / tPos.x;
		_tPos.y = y / tPos.y;
		return _tPos;
	}

	_tagPosition operator / (int value)	const
	{
		_tagPosition	tPos;
		tPos.x = x / value;
		tPos.y = y / value;
		return tPos;
	}

	_tagPosition operator / (float value)	const
	{
		_tagPosition	tPos;
		tPos.x = x / value;
		tPos.y = y / value;
		return tPos;
	}

	void operator /= (const _tagPosition& tPos)
	{
		x /= tPos.x;
		y /= tPos.y;
	}

	void operator /= (const POINT& tPos)
	{
		x /= tPos.x;
		y /= tPos.y;
	}

	void operator /= (int value)
	{
		x /= value;
		y /= value;
	}

	void operator /= (float value)
	{
		x /= value;
		y /= value;
	}
}POSITION, * PPOSITION, _SIZE, * _PSIZE;


typedef struct _tagRectInfo
{
	float	l;
	float	t;
	float	r;
	float	b;

	_tagRectInfo() :
		l(0.f),
		t(0.f),
		r(0.f),
		b(0.f)
	{
	}

	_tagRectInfo(float _l, float _t, float _r, float _b) :
		l(_l),
		t(_t),
		r(_r),
		b(_b)
	{
	}

	_tagRectInfo(const _tagRectInfo& tInfo)
	{
		l = tInfo.l;
		t = tInfo.t;
		r = tInfo.r;
		b = tInfo.b;
	}

	void SetRect(float _l, float _t, float _r, float _b)
	{
		l = _l;
		t = _t;
		r = _r;
		b = _b;
	}

	void Move(float x, float y)
	{
		l += x;
		t += y;
		r += x;
		b += y;
	}

	float GetWidth()	const
	{
		return r - l;
	}

	float GetHeight()	const
	{
		return b - t;
	}

	void Render(HDC hDC)
	{
		Rectangle(hDC, (int)l, (int)t, (int)r, (int)b);
	}

	void RenderEllipse(HDC hDC)
	{
		Ellipse(hDC, (int)l, (int)t, (int)r, (int)b);
	}
}RECTINFO, * PRECTINFO;

typedef struct _tagSphereInfo
{
	POSITION tCenter;
	float fRadius;

	_tagSphereInfo():
		fRadius(0.f)
	{
	}

	_tagSphereInfo(float x, float y, float r) :
		tCenter(x, y),
		fRadius(r)
	{
	}
	_tagSphereInfo(const _tagSphereInfo& tInfo)
	{
		tCenter = tInfo.tCenter;
		fRadius = tInfo.fRadius;
	}

	void SetSphere(float x, float y, float r)
	{
		tCenter.x = x;
		tCenter.y = y;
		fRadius = r;
	}

	void Move(float x, float y)
	{
		tCenter.x += x;
		tCenter.y += y;
	}

	void Render(HDC hDC)
	{
		Ellipse(hDC, (int)tCenter.x - fRadius, (int)tCenter.y - fRadius,
			(int)tCenter.x + fRadius, (int)tCenter.y + fRadius);
	}

	void RenderFrame(HDC hDC)
	{
		POSITION tPos;
		tPos.x = tCenter.x + fRadius;
		tPos.y = tCenter.y;

		MoveToEx(hDC, tPos.x, tPos.y, nullptr);

		for (int i = 2; i <= 180; ++i)
		{
			tPos.x = tCenter.x + cosf(i * 2 * PI / 180.f) * fRadius;
			tPos.y = tCenter.y + sinf(i * 2 * PI / 180.f) * fRadius;

			LineTo(hDC, tPos.x, tPos.y);
		}
	}
}SPHEREINFO,*PSPHEREINFO;

typedef struct _tagPixel32
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

}PIXEL32,*PPIXEL32;
typedef struct _tagPixelCollInfo
{
	void* pPixel;
	unsigned int iPixelSize;
	unsigned int iPixelCount;
	unsigned int iWidth;
	unsigned int iHeight;
	POSITION tWorldPos;
	PIXEL32 tCollisionPixel;

}PIXELINFO,*PPIXELINFO;