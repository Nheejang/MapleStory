#include "Input.h"
#include "Core.h"
#include"Camera.h"
#include"Mouse.h"

DEFINITION_SINGLE(CInput)

CInput::CInput() :
	m_pCreateKey(nullptr),
	m_pMouse(nullptr),
	m_bShowCursor(false)
{
}

CInput::~CInput()
{
	SAFE_RELEASE(m_pMouse);
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init()
{

	AddKey("MoveUp", 'W');
	AddKey("MoveDown", 'S');
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');

	AddKey(VK_LBUTTON, "LButton");

	AddKey(VK_RBUTTON, "RButton");

	AddKey(VK_MBUTTON, "MButton");
	m_pMouse = new CMouse;

	if (!m_pMouse->Init())
	{
		SAFE_RELEASE(m_pMouse);
		return false;
	}

	m_pMouse->SetSize(20.f, 20.f);
	m_pMouse->SetTexture("Mouse", TEXT("Teemo.bmp"));
	m_pMouse->SetColorKey(255, 0, 255);
	ShowCursor(false);

	return true;
}

void CInput::Update(float fTime)
{
	unordered_map<string, PKEYINFO>::iterator	iter;
	unordered_map<string, PKEYINFO>::iterator	iterEnd = m_mapKey.end();

	for (iter = m_mapKey.begin(); iter != iterEnd; ++iter)
	{
		size_t	iCount = 0;
		for (size_t i = 0; i < iter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->vecKey[i]) & 0x8000)
				++iCount;
		}

		if (iCount == iter->second->vecKey.size())
		{
			if (!iter->second->bPress && !iter->second->bPush)
			{
				iter->second->bPress = true;
				iter->second->bPush = true;
			}

			else if (iter->second->bPress)
			{
				iter->second->bPress = false;
			}
		}

		else if (iter->second->bPush)
		{
			iter->second->bUp = true;
			iter->second->bPress = false;
			iter->second->bPush = false;
		}

		else if (iter->second->bUp)
			iter->second->bUp = false;
	}

	POINT tMousePos;

	GetCursorPos(&tMousePos);
	ScreenToClient(WINDOWHANDLE, &tMousePos);

	m_tMouseGap.x = tMousePos.x - m_tMouseClient.x;
	m_tMouseGap.y = tMousePos.y - m_tMouseClient.y;

	m_tMouseClient = tMousePos;

	m_tMouseWorld = m_tMouseClient + GET_SINGLE(CCamera)->GetPos();

	m_pMouse->SetPos(m_tMouseWorld);

	m_pMouse->Update(fTime);
	m_pMouse->LateUpdate(fTime);


	if (!m_bShowCursor && (m_tMouseClient.x < 0 || m_tMouseClient.x > _RESOLUTION.iWidth ||
		m_tMouseClient.y < 0 || m_tMouseClient.y > _RESOLUTION.iHeight))
	{
		m_bShowCursor = true;

		while (ShowCursor(TRUE) != 0)
		{
		}
	}

	else if (m_bShowCursor && 0.f <= m_tMouseClient.x && m_tMouseClient.x <= _RESOLUTION.iWidth &&
		0.f <= m_tMouseClient.y && m_tMouseClient.y <= _RESOLUTION.iHeight)
	{
		m_bShowCursor = false;
		while (ShowCursor(FALSE) >= 0)
		{
		}
	}
	
}

bool CInput::KeyPress(const string& strKey)
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPress;
}

bool CInput::KeyPush(const string& strKey)
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bPush;
}

bool CInput::KeyUp(const string& strKey)
{
	PKEYINFO	pInfo = FindKey(strKey);

	if (!pInfo)
		return false;

	return pInfo->bUp;
}

void CInput::RenderMouse(HDC hDC, float fTime)
{
	m_pMouse->Render(hDC, fTime);
}


PKEYINFO CInput::FindKey(const string& strKey)
{
	unordered_map<string, PKEYINFO>::iterator	iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return nullptr;

	return iter->second;
}
