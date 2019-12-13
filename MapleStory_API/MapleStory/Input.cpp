#include "Input.h"
#include "Core.h"
#include "Camera.h"

DEFINITION_SINGLE(CInput)

CInput::CInput() :
	m_pCreateKey(nullptr),
	
	m_bShowCursor(false)
{
}

CInput::~CInput()
{
	Safe_Delete_Map(m_mapKey);
}

bool CInput::Init()
{

	AddKey("MoveUp", 'W');
	AddKey("MoveDown", 'S');
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');

	

	ShowCursor(TRUE);

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



PKEYINFO CInput::FindKey(const string& strKey)
{
	unordered_map<string, PKEYINFO>::iterator	iter = m_mapKey.find(strKey);

	if (iter == m_mapKey.end())
		return nullptr;

	return iter->second;
}
