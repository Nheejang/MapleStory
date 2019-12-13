#include"Character.h"

CCharacter::CCharacter()
{}

CCharacter::CCharacter(const CCharacter& character) :
	CObj(character)
{
}

CCharacter::~CCharacter()
{}

bool CCharacter::Init()
{
	return true;
}

int CCharacter::Input(float fTime)
{
	CObj::Input(fTime);
	return 0;
}

int CCharacter::Update(float fTime)
{
	CObj::Update(fTime);
	return 0;
}

int CCharacter::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);
	return 0;
}

void CCharacter::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CCharacter::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}