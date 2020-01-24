#include "BackGround.h"

CBackGround::CBackGround()
{
}

CBackGround::CBackGround(CBackGround& back)
	:CObj(back)
{
}
CBackGround::~CBackGround()
{

}
bool CBackGround::Init()
{
	return true;
}

int CBackGround::Input(float fTime)
{
	CObj::Input( fTime);
	return 0;
}

int CBackGround::Update(float fTime)
{

	CObj::Update(fTime);

	return 0;
}

int CBackGround::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);
	return 0;
}

void CBackGround::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CBackGround::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CBackGround* CBackGround::Clone()
{
	return new CBackGround(*this);
}
