#pragma once

#include "Game.h"

class CCamera
{
private:
	POSITION	m_tPos;
	_SIZE		m_tResolution;
	_SIZE		m_tWorldSize;
	class CObj* m_pTarget;
	POSITION	m_tTargetPivot;

public:
	POSITION GetPos()	const
	{
		return m_tPos;
	}

	_SIZE GetResolution()	const
	{
		return m_tResolution;
	}

	_SIZE GetWorldSize()	const
	{
		return m_tWorldSize;
	}

public:
	void SetTarget(class CObj* pTarget);

	void SetTargetPivot(const POSITION& tPos)
	{
		m_tTargetPivot = tPos;
	}

	void SetTargetPivot(float x, float y)
	{
		m_tTargetPivot.x = x;
		m_tTargetPivot.y = y;
	}

	void SetPos(const POSITION& tPos)
	{
		m_tPos = tPos;
	}

	void SetPos(float x, float y)
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}

	void SetResolution(const _SIZE& tResolution)
	{
		m_tResolution = tResolution;
	}

	void SetResolution(float x, float y)
	{
		m_tResolution.x = x;
		m_tResolution.y = y;
	}

	void SetWorldSize(const _SIZE& tWorldSize)
	{
		m_tWorldSize = tWorldSize;
	}

	void SetWorldSize(float x, float y)
	{
		m_tWorldSize.x = x;
		m_tWorldSize.y = y;
	}

	void Move(float x, float y, float fTime)
	{
		m_tPos.x += x * fTime;
		m_tPos.y += y * fTime;

		if (m_tPos.x < 0.f)
			m_tPos.x = 0.f;

		else if (m_tPos.x + m_tResolution.x >= m_tWorldSize.x)
			m_tPos.x = m_tWorldSize.x - m_tResolution.x;

		if (m_tPos.y < 0.f)
			m_tPos.y = 0.f;

		else if (m_tPos.y + m_tResolution.y >= m_tWorldSize.y)
			m_tPos.y = m_tWorldSize.y - m_tResolution.y;
	}

public:
	bool Init();
	void Update(float fTime);

	DECLARE_SINGLE(CCamera)
};

