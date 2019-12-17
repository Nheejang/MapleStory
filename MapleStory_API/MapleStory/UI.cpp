#include"UI.h"


CUI::CUI()
{
	m_eType = OT_UI;
	m_bCameraEnable = false;
}

CUI::CUI(const CUI& ui) :
	CObj(ui)
{

}

CUI::~CUI()
{

}

bool CUI::Init()
{
	if (!CObj::Init())
		return false;
	return true;
}

int CUI::Input(float fTime)
{
	CObj::Input(fTime);
	
	return 0;
}

int CUI::Update(float fTime)
{
	CObj::Update(fTime);

	return 0;
}

int CUI::LateUpdate(float fTime)
{
	CObj::LateUpdate(fTime);

	return 0;
}

void CUI::Collision(float fTime)
{
	CObj::Collision(fTime);
}

void CUI::Render(HDC hDC, float fTime)
{
	CObj::Render(hDC, fTime);
}
