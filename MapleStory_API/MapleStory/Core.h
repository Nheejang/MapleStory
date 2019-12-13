#pragma once

#include"Game.h"

class CCore
{
private:
	static bool m_bLoop;

private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	RESOLUTION m_tResolution;
	HDC m_hDC;
	class CTimer* m_pTimer;
	float m_fTimeScale;
	class CTexture* m_pBackBuffer;


public:
	HINSTANCE GetWindowInstance() const
	{
		return m_hInst;
	}
	HWND GetWindowHandle() const
	{
		return m_hWnd;
	}

	RESOLUTION GetResolution() const
	{
		return m_tResolution;
	}
	HDC GetWindowDC() const
	{
		return m_hDC;
	}
	void ResizeWindow()
	{
		RECT rc = {};
		GetClientRect(m_hWnd, &rc);

		m_tResolution.iWidth = rc.right - rc.left;
		m_tResolution.iHeight = rc.bottom - rc.top;
	}

public:
	bool Init(HINSTANCE hInst, unsigned int iWidth, unsigned int iHeight,
		const TCHAR* pTitle, const TCHAR* pClass, int iIconID);
	int Run();

private:
	void Logic();
	int Input(float fTime);
	int Update(float fTime);
	int Collision(float fTime);
	int Render(float fTime);

private:
	void Register(const TCHAR* pClass, int iIconID);
	void CreateWnd(const TCHAR* pTitle, const TCHAR* pClass);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam);

DECLARE_SINGLE(CCore)
};