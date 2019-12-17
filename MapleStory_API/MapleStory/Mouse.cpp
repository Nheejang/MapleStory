#include"Mouse.h"
#include"Input.h"
#include<iostream>

CMouse::CMouse()
{

}
CMouse::CMouse(const CMouse& mouse) :
	CObj(mouse)
{
	m_bLClick = mouse.m_bLClick;
	m_bRClick = mouse.m_bRClick;
	m_bMClick = mouse.m_bMClick;
}

CMouse::~CMouse()
{

}

bool CMouse::GetLButton() const
{
	return m_bLClick;
}
bool CMouse::GetRButton() const
{
	return m_bRClick;
}
bool CMouse::GetMButton() const
{
	return m_bMClick;
}

bool CMouse::Init()
{
	if (!CObj::Init())
		return false;

	m_bLClick = false;
	m_bRClick = false;
	m_bMClick = false;

	return true;
}

int CMouse::Input(float fTime)
{
	CObj::Input(fTime);
	
	if (KEYPUSH("LButton"))
	{
		m_bLClick = true;
		std::cout << "ÂïÈû" << std::endl;
	}
	//else if (KEYUP("LButton"))
	//	m_bLClick = false;
	
	if (KEYPUSH("RButton"))
		m_bRClick = true;
	/*else if (KEYUP("RButton"))
		m_bRClick = false;
*/
	if (KEYPUSH("MButton"))
		m_bMClick = true;
	/*else if (KEYUP("MButton"))
		m_bMClick = false;
*/
	return 0;
}

int CMouse::Update(float fTime)
{

	CObj::Update(fTime);

	return 0;
}
int CMouse::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);

	return 0;
}

void CMouse::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CMouse::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}

CMouse* CMouse::Clone()
{
	return new CMouse(*this);
}