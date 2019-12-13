#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

protected:
	string m_strTag;
	int m_iRefCount;
	bool m_bEnable;
	bool m_bActive;

public:
	bool IsEnable()
	{
		return m_bEnable;
	}

	void SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
	}

	void SetActive(bool bActive)
	{
		m_bActive = bActive;
	}
	bool IsActive() const
	{
		return m_bActive;
	}

	void AddRef()
	{
		++m_iRefCount;
	}
	int Release()
	{
		--m_iRefCount;
		if (m_iRefCount == 0)
		{
			delete this;
			return 0;
		}
		return m_iRefCount;
	}

	void SetTag(const string& strTag)
	{
		m_strTag = strTag;
	}

	const string& GetTag() const
	{
		return m_strTag;
	}
};