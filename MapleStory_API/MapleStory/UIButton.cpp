#include"UIButton.h"
#include"Input.h"

CUIButton::CUIButton()
{
	m_eType = OT_UI;
	m_bCameraEnable = false;
}

CUIButton::CUIButton(const CUIButton& ui) :
	CUI(ui)
{

}

CUIButton::~CUIButton()
{

}

bool CUIButton::Init()
{
	if (!CUI::Init())
		return false;

	SetSize(90, 40);
	return true;
}

int CUIButton::Input(float fTime)
{
	CUI::Input(fTime);

	return 0;
}

int CUIButton::Update(float fTime)
{
	CUI::Update(fTime);


	return 0;
}

int CUIButton::LateUpdate(float fTime)
{
	CUI::LateUpdate(fTime);

	return 0;
}

void CUIButton::Collision(float fTime)
{
	CUI::Collision(fTime);
}

void CUIButton::Render(HDC hDC, float fTime)
{
	CUI::Render(hDC, fTime);

}

CUIButton* CUIButton::Clone()
{
	return new CUIButton(*this);
}