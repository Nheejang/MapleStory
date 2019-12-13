#include"Timer.h"
#include"Debug.h"

CTimer::CTimer() :
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iTick(0),
	m_iLimitFrame(0)
{

}

CTimer::~CTimer()
{

}

bool CTimer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTick);
	QueryPerformanceCounter(&m_tSecondTick);

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER tTick = {};
	QueryPerformanceCounter(&tTick);

	//현재 틱 - 이전틱을 초당 틱으로 나누어주면
	//현재 몇초가 지났는지 알 수 있다.
	//즉 1프레임이 지날때 시간을 구해줄 수 있게 된다.

	m_fDeltaTime = (tTick.QuadPart - m_tTick.QuadPart) /
		(float)m_tSecond.QuadPart;

	//연산이 끝난 후 이전 틱을 현재 틱으로 갱신해준다.
	m_tTick = tTick;

	if (m_tSecondTick.QuadPart - tTick.QuadPart >= m_tSecond.QuadPart)
	{
		QueryPerformanceFrequency(&m_tSecond);
		m_tSecondTick = tTick;
	}
	m_fFPSTime += m_fDeltaTime;
	++m_iTick;

	if (m_iTick == 60)
	{
		m_fFPS = m_iTick / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iTick = 0;

		char strText[128] = {};
		sprintf_s(strText, "FPS : %f, DeltaTime : %f", m_fFPS, m_fDeltaTime);

		CDebug::OutputTitle(strText);
	}
}