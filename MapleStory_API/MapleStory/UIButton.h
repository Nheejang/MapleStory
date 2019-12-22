#pragma once
#include"UI.h"
class CUIButton :
	public CUI
{
	friend class CObj;

protected:
	CUIButton();
	CUIButton(const CUIButton& ui);
	~CUIButton();

protected:
	BUTTON_STATE m_eBtnState;
	function<void(float)> m_ClickCallback;
	bool m_bCallback;

public:
	virtual bool Init();
	virtual int Input(float fTime);
	virtual int Update(float fTime);
	virtual int LateUpdate(float fTime);
	virtual void Collision(float fTime);
	virtual void Render(HDC hDC, float fTime);
	virtual CUIButton* Clone();



};