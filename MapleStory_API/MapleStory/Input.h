#pragma once

#include "Game.h"

typedef struct _tagKeyInfo
{
	string			strName;
	vector<DWORD>	vecKey;
	bool	bPush;
	bool	bUp;
	bool	bPress;
}KEYINFO, * PKEYINFO;

class CInput
{
private:
	unordered_map<string, PKEYINFO>	m_mapKey;
	PKEYINFO		m_pCreateKey;
	POSITION		m_tMouseClient;
	POSITION		m_tMouseWorld;
	POSITION		m_tMouseGap;
	class CMouse*	m_pMouse;
	bool			m_bShowCursor;

public:
	class CMouse* GetMouseObj() const
	{
		return m_pMouse;
	}
	POSITION GetMouseGap() const
	{
		return m_tMouseGap;
	}
	POSITION GetMouseClient() const
	{
		return m_tMouseClient;
	}
	POSITION GetMouseWorld() const
	{
		return m_tMouseWorld;
	}

public:
	bool Init();
	void Update(float fTime);
	bool KeyPress(const string& strKey);
	bool KeyPush(const string& strKey);
	bool KeyUp(const string& strKey);
	void RenderMouse(HDC hDC, float fTime);

private:
	PKEYINFO FindKey(const string& strKey);

public:
	// 템플릿 가변인자의 종료조건 함수를 만들어준다.
	template <typename T>
	bool AddKey(const T& value)
	{
		const char* pType = typeid(T).name();

		if (strcmp(pType, "int") == 0 || strcmp(pType, "char") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)value);
		}

		else
		{
			m_pCreateKey->strName = value;

			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		return true;
	}

	template <typename T, typename ... Types>
	bool AddKey(const T& value, Types ... Args)
	{
		if (!m_pCreateKey)
		{
			m_pCreateKey = new KEYINFO;
			m_pCreateKey->bPress = false;
			m_pCreateKey->bPush = false;
			m_pCreateKey->bUp = false;
		}

		const char* pType = typeid(T).name();

		if (strcmp(pType, "int") == 0 || strcmp(pType, "char") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)value);
		}

		else
		{
			m_pCreateKey->strName = value;

			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		AddKey(Args...);

		if (m_pCreateKey)
			m_pCreateKey = nullptr;

		return true;
	}

	DECLARE_SINGLE(CInput)
};

