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

public:
	void OnCollisionEnter(CCollider* pSrc, CCollider* pDest, float fTime);
	void OnCollision(CCollider* pSrc, CCollider* pDest, float fTime);
	void OnCollisionLeave(CCollider* pSrc, CCollider* pDest, float fTime);

public:
	void SetCallback(void(*pFunc)(float));
	template<typename T>
	void SetCallback(void(T::* pFunc)(float), T* pObj)
	{
		m_bCallback = true;
		m_ClickCallback = bind(pFunc, pObj, placeholders::_1);
	}
};