#pragma once

#include"Game.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER m_tTick;
	LARGE_INTEGER m_tSecondTick;
	LARGE_INTEGER m_tSecond;
	float m_fDeltaTime;
	float m_fFPS;
	float m_fFPSTime;
	int m_iTick;
	int m_iLimitFrame;

public:
	float GetDeltaTime() const
	{
		return m_fDeltaTime;
	}
	float GetFPS() const
	{
		return m_fFPS;
	}
public:
	bool Init();
	void Update();

};